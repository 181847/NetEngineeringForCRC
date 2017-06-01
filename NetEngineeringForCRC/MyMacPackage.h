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
	//ԭʼ���õ����ݳ��ȣ����ֽ�Ϊ��λ
	unsigned int originalDataLength;
	//����У�飨���ܻ���������䣩�������ݳ��ȣ�
	//���ֽ�Ϊ��λ��
	unsigned int dataLength;

	//��̬��������� �� ����
	//���������ԴMac��ַ��Ŀ��Mac��ַ��
	//�Լ�data����ʾ�Ķ���������
	bool bit_array[1501 * 8];
	unsigned int bit_array_length;

	const unsigned int minDataBytes = 46;
	const unsigned int maxDataBytes = 1500;

	//FCSУ������ֽڳ���
	unsigned int FCS_length;
	bool fillTo64;

	//�Ƿ�����CRC32��У�顣
	bool enableCRC_32;
public:
	MYCRC_8 crcCheckResult;
	MYCRC_32 crcCheckResult_32;
	friend class MyMacPackageDisplayer;

public:
	MyMacPackage();
	~MyMacPackage();

	void setSourceMac(const char source[13]);
	void setTargetMac(const char target[13]);
	void setData(const char data[], const unsigned int dataLength);
	int checkCRC();
	void fillbit_array();

	void static translate_hex_to_bit(const char hexChar[],
		unsigned int hex_length,
		bool bit_array[], 
		unsigned int startLocation);

	void static translate_hex_to_bit(const char hex,
		bool bit_array[],
		unsigned int startLocation);

	void static translate_uint_to_16bit(unsigned int number,
		bool bit_array[], 
		unsigned int 
		startLocaation);

	void static translate_char_to_bit(const char string[],
		unsigned int string_length,
		bool bit_array[],
		unsigned int startLocation);

	void static translate_char_to_bit(const char charactor,
		bool bit_array[],
		unsigned int startLocation);

	void static fillWith(bool bit_0, bool bit_1, bool bit_2, bool bit_3,
		bool bit_array[],
		unsigned int startLocation);

	void setFillTo64(bool fillTo64);

	//�����Ƿ�����CRC32��У�顣
	void enable_CRC_32(bool enableCRC_32);

	//��CRCУ��õ�������׷�ӵ�Mac����β����
	void appendFCS();
};

