
/******************************************************************* 
 *  Copyright(c) 2000-2013 linghegu
 *  All rights reserved. 
 *   
 ******************************************************************/
#pragma once




#define output_error(x)   const char *errstr = strerror (x);\            
					   fprintf (stderr, "%s (%s:%d)\n", errstr, __FILE__, __LINE__);\           
					   abort();


#define	output_debug(str)	 fprintf (stdout, "%s (%s:%d)\n",str , __FILE__, __LINE__);
