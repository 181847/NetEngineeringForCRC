// stdafx.h : 标准系统包含文件的包含文件，
// 或是经常使用但不常更改的
// 特定于项目的包含文件
//

#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>
#include <iostream>
#include <sstream>
#include "MYCRC_8.h"
#include "MYCRC_32.h"
#include "MyMacPackage.h"
#include "MyMacPackageDisplayer.h"
#include "Tools.h"

#define USE_MICROSOFT_FUN_S 1

#ifdef USE_MICROSOFT_FUN_S
#define strcpy strcpy_s
#endif

//四个字节的字符型数组作为一个结构体。
typedef struct CHAR4 {
	unsigned char C0;
	unsigned char C1;
	unsigned char C2;
	unsigned char C3;
} CHAR4;

typedef union U_U16_CHAR4{
	unsigned int U16;
	CHAR4 C4;
} U_U16_CHAR4;




// TODO:  在此处引用程序需要的其他头文件
