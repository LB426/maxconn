/* отслеживает дочерний процесс по сигналу SIGCHLD */
#include <unp.h>

void 
sig_chld(int signo)
{
        pid_t   pid;
        int     stat;

        while ( (pid = waitpid(-1, &stat, WNOHANG)) > 0)
                printf("launcher. signal_handler. child %d terminated\n", pid);
}

int
main(int argc, char **argv)
{
        pid_t pid;
        int errno_save;

        signal(SIGCHLD, sig_chld);
        errno_save = errno;
        if (errno_save != 0)
                printf("launcher. errno: %d, %s\n", errno_save, strerror(errno));

        if ((pid = fork()) < 0) {
                err_sys("launcher: fork error");
        } else if (pid == 0) {
                if (execlp("client05", "client05", "127.0.0.1", (char *)0) < 0)
                        err_sys("launcher: execlp error");
        }

        sleep(30);

        printf("launcher end. PID=%d\n", getpid());

        exit(0);
}
