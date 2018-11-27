/* include unph */

#ifndef __unp_h
#define __unp_h

#include        <netinet/in.h>
#include        <sys/socket.h>
#include        <errno.h>
#include        <stdio.h>
#include        <stdlib.h>
#include        <string.h>
#include        <unistd.h>

#define SA      struct sockaddr

/* Miscellaneous constants */
#define MAXLINE         4096    /* max text line length */
#define BUFFSIZE        8192    /* buffer size for reads and writes */
#define SERV_PORT       9877
#define LISTENQ         1024

void     Close(int);
pid_t    Fork(void);
int      Accept(int, SA *, socklen_t *);
void     Bind(int, const SA *, socklen_t);
void     Listen(int, int);
int      Socket(int, int, int);
void     Writen(int, void *, size_t);
void     str_echo(int);
void     err_sys(const char *, ...);

#endif  /* __unp_h */
