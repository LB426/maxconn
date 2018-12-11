#include        "unp.h"

void
gen_num_str(int sockfd)
{
        char    sendline[MAXLINE], recvline[MAXLINE];

        strcpy(sendline, "1 1\n");
        printm("%s", sendline);

        Writen(sockfd, sendline, strlen(sendline));

        if (Readline(sockfd, recvline, MAXLINE) == 0)
                err_quit("str_cli: server terminated prematurely");

        Fputs(recvline, stdout);
}
