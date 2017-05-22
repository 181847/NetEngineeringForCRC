#include "stdafx.h"
#include "MYCRC_8.h"

MYCRC_8::MYCRC_8()
{
	for (int i = 0; i < 8; ++i) {
		buffer[i] = false;
	}
}


MYCRC_8::~MYCRC_8()
{
}

/*
 *@param data 
 *		作为比特流的数据，
 *		长度最好为8的整数倍，
 *@param bitLength
 *		比特流的具体长度，
 *		必须大于等于8。
 */
void MYCRC_8::checkData(bool * data, int bitLength)
{
	if (bitLength <= 8) {
		return;
	}

	//先提取第0位到第7位之间的八个数据
	for (int i = 1; i < 8; ++i) {
		buffer[i] = data[i];
	}

	//从data数组的第0号位置开始检查
	int checkPointer = 0;

	for (; checkPointer < bitLength; ++checkPointer) {

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

void MYCRC_8::leftMove(int checkPointer, bool * data, int bitLength)
{
	checkPointer += 8;
	for (int i = 0; i < 7; ++i) {
		buffer[i] = buffer[i + 1];
	}

	if (checkPointer >= bitLength) {
		buffer[7] = false;
	}
	else {
		buffer[7] = data[checkPointer];
	}
}

void MYCRC_8::compareWithCheckerBuffer()
{
	for (int i = 0; i < 8; ++i) {
		buffer[i] = buffer[i] != checkBuffer[i];
	}
}

void MYCRC_8::showAsBit()
{
	for (int i = 0; i < 8; ++i) {
		std::cout << buffer[i] ? '1' : '0';
	}
}
