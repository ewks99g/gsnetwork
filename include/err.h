
/******************************************************************* 
 *  Copyright(c) 2000-2013 linghegu
 *  All rights reserved. 
 *   
 ******************************************************************/
#pragma once




#define output_error(x)   const char *errstr = strerror (x);\            
					   fprintf (stderr, "%s (%s:%d)\n", errstr, __FILE__, __LINE__);\           
					   abort();

























