/*
 * Wrapper functions for our own library functions.
 * Most are included in the source file for the function itself.
 */

#include "unp.h"

void
Inet_pton(int family, const char *strptr, void *addrptr)
{
        int             n;

        if ( (n = inet_pton(family, strptr, addrptr)) < 0)
                err_sys("inet_pton error for %s", strptr);      /* errno set */
        else if (n == 0)
                err_quit("inet_pton error for %s", strptr);     /* errno not set */

        /* nothing to return */
}
