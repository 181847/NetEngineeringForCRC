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
	//先提取第0位到第7位之间的八个数据
	for (pData = 0; pData < 32; ++pData) {
		if (pData >= bitLength) {
			buffer[pData] = false;
		}
		else
		{
			buffer[pData] = data[pData];
		}

	}

	//从data数组的第0号位置开始检查
	int checkPointer = 0;

	//For_CRC_8
	for (; checkPointer < bitLength; ++checkPointer)
	{
		//如果第checkPointer位为true，
		//表示这个位置的比特数据为1
		if (buffer[0]) {
			//左移buffer中的数据一位，
			//末尾的数据由data[checkPointer + 9]来补足，
			//如果checkPointer + 9 >= bitLength，
			//就补false。
			leftMove(checkPointer, data, bitLength);
			//buffer中存储的后8位与对比数组进行异或运算,
			//由于最高位的1被省去，
			//这里只需要后面的8位运算。
			compareWithCheckerBuffer();
		}
		else {
			//只是左移一位
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
