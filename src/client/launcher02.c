#include <unp.h>

#define MAXPROC 5

int
main(int argc, char **argv)
{
        pid_t pid;
        int i, stat;

        for (i = 0; i < MAXPROC; ++i) {
                if ((pid = fork()) < 0) {
                        err_sys("launcher: fork error");
                } else if (pid == 0) {
                        if (execlp("client05", "client05", "127.0.0.1", (char *)0) < 0)
                                err_sys("launcher: execlp error");
                }
        }

        while ((pid = wait(&stat)) > 0) {
                printf("proc end. PID=%d STAT=%d\n", pid, stat);
        }
        if (pid == -1)
                printf("launcher: wait ret -1. No child processes\n");

        printf("launcher end. PID=%d\n", getpid());

        exit(0);
}
