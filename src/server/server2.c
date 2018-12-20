#include "unp.h"

extern _procinfo procinfo;

int 
main(int argc, char **argv)
{
        int                     listenfd, connfd;
        pid_t                   childpid;
        socklen_t               clilen;
        struct sockaddr_in      cliaddr, servaddr;
        void                    sig_chld(int);

        if (argc != 2)
                err_quit("usage: server2 <logdir>");
        snprintf(procinfo.progname, 32, "%s", basename(argv[0]));        
        snprintf(procinfo.logdirpath, 128, "%s", argv[1]);        

        log_to_file("server2 start");

        listenfd = Socket(AF_INET, SOCK_STREAM, 0);

        bzero(&servaddr, sizeof(servaddr));
        servaddr.sin_family      = AF_INET;
        servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
        servaddr.sin_port        = htons(SERV_PORT);

        Bind(listenfd, (SA *) &servaddr, sizeof(servaddr));

        Listen(listenfd, LISTENQ);

        Signal(SIGCHLD, sig_chld);

        for( ; ; ) {
                clilen = sizeof(cliaddr);
                if ( (connfd = accept(listenfd, (SA *) &cliaddr, &clilen)) < 0) {
                        if (errno == EINTR)
                                continue;               /* back to for */
                        else
                                err_sys("accept error");
                }

                if( (childpid = Fork()) == 0 ) {
                        Close(listenfd);
                        str_echo2(connfd);
                        exit(0);
                }
                Close(connfd);
        }

        log_to_file("server2 stop");

        return 0;
}
