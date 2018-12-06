#include        "unp.h"
#include        <stdarg.h>              /* ANSI C header file */
#include        <syslog.h>              /* for syslog() */

int             daemon_proc;            /* set nonzero by daemon_init() */

static void     err_doit(int, int, const char *, va_list);

/* Fatal error related to system call
 * Print message and terminate */

void
err_sys(const char *fmt, ...)
{
        va_list         ap;

        va_start(ap, fmt);
        err_doit(1, LOG_ERR, fmt, ap);
        va_end(ap);
        exit(1);
}

/* Fatal error unrelated to system call
 * Print message and terminate */

void
err_quit(const char *fmt, ...)
{
        va_list         ap;

        va_start(ap, fmt);
        err_doit(0, LOG_ERR, fmt, ap);
        va_end(ap);
        exit(1);
}

/* Print message and return to caller
 * Caller specifies "errnoflag" and "level" */

static void
err_doit(int errnoflag, int level, const char *fmt, va_list ap)
{
        int     errno_save, n;
        char    buf[MAXLINE + 1];

        errno_save = errno;             /* value caller might want printed */
        vsnprintf(buf, MAXLINE, fmt, ap);
        n = strlen(buf);
        if (errnoflag)
                snprintf(buf + n, MAXLINE - n, ": %s", strerror(errno_save));
        strcat(buf, "\n");

        if (daemon_proc) {
                syslog(level, "%s", buf);
        } else {
                fflush(stdout);         /* in case stdout and stderr are the same */
                fputs(buf, stderr);
                fflush(stderr);
        }
        return;
}

void
printm(const char *fmt, ...)
{
        va_list         ap;
        char            buf[MAXLINE + 1] = {0};

        va_start(ap, fmt);
        vsnprintf(buf, MAXLINE, fmt, ap);
        printf("%s", buf);
        syslog(LOG_ALERT, "%s", buf);
        va_end(ap);
        return;
}
