#include "stdafx.h"
#include "MyMacPackage.h"

extern bool IS_BIG_ENDIAN;

MyMacPackage::MyMacPackage()
{
	FCS_length = 4;
	enableCRC_32 = false;
}


MyMacPackage::~MyMacPackage()
{
}

//设置源Mac地址，使用12位16进制数表示
void MyMacPackage::setSourceMac(const char source[13])
{
	strcpy(sourceMac, source);
}

void MyMacPackage::setTargetMac(const char target[13])
{
	strcpy(targetMac, target);
}

//设置数据部分的字节，每个字符表示一个字节的数据
//dataLength
//		字符的长度。
void MyMacPackage::setData(const char data[], const unsigned int dataLength)
{
	if (dataLength < 0) {
		return;
	}

	this->originalDataLength = dataLength;
	this->dataLength = dataLength;
	//记录数据
	for (unsigned int i = 0; i < dataLength; ++i)
	{
		this->data[i] = data[i];
	}
}

//将源Mac地址、目的Mac地址 以及 数据部分，
//全部翻译成二进制形式存在bit_array数组中，
//操作失败返回0，成功返回1.
int MyMacPackage::checkCRC()
{
	//从两个Mac地址和数据部分，填充字 到bit_array数组中。
	fillbit_array();

	//计算校验和
	crcCheckResult.checkData(bit_array, bit_array_length - FCS_length * 8);

	crcCheckResult_32.checkData(bit_array, bit_array_length - FCS_length * 8);

	appendFCS();

	return 1;
}

//将两个Mac地址和数据部分的数据，翻译成字（bit）的形式，
//存到bit_array数组中，无需为bit_array重新分配数组空间
void MyMacPackage::fillbit_array()
{
	//将两个Mac地址转换成bit数组
	translate_hex_to_bit(sourceMac, 12, bit_array, 0);
	translate_hex_to_bit(targetMac, 12, bit_array, 6 * 8);

	//将数据部分转换成字（bit）的形式，存在bit_array数组中
	translate_char_to_bit(data, dataLength, bit_array, (12 + 2) * 8);

	//如果数据部分的长度小于46，
	//而且要保证Mac帧长度至少为64。
	if (originalDataLength < 46 && fillTo64) {
		for (int i = (12 + 2 + originalDataLength) * 8; i < 60 * 8; ++i)
		{//注意最后的4字节是FCS校验码
			bit_array[i] = false;
		}
		//修改数据部分的长度为46.
		dataLength = 46;
	}
	else
	{
		dataLength = originalDataLength;
	}

	bit_array_length = 12 * 8	//两个Mac地址的字长度
		+ 2 * 8					//Mac长度字段
		+ dataLength * 8		//数据字段长度
		+ FCS_length * 8;			//校验和长度

	//将Mac帧数据部分的长度，用16位二进制存到bit_array数组中
	translate_uint_to_16bit(dataLength,
		bit_array, 12 * 8);
}

//假设hexChar存储的是表示16进制数据的数字，
//讲这些数字翻译成字（bit）的形式，
//从bit_array数组中startLocation位置开始存放bit数据。
void MyMacPackage::translate_hex_to_bit(const char hexChar[], unsigned int hex_length, bool bit_array[], unsigned int startLocation)
{
	for (unsigned int i = 0; i < hex_length; ++i)
	{
		translate_hex_to_bit(hexChar[i], bit_array, startLocation + i * 4 );
	}
}

//将16进制的字符转换成bit形式存到bit_array的startLocation位置。
void MyMacPackage::translate_hex_to_bit(const char hex, bool bit_array[], unsigned int startLocation)
{
	switch (hex) {
	case '0':
		fillWith(0, 0, 0, 0, bit_array, startLocation);
		break;
	case '1':
		fillWith(0, 0, 0, 1, bit_array, startLocation);
		break;
	case '2':
		fillWith(0, 0, 1, 0, bit_array, startLocation);
		break;
	case '3':
		fillWith(0, 0, 1, 1, bit_array, startLocation);
		break;
	case '4':
		fillWith(0, 1, 0, 0, bit_array, startLocation);
		break;
	case '5':
		fillWith(0, 1, 0, 1, bit_array, startLocation);
		break;
	case '6':
		fillWith(0, 1, 1, 0, bit_array, startLocation);
		break;
	case '7':
		fillWith(0, 1, 1, 1, bit_array, startLocation);
		break;
	case '8':
		fillWith(1, 0, 0, 0, bit_array, startLocation);
		break;
	case '9':
		fillWith(1, 0, 0, 1, bit_array, startLocation);
		break;
	case 'a':
	case 'A':
		fillWith(1, 0, 1, 0, bit_array, startLocation);
		break;
	case 'b':
	case 'B':
		fillWith(1, 0, 1, 1, bit_array, startLocation);
		break;
	case 'c':
	case 'C':
		fillWith(1, 1, 0, 0, bit_array, startLocation);
		break;
	case 'd':
	case 'D':
		fillWith(1, 1, 0, 1, bit_array, startLocation);
		break;
	case 'e':
	case 'E':
		fillWith(1, 1, 1, 0, bit_array, startLocation);
		break;
	case 'f':
	case 'F':
		fillWith(1, 1, 1, 1, bit_array, startLocation);
		break;
	default:
		fillWith(0, 0, 0, 0, bit_array, startLocation);
	}
}

