#pragma  once


int ndk_fprintf(FILE *stream, char *format , ...);
int ndk_printf( char *format , ...);
int ndk_fputs(const char * _str , FILE *stream);
int ndk_fputs(const char * _str , FILE *stream);
int ndk_puts(const char * _str);
int ndk_fputc(char _ch , FILE *stream);
int ndk_putchar(const char _ch);

#ifdef ANDROID
#define fprintf ndk_fprintf
#define printf  ndk_printf
#define fputs   ndk_fputs
#define puts    ndk_puts
#define fputc   ndk_fputc
#undef putchar
#define putchar ndk_putchar
#endif
