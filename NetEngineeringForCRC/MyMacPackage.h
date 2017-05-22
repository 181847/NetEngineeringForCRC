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

	//固定的48个字的Mac地址
	bool sourcMac_bit[48];
	bool sourceMac_bit[48];

	//动态分配的数据 字 数组
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

