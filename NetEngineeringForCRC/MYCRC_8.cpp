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
 *		��Ϊ�����������ݣ�
 *		�������Ϊ8����������
 *@param bitLength
 *		�������ľ��峤�ȣ�
 *		������ڵ���8��
 */
void MYCRC_8::checkData(bool * data, int bitLength)
{
	if (bitLength <= 8) {
		return;
	}

	//����ȡ��0λ����7λ֮��İ˸�����
	for (int i = 1; i < 8; ++i) {
		buffer[i] = data[i];
	}

	//��data����ĵ�0��λ�ÿ�ʼ���
	int checkPointer = 0;

	for (; checkPointer < bitLength; ++checkPointer) {

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
