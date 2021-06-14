#include "apue.h"
#include <sys/socket.h>

/* size of control buffer to send/recv one file descriptor */
#define CMSG_LEN(l)             (__DARWIN_ALIGN32(sizeof(struct cmsghdr)) + (l))
#define	CONTROLLEN	CMSG_LEN(sizeof(int))

static struct cmsghdr	*cmptr = NULL;	/* malloc'ed first time */

/*
 * Pass a file descriptor to another process.
 * If fd<0, then -fd is sent back instead as the error status.
 */
int
send_fd(int fd, int fd_to_send)
{
	struct iovec	iov[1];   //iovec表示io缓存buf
	struct msghdr	msg;   //包含了要发送或接受的消息
	char			buf[2];	/* send_fd()/recv_fd() 2-byte protocol */

	iov[0].iov_base = buf;   //在2字节0之后开始
	iov[0].iov_len  = 2;   //长度为2字节
	msg.msg_iov     = iov;
	msg.msg_iovlen  = 1;  //数组长度1
	msg.msg_name    = NULL;
	msg.msg_namelen = 0;

	if (fd_to_send < 0) {  //如果fd为负数
		msg.msg_control    = NULL;
		msg.msg_controllen = 0;
		buf[1] = -fd_to_send;	/* nonzero status means error */
		if (buf[1] == 0)
			buf[1] = 1;	/* -256, etc. would screw up protocol */
	} else {
		if (cmptr == NULL && (cmptr = malloc(CONTROLLEN)) == NULL)
			return(-1);
		cmptr->cmsg_level  = SOL_SOCKET;  //控制级别为套接字
		cmptr->cmsg_type   = SCM_RIGHTS;  //传送访问权
		cmptr->cmsg_len    = CONTROLLEN;
		msg.msg_control    = cmptr;  //控制信息头
		msg.msg_controllen = CONTROLLEN;
		*(int *)CMSG_DATA(cmptr) = fd_to_send;		/* the fd to pass */
		buf[1] = 0;		/* zero status means OK */
	}

	buf[0] = 0;			/* null byte flag to recv_fd() */
	if (sendmsg(fd, &msg, 0) != 2)   //发送消息，fd是建好连接的套接字
		return(-1);
	return(0);
}