//将无符号整形转换成字节形式。
void MyMacPackage::translate_uint_to_16bit(unsigned int number, bool bit_array[], unsigned int startLocation)
{
	//准备提取无符号整形
	U_U16_CHAR4 transport;
	transport.U16 = number;
	if (IS_BIG_ENDIAN)
	{
		//大端序
		translate_char_to_bit(transport.C4.C2, bit_array, startLocation);
		translate_char_to_bit(transport.C4.C3, bit_array, startLocation + 8);
	}
	else
	{
		//小端序
		translate_char_to_bit(transport.C4.C1, bit_array, startLocation);
		translate_char_to_bit(transport.C4.C0, bit_array, startLocation + 8);
	}
}

//将字符串全部转换成bit存进bit_array数组中。
void MyMacPackage::translate_char_to_bit(const char string[], unsigned int string_length, bool bit_array[], unsigned int startLocation)
{
	for (unsigned int i = 0; i < string_length; ++i)
	{
		translate_char_to_bit(string[i], bit_array, startLocation + i * 8);
	}
}

//将字符转换成bit存进bit_array数组中。
void MyMacPackage::translate_char_to_bit(const char charactor, bool bit_array[], unsigned int startLocation)
{
	if (charactor & 0x80)//1000 0000
	{//字符第1位为 1
		bit_array[startLocation] = 1;
	}
	else
	{
		bit_array[startLocation] = 0;
	}

	if (charactor & 0x40)//0100 0000
	{//字符第1位为 1
		bit_array[startLocation + 1] = 1;
	}
	else
	{
		bit_array[startLocation + 1] = 0;
	}

	if (charactor & 0x20)//0010 0000
	{//字符第1位为 1
		bit_array[startLocation + 2] = 1;
	}
	else
	{
		bit_array[startLocation + 2] = 0;
	}

	if (charactor & 0x10)//0001 0000
	{//字符第1位为 1
		bit_array[startLocation + 3] = 1;
	}
	else
	{
		bit_array[startLocation + 3] = 0;
	}

	if (charactor & 0x08)//0000 1000
	{//字符第1位为 1
		bit_array[startLocation + 4] = 1;
	}
	else
	{
		bit_array[startLocation + 4] = 0;
	}

	if (charactor & 0x04)//0000 0100
	{//字符第1位为 1
		bit_array[startLocation + 5] = 1;
	}
	else
	{
		bit_array[startLocation + 5] = 0;
	}

	if (charactor & 0x02)//0000 0010
	{//字符第1位为 1
		bit_array[startLocation + 6] = 1;
	}
	else
	{
		bit_array[startLocation + 6] = 0;
	}

	if (charactor & 0x01)//0000 0001
	{//字符第1位为 1
		bit_array[startLocation + 7] = 1;
	}
	else
	{
		bit_array[startLocation + 7] = 0;
	}
}

//将四个bit填到bit_array的startLocation开始的四个数组空间。
void MyMacPackage::fillWith(bool bit_0, bool bit_1, bool bit_2, bool bit_3, bool bit_array[], unsigned int startLocation)
{
	bit_array[startLocation] = bit_0;
	bit_array[startLocation + 1] = bit_1;
	bit_array[startLocation + 2] = bit_2;
	bit_array[startLocation + 3] = bit_3;
}

void MyMacPackage::setFillTo64(bool fillTo64)
{
	this->fillTo64 = fillTo64;
}

void MyMacPackage::enable_CRC_32(bool enableCRC_32)
{
	this->enableCRC_32 = enableCRC_32;
}

void MyMacPackage::appendFCS()
{
	const bool* result;
	if (enableCRC_32)	//如果启用CRC32来校验
	{
		result = crcCheckResult_32.getResult();
		for (unsigned int i = 0; i < 32; ++i) {
			bit_array[bit_array_length - FCS_length * 8 + i] =
				result[i];
		}
	}
	else				//启用CRC8来校验
	{
		
		result = crcCheckResult.getResult();

		//由于目前用到的是8位校验码，
		//先只填写FCS的前一个字节。
		for (unsigned int i = 0
			; i < 8; ++i)
		{
			bit_array[bit_array_length - FCS_length * 8 + i] =
				result[i];
		}
		//校验码需要4个字节，
		//前面的校验码只填了1个字节，
		//后面的三个字节用0来填。
		for (unsigned int i = bit_array_length - (FCS_length - 1) * 8;
			i < bit_array_length; ++i)
		{
			bit_array[i] = 0;
		}
	}
	
}


