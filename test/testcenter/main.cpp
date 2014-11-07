/*******************************************************************
*  Copyright(c) 2000-2013 linghegu
*  All rights reserved.
*  Author: 	wangbin
*  Email:  	wang70bin@163.com
*  CreateTime: 2014/05/31
******************************************************************/
#include <stdio.h>
#include <unistd.h>
#include <map>
#include "head.h"
#include <pthread.h>


void *func1(void * arg)
{
sleep(20);
   printf("线程1（ID：0x%x）退出。/n",(unsigned int)pthread_self());
   pthread_exit((void *)0);
}


int
main()
{
	float _val = float(90)/float(100);
	printf("%0.5f",_val);
}	

