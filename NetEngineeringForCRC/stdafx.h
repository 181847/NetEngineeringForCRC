// stdafx.h : ��׼ϵͳ�����ļ��İ����ļ���
// ���Ǿ���ʹ�õ��������ĵ�
// �ض�����Ŀ�İ����ļ�
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

//�ĸ��ֽڵ��ַ���������Ϊһ���ṹ�塣
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




// TODO:  �ڴ˴����ó�����Ҫ������ͷ�ļ�
