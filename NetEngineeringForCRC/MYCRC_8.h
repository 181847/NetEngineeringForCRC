#pragma once
class MYCRC_8
{
protected:
	bool buffer[8];
	const bool checkBuffer[8] = 
		{ false, false, false, false, false, true, true, true };
	//G��X��=X8+X2+X1+1,�ھ�λ��true��ʡȥ��
public:
	MYCRC_8();
	~MYCRC_8();
	/**
	* Ϊdata�е����ݽ��м�飬�õ���У���뽫�����buffer�С�
	*/
	void checkData(bool* data, int bitLength);

	//����buffer�е�����һλ��
	//ĩβ��������data[checkPointer + 9]�����㣬
	//���checkPointer + 9 >= bitLength��
	//�Ͳ�false��
	void leftMove(int checkPointer, bool* data, int bitLength);

	//buffer�д洢�ĺ�8λ��Ա���������������,
	//�������λ��1��ʡȥ��
	//����ֻ��Ҫ�����8λ���㡣
	void compareWithCheckerBuffer();

	//��01����������ʽ�����������������̨�ϣ�
	void showAsBit();
};