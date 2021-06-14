#include	"opend.h"
#include	<syslog.h>

int		 debug, oflag, client_size, log_to_stderr;
char	 errmsg[MAXLINE];
char	*pathname;
Client	*client = NULL;

/*
 *  服务器进程2
 */
int main(int argc, char *argv[])
{
	int		c;

	log_open("open.serv", LOG_PID, LOG_USER);

	opterr = 0;		/* don't want getopt() writing to stderr */
	while ((c = getopt(argc, argv, "d")) != EOF) {  //遍历检查函数参数，d表示守护进程
		switch (c) {
		case 'd':		/* debug */
			debug = log_to_stderr = 1;   // debug = log_to_stderr; log_to_stderr = 1;
			break;

		case '?':
			err_quit("unrecognized option: -%c", optopt);
		}
	}

	if (debug == 0)
		daemonize("opend");  //转为守护进程，父进程关闭

	loop();		/* never returns */
}
