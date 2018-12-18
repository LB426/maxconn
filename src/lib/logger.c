#include        "unp.h"
#include        <stdarg.h>

char logdir[128] = {0};

/* лог в файл */
void
log_to_file(const char* message, ...)
{
        char msgstr[2048] = {0};
        va_list args;
        char timestr[128] = {0};
        time_t now;
        struct tm *t; 
        char filename[64] = {0};
        FILE *f; 

        
        snprintf(filename, 256, "%s/%s%d.log", logdir,"client", getpid());
        now = time(NULL);
        t = localtime(&now);
        strftime(timestr, sizeof(timestr), "%Y-%m-%d %H:%M:%S", t); 

        va_start(args, message);
        vsprintf(msgstr, message, args);
        va_end(args);

        for(int i = 0; i < 2048; ++i) {
                if (msgstr[i] == 0x0A)
                        msgstr[i] = ' ';
        }

        f = fopen( filename, "a+" );
        if(f == NULL) {
                printf("ERROR can't open log file %s\n", filename);
                exit(1);
        } else {
                fprintf( f, "%s %s\n", timestr, msgstr );
                fclose(f);
        }   
}
