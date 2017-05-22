#pragma once
class MyMacPackage
{
protected:
	//Mac��ַ�ܹ���48λ�����ƣ�6�ֽڣ�12��16��������
	//�������ַ��ͱ����洢12��16������
	char sourceMac[13];
	char targetMac[13];

	//���ݲ��������1500���ֽ�
	char data[1501];

	//�̶���48���ֵ�Mac��ַ
	bool sourcMac_bit[48];
	bool sourceMac_bit[48];

	//��̬��������� �� ����
	bool* data_bit;

	const unsigned int minDataBytes = 46;
	const unsigned int maxDataBytes = 1500;

	MYCRC_8 crcCheckResult;
public:
	MyMacPackage();
	~MyMacPackage();

	void setSourceMac(const char source[13]);
	void setTargetMac(const char target[13]);
	void setData(const char data[], const int dataLength);
	void checkCRC();
};

