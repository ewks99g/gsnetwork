
/******************************************************************* 
 *  Copyright(c) 2000-2013 linghegu
 *  All rights reserved. 
 *   
 *  文件名称: err description
 *  简要描述: 
 *   
 *  创建日期: 2014/4/14
 *  作者:	      wangbin
 *  说明: 	      
 ******************************************************************/
#pragma once




#define output_error(x)   const char *errstr = strerror (x);\            
					   fprintf (stderr, "%s (%s:%d)\n", errstr, __FILE__, __LINE__);\           
					   abort();

























