#pragma once
class MYCRC_32
{
protected:
	bool buffer[32];
	const bool checkBuffer[32] =
	{
		false, false, false, false,  false, true, false, false,
		true, true, false, false,  false, false, false, true,
		false, false, false, true,  true, true, false, true,
		true, false, true, true,  false, true, true, true
	};
public:
	MYCRC_32();
	~MYCRC_32();

	/**
	* Ϊdata�е����ݽ��м�飬�õ���У���뽫�����buffer�С�
	*/
	void checkData(bool* data, int bitLength);

	//����buffer�е�����һλ��
	//ĩβ��������data[checkPointer + 32]�����㣬
	//���checkPointer + 32 >= bitLength��
	//�Ͳ�false��
	void leftMove(int checkPointer, bool* data, int bitLength);

	//buffer�д洢��32λ��Ա���������������,
	//�������λ��1��ʡȥ��
	//����ֻ��Ҫ�����32λ���㡣
	void compareWithCheckerBuffer();

	const bool * getResult();
};

