
/******************************************************************* 
 *  Copyright(c) 2000-2013 linghegu
 *  All rights reserved. 
 *   
 ******************************************************************/
#pragma once


#define output_error(descstr)   const char *errstr = strerror (errno);\
					   fprintf (stderr, "%s: %s (%s:%d)\n",descstr,errstr, __FILE__, __LINE__);\
					   abort();


#define	output_debug(str)	 fprintf (stdout, "%s (%s:%d)\n",str , __FILE__, __LINE__);
