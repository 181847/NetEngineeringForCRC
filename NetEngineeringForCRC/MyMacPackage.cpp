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

//����ԴMac��ַ��ʹ��12λ16��������ʾ
void MyMacPackage::setSourceMac(const char source[13])
{
	strcpy(sourceMac, source);
}

void MyMacPackage::setTargetMac(const char target[13])
{
	strcpy(targetMac, target);
}

//�������ݲ��ֵ��ֽڣ�ÿ���ַ���ʾһ���ֽڵ�����
//dataLength
//		�ַ��ĳ��ȡ�
void MyMacPackage::setData(const char data[], const unsigned int dataLength)
{
	if (dataLength < 0) {
		return;
	}

	this->originalDataLength = dataLength;
	this->dataLength = dataLength;
	//��¼����
	for (unsigned int i = 0; i < dataLength; ++i)
	{
		this->data[i] = data[i];
	}
}

//��ԴMac��ַ��Ŀ��Mac��ַ �Լ� ���ݲ��֣�
//ȫ������ɶ�������ʽ����bit_array�����У�
//����ʧ�ܷ���0���ɹ�����1.
int MyMacPackage::checkCRC()
{
	//������Mac��ַ�����ݲ��֣������ ��bit_array�����С�
	fillbit_array();

	//����У���
	crcCheckResult.checkData(bit_array, bit_array_length - FCS_length * 8);

	crcCheckResult_32.checkData(bit_array, bit_array_length - FCS_length * 8);

	appendFCS();

	return 1;
}

//������Mac��ַ�����ݲ��ֵ����ݣ�������֣�bit������ʽ��
//�浽bit_array�����У�����Ϊbit_array���·�������ռ�
void MyMacPackage::fillbit_array()
{
	//������Mac��ַת����bit����
	translate_hex_to_bit(sourceMac, 12, bit_array, 0);
	translate_hex_to_bit(targetMac, 12, bit_array, 6 * 8);

	//�����ݲ���ת�����֣�bit������ʽ������bit_array������
	translate_char_to_bit(data, dataLength, bit_array, (12 + 2) * 8);

	//������ݲ��ֵĳ���С��46��
	//����Ҫ��֤Mac֡��������Ϊ64��
	if (originalDataLength < 46 && fillTo64) {
		for (int i = (12 + 2 + originalDataLength) * 8; i < 60 * 8; ++i)
		{//ע������4�ֽ���FCSУ����
			bit_array[i] = false;
		}
		//�޸����ݲ��ֵĳ���Ϊ46.
		dataLength = 46;
	}
	else
	{
		dataLength = originalDataLength;
	}

	bit_array_length = 12 * 8	//����Mac��ַ���ֳ���
		+ 2 * 8					//Mac�����ֶ�
		+ dataLength * 8		//�����ֶγ���
		+ FCS_length * 8;			//У��ͳ���

	//��Mac֡���ݲ��ֵĳ��ȣ���16λ�����ƴ浽bit_array������
	translate_uint_to_16bit(dataLength,
		bit_array, 12 * 8);
}

//����hexChar�洢���Ǳ�ʾ16�������ݵ����֣�
//����Щ���ַ�����֣�bit������ʽ��
//��bit_array������startLocationλ�ÿ�ʼ���bit���ݡ�
void MyMacPackage::translate_hex_to_bit(const char hexChar[], unsigned int hex_length, bool bit_array[], unsigned int startLocation)
{
	for (unsigned int i = 0; i < hex_length; ++i)
	{
		translate_hex_to_bit(hexChar[i], bit_array, startLocation + i * 4 );
	}
}

//��16���Ƶ��ַ�ת����bit��ʽ�浽bit_array��startLocationλ�á�
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

//���޷�������ת�����ֽ���ʽ��
void MyMacPackage::translate_uint_to_16bit(unsigned int number, bool bit_array[], unsigned int startLocation)
{
	//׼����ȡ�޷�������
	U_U16_CHAR4 transport;
	transport.U16 = number;
	if (IS_BIG_ENDIAN)
	{
		//�����
		translate_char_to_bit(transport.C4.C2, bit_array, startLocation);
		translate_char_to_bit(transport.C4.C3, bit_array, startLocation + 8);
	}
	else
	{
		//С����
		translate_char_to_bit(transport.C4.C1, bit_array, startLocation);
		translate_char_to_bit(transport.C4.C0, bit_array, startLocation + 8);
	}
}

//���ַ���ȫ��ת����bit���bit_array�����С�
void MyMacPackage::translate_char_to_bit(const char string[], unsigned int string_length, bool bit_array[], unsigned int startLocation)
{
	for (unsigned int i = 0; i < string_length; ++i)
	{
		translate_char_to_bit(string[i], bit_array, startLocation + i * 8);
	}
}

//���ַ�ת����bit���bit_array�����С�
void MyMacPackage::translate_char_to_bit(const char charactor, bool bit_array[], unsigned int startLocation)
{
	if (charactor & 0x80)//1000 0000
	{//�ַ���1λΪ 1
		bit_array[startLocation] = 1;
	}
	else
	{
		bit_array[startLocation] = 0;
	}

	if (charactor & 0x40)//0100 0000
	{//�ַ���1λΪ 1
		bit_array[startLocation + 1] = 1;
	}
	else
	{
		bit_array[startLocation + 1] = 0;
	}

	if (charactor & 0x20)//0010 0000
	{//�ַ���1λΪ 1
		bit_array[startLocation + 2] = 1;
	}
	else
	{
		bit_array[startLocation + 2] = 0;
	}

	if (charactor & 0x10)//0001 0000
	{//�ַ���1λΪ 1
		bit_array[startLocation + 3] = 1;
	}
	else
	{
		bit_array[startLocation + 3] = 0;
	}

	if (charactor & 0x08)//0000 1000
	{//�ַ���1λΪ 1
		bit_array[startLocation + 4] = 1;
	}
	else
	{
		bit_array[startLocation + 4] = 0;
	}

	if (charactor & 0x04)//0000 0100
	{//�ַ���1λΪ 1
		bit_array[startLocation + 5] = 1;
	}
	else
	{
		bit_array[startLocation + 5] = 0;
	}

	if (charactor & 0x02)//0000 0010
	{//�ַ���1λΪ 1
		bit_array[startLocation + 6] = 1;
	}
	else
	{
		bit_array[startLocation + 6] = 0;
	}

	if (charactor & 0x01)//0000 0001
	{//�ַ���1λΪ 1
		bit_array[startLocation + 7] = 1;
	}
	else
	{
		bit_array[startLocation + 7] = 0;
	}
}

//���ĸ�bit�bit_array��startLocation��ʼ���ĸ�����ռ䡣
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
	if (enableCRC_32)	//�������CRC32��У��
	{
		result = crcCheckResult_32.getResult();
		for (unsigned int i = 0; i < 32; ++i) {
			bit_array[bit_array_length - FCS_length * 8 + i] =
				result[i];
		}
	}
	else				//����CRC8��У��
	{
		
		result = crcCheckResult.getResult();

		//����Ŀǰ�õ�����8λУ���룬
		//��ֻ��дFCS��ǰһ���ֽڡ�
		for (unsigned int i = 0
			; i < 8; ++i)
		{
			bit_array[bit_array_length - FCS_length * 8 + i] =
				result[i];
		}
		//У������Ҫ4���ֽڣ�
		//ǰ���У����ֻ����1���ֽڣ�
		//����������ֽ���0���
		for (unsigned int i = bit_array_length - (FCS_length - 1) * 8;
			i < bit_array_length; ++i)
		{
			bit_array[i] = 0;
		}
	}
	
}


