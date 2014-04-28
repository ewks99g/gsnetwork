
/*******************************************************************
*  Copyright(c) 2000-2013 lingheg
*  All rights reserved.
*  Author: 	wangbin
*  Email:  	wang70bin@163.com
*  CreateTime: 2014/04/28
******************************************************************/
#pragma once

#include "msg.h"

struct SSquareTestInfo
{
	int len;
	int width;
};

typedef CMessageMonoInfoTemplate<SSquareTestInfo> CMessageSquareMsg;
typedef CMessageFlexInfoTemplate<SSquareTestInfo,30> CMessageMultiSquareMsg;
