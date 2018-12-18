#include <unp.h>

#define MAXPROC 5

int
main(int argc, char **argv)
{
        pid_t pid;
        int i, stat;

        if (argc != 2)
                err_quit("usage: launcher <number of process>");

        for (i = 0; i < atoi(argv[1]); ++i) {
                if ((pid = fork()) < 0) {
                        err_sys("launcher: fork error");
                } else if (pid == 0) {
                        if (execlp("client06", "client06", "127.0.0.1", "logdir", (char *)0) < 0)
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
