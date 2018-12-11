/* include unph */

#ifndef __unp_h
#define __unp_h

#include        <netinet/in.h>
#include        <arpa/inet.h>
#include        <sys/socket.h>
#include        <errno.h>
#include        <signal.h>
#include        <stdio.h>
#include        <stdlib.h>
#include        <string.h>
#include        <unistd.h>
#include        <sys/wait.h>

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
void     Connect(int, const struct sockaddr *, socklen_t);
void     Listen(int, int);
int      Socket(int, int, int);
void     Writen(int, void *, size_t);
void     err_sys(const char *, ...);
void     err_quit(const char *, ...);
void     printm(const char *, ...);
void     Inet_pton(int, const char *, void *);
void     str_echo(int);
void     str_cli(FILE *, int);
void     str_cli2(FILE *, int);
char     *Fgets(char *, int, FILE *);
void     Fputs(const char *, FILE *);
ssize_t  Readline(int, void *, size_t);

typedef void    Sigfunc(int);   /* for signal handlers */
Sigfunc  *Signal(int, Sigfunc *);
void     sig_chld(int);

#endif  /* __unp_h */
