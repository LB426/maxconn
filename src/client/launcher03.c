#include <unp.h>

extern _procinfo procinfo;

int
main(int argc, char **argv)
{
        pid_t pid;
        int i, stat;

        if (argc != 3)
                err_quit("usage: launcher <number of process> <logdir>");
        snprintf(procinfo.progname, 32, "%s", basename(argv[0]));        
        snprintf(procinfo.logdirpath, 128, "%s", argv[2]);        

        for (i = 0; i < atoi(argv[1]); ++i) {
                if ((pid = fork()) < 0) {
                        err_sys("launcher: fork error");
                } else if (pid == 0) {
                        if (execlp("client06", "client06", "127.0.0.1", "logdir", (char *)0) < 0)
                                err_sys("launcher: execlp error");
                }
        }

        while ((pid = wait(&stat)) > 0) {
                log_to_file("proc end. PID=%d STAT=%d", pid, stat);
        }
        if (pid == -1)
                log_to_file("launcher: wait ret -1. No child processes\n");

        printf("launcher end. PID=%d\n", getpid());

        exit(0);
}
