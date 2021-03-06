/*******************************************************************************
 * соединяется с сервером и отсылает два числа в виде строки, разделитель пробел 
 * сервер вычисляет сумму чисел и отсылает клиенту
 * клиент проверяет сумму и если всё нормально то засыпает на период
 * просыпается и повторяет.
 * всё делается в бесконечном цикле.
 ******************************************************************************/

#include "unp.h"

int 
main(int argc, char **argv)
{
        int                     sockfd;
        struct sockaddr_in      servaddr;

        if (argc != 2)
                err_quit("usage: client <IPaddress>");

        sockfd = Socket(AF_INET, SOCK_STREAM, 0);

        bzero(&servaddr, sizeof(servaddr));
        servaddr.sin_family = AF_INET;
        servaddr.sin_port = htons(SERV_PORT);
        Inet_pton(AF_INET, argv[1], &servaddr.sin_addr);

        Connect(sockfd, (SA *) &servaddr, sizeof(servaddr));

        gen_num_str(sockfd);

        exit(0);
}
