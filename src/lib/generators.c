#include        "unp.h"

void
gen_num_str(int sockfd)
{
        char    sendline[MAXLINE], recvline[MAXLINE];
        int max, min, suml, sumr, n1, n2;

        max = 1000; min = 0;

        srand(time(NULL));
        while (1) {
                n1 = (rand()%(max-min))+min;
                n2 = (rand()%(max-min))+min;
                suml = n1 + n2;
                snprintf(sendline, sizeof(sendline), "%d %d\n", n1 , n2);
                printm("-> data to send: %s", sendline);

                Writen(sockfd, sendline, strlen(sendline));

                if (Readline(sockfd, recvline, MAXLINE) == 0)
                        err_quit("str_cli: server terminated prematurely");

                printm("<- recived data: %s", recvline);
                sumr = atoi(recvline);
                if (suml == sumr)
                        printm("== OK  sumr=%d suml=%d\n", sumr, suml);
                else
                        printm("== ERR sumr=%d suml=%d\n", sumr, suml);
                sleep(5);
        }
}
