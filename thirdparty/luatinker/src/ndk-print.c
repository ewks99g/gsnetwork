#include <stdio.h>
#include <stdarg.h>

#ifdef ANDROID
#include <jni.h>
#include <android/log.h>
#define  LOG_TAG    "cos_game"
#define  LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)
#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)
#endif


int ndk_fprintf(FILE *stream,char *_format , ...)
{
	char _buf[1024 * 8 ] = {0};
    va_list ap;
    va_start(ap,_format); 
	vsnprintf(_format , 1024 * 8 , _buf , ap);
    va_end(ap);
#ifdef ANDROID
	if(stream == stderr || stream == stdout )
	{
		LOGI("%s",_buf);
	    return 0;
	}
#endif
	return fputs(_buf , stream );
}

int ndk_printf(char *_format , ...)
{
	char _buf[1024 * 8 ] = {0};
	va_list ap;
	va_start(ap,_format);
	vsnprintf(_format,1024*8,_buf,ap);
	va_end(ap);
#ifdef ANDROID
	LOGI("%s",_buf);
#endif
	return printf("%s",_buf);
}

int ndk_fputs(const char * _str , FILE *stream)
{
#ifdef ANDROID
	if(stream == stderr || stream == stdout )
	{
		LOGI("%s",_str);
	}
#endif
	return fputs(_str , stream);
}

int ndk_puts(const char * _str)
{
#ifdef ANDROID
	LOGI("%s",_str);
#endif
	return puts(_str);
}


int ndk_fputc(char _ch , FILE *stream)
{
#ifdef ANDROID
	if(stream == stderr || stream == stdout )
	{
		char _buf[2] = {_ch , 0};
		LOGI("%s",_buf);
	}
#endif
	return fputc(_ch , stream);
}

int ndk_putchar(char _ch)
{
#ifdef ANDROID
	char _buf[2] = {_ch , 0};
	LOGI("%s",_buf);
#endif
	return putchar(_ch);
}
