#include "stdafx.h"
#include "MYCRC_32.h"


MYCRC_32::MYCRC_32()
{
	for (unsigned int i = 0; i < 32; ++i)
	{
		buffer[i] = 1;
	}
}


MYCRC_32::~MYCRC_32()
{
}

void MYCRC_32::checkData(bool * data, int bitLength)
{
	if (bitLength <= 0) {
		return;
	}

	unsigned int pData;
	//ForCRC_8
	//����ȡ��0λ����7λ֮��İ˸�����
	for (pData = 0; pData < 32; ++pData) {
		if (pData >= bitLength) {
			buffer[pData] = false;
		}
		else
		{
			buffer[pData] = data[pData];
		}

	}

	//��data����ĵ�0��λ�ÿ�ʼ���
	int checkPointer = 0;

	//For_CRC_8
	for (; checkPointer < bitLength; ++checkPointer)
	{
		//�����checkPointerλΪtrue��
		//��ʾ���λ�õı�������Ϊ1
		if (buffer[0]) {
			//����buffer�е�����һλ��
			//ĩβ��������data[checkPointer + 9]�����㣬
			//���checkPointer + 9 >= bitLength��
			//�Ͳ�false��
			leftMove(checkPointer, data, bitLength);
			//buffer�д洢�ĺ�8λ��Ա���������������,
			//�������λ��1��ʡȥ��
			//����ֻ��Ҫ�����8λ���㡣
			compareWithCheckerBuffer();
		}
		else {
			//ֻ������һλ
			leftMove(checkPointer, data, bitLength);
		}
	}
}

void MYCRC_32::leftMove(int checkPointer, bool * data, int bitLength)
{
	checkPointer += 32;
	for (int i = 0; i < 31; ++i) {
		buffer[i] = buffer[i + 1];
	}

	if (checkPointer >= bitLength) {
		buffer[31] = false;
	}
	else {
		buffer[31] = data[checkPointer];
	}
}

void MYCRC_32::compareWithCheckerBuffer()
{
	for (int i = 0; i < 32; ++i) {
		buffer[i] = buffer[i] != checkBuffer[i];
	}
}

const bool * MYCRC_32::getResult()
{
	return buffer;
}
