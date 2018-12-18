/*******************************************************************************
 * соединяется с сервером и отсылает два числа в виде строки, разделитель пробел 
 * сервер вычисляет сумму чисел и отсылает клиенту
 * клиент проверяет сумму и завершается
 ******************************************************************************/
#include "unp.h"

int 
main(int argc, char **argv)
{
        int                     sockfd;
        struct sockaddr_in      servaddr;
        char   sendline[MAXLINE], recvline[MAXLINE];
        int    max, min, suml, sumr, n1, n2;

        if (argc != 2)
                err_quit("usage: client <IPaddress>");

        sockfd = Socket(AF_INET, SOCK_STREAM, 0);

        bzero(&servaddr, sizeof(servaddr));
        servaddr.sin_family = AF_INET;
        servaddr.sin_port = htons(SERV_PORT);
        Inet_pton(AF_INET, argv[1], &servaddr.sin_addr);

        Connect(sockfd, (SA *) &servaddr, sizeof(servaddr));

        max = 1000; min = 0;
        srand(time(NULL));
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

        printf("client05 end. PID=%d\n", getpid());

        exit(0);
}
