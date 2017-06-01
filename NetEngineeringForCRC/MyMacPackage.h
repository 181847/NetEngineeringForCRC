#pragma once

class MyMacPackage
{
protected:
	//Mac地址总共有48位二进制，6字节，12个16进制数，
	//这里用字符型变量存储12个16进制数
	char sourceMac[13];
	char targetMac[13];

	//数据部分最多有1500个字节
	char data[1501];
	//原始设置的数据长度，以字节为单位
	unsigned int originalDataLength;
	//进行校验（可能会有数据填充）会后的数据长度，
	//以字节为单位。
	unsigned int dataLength;

	//动态分配的数据 字 数组
	//这里面包括源Mac地址和目的Mac地址，
	//以及data所表示的二进制数据
	bool bit_array[1501 * 8];
	unsigned int bit_array_length;

	const unsigned int minDataBytes = 46;
	const unsigned int maxDataBytes = 1500;

	//FCS校验码的字节长度
	unsigned int FCS_length;
	bool fillTo64;

	//是否启用CRC32来校验。
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

	//设置是否启用CRC32来校验。
	void enable_CRC_32(bool enableCRC_32);

	//将CRC校验得到的数据追加到Mac包的尾部。
	void appendFCS();
};

