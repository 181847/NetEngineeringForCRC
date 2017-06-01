#include "stdafx.h"
#include "MyMacPackageDisplayer.h"


MyMacPackageDisplayer::MyMacPackageDisplayer(MyMacPackage* macPackage)
{
	this->macPackage = macPackage;
}


MyMacPackageDisplayer::~MyMacPackageDisplayer()
{
}

void MyMacPackageDisplayer::display()
{
	showEtherHead();
	nextLine();
	showMacHead();
	nextLine();
	showMacDataLength();
	nextLine();
	showMacData();
	nextLine();
	showMacFCS();
	nextLine();
}

void MyMacPackageDisplayer::setShowInHex(bool showInHex)
{
	this->showInHex = showInHex;
}

void MyMacPackageDisplayer::showEtherHead()
{
	std::cout << "��̫��֡ͷ����\n";
	if (showInHex) {
		//һ����ʾ4���ֽڣ���ʾ8��16��������ÿ������һ��
		showHex(etherHead, 0, 8);
		nextLine();
		showHex(etherHead, 32, 8);
		nextLine();
	}
	else
	{
		for (int i = 0; i < 4; ++i)
		{
			//һ����ʾ�����ֽڣ�ÿ�ĸ���Ϊһ����λ����ʾ4����λ
			showBit(etherHead, i * 16, 4);
			nextLine();
		}
	}
}

void MyMacPackageDisplayer::showMacHead()
{
	std::cout << "Mac֡ͷ����\n";
	if (showInHex)
	{
		//ԴMac��ַ
		showHex(macPackage->bit_array, 0, 12);
		nextLine();
		//Ŀ��Mac��ַ
		showHex(macPackage->bit_array, 12 * 4, 12);
		nextLine();
	}
	else
	{
		//ԴMac��ַ
		showBit(macPackage->bit_array, 0, 12);
		nextLine();
		//Ŀ��Mac��ַ
		showBit(macPackage->bit_array, 12 * 4, 12);
		nextLine();
	}
}

void MyMacPackageDisplayer::showMacDataLength()
{
	std::cout << "Mac֡���ݲ��ֳ���/���ͣ�\n";
	if (showInHex)
	{
		showHex(macPackage->bit_array, 12 * 8, 4);
	}
	else
	{
		showBit(macPackage->bit_array, 12 * 8, 4);
	}
	nextLine();
}

void MyMacPackageDisplayer::showMacData()
{
	std::cout << "Mac֡�����ֶΣ�\n";
	std::cout << ("�Ƿ�������ݣ�����֤Mac֡���Ȳ�С��64��")
		<< (macPackage->fillTo64 ? "��" : "��")
		<< std::endl;

	//��ʼ������ֵ�λ�á�
	unsigned int startLocation = (12 + 2) * 8;

	//���ݲ����ֽڳ��ȣ�
	//����������ڴ洢��δ��ʾ��������ֽڡ�
	unsigned int dataLength = macPackage->dataLength;

	//ÿ�е��ֽ���
	unsigned int bytePerLine = 4;
	if (showInHex)
	{
		while (dataLength > 0)
		{
			if (dataLength > bytePerLine)
			{
				showHex(macPackage->bit_array, startLocation, bytePerLine * 2);
				dataLength -= bytePerLine;
				startLocation += bytePerLine * 8;
			}
			else
			{
				showHex(macPackage->bit_array, startLocation, dataLength * 2);
				dataLength = 0;
			}
			nextLine();
		}
	}
	else
	{
		bytePerLine = 2;

		while (dataLength > 0)
		{
			if (dataLength > bytePerLine)
			{
				showBit(macPackage->bit_array, startLocation, bytePerLine * 2);
				dataLength -= bytePerLine;
				startLocation += bytePerLine * 8;
			}
			else
			{
				showBit(macPackage->bit_array, startLocation, dataLength * 2);
				dataLength = 0;
			}
			nextLine();
		}
	}
}

void MyMacPackageDisplayer::showMacFCS()
{
	std::cout << "FCSУ��ͣ�\n";
	unsigned int startLocation = macPackage->bit_array_length;
	unsigned int FCS_length = macPackage->FCS_length;
	startLocation -= FCS_length * 8;
	if (showInHex)
	{
		showHex(macPackage->bit_array, startLocation, FCS_length * 2);
	}
	else
	{
		showBit(macPackage->bit_array, startLocation, FCS_length * 2);
	}
}

void MyMacPackageDisplayer::showHex(bool bitArray[], unsigned int startLocation, unsigned int countNum)
{
	for (unsigned int i = 0; i < countNum; ++i)
	{
		showHex(bitArray, startLocation + i * 4);

		//iΪ����������ǰ�Ѿ���ʾ��ż����16��������
		//���ڿ�һ��
		if (i % 2 == 1)
		{
			seperate();
		}
	}
}

void MyMacPackageDisplayer::showHex(bool bitArray[], unsigned int startLocation)
{
	unsigned int num = 0;
	num += ( bitArray[startLocation] ? 8 : 0 );
	num += (bitArray[startLocation + 1] ? 4 : 0);
	num += (bitArray[startLocation + 2] ? 2 : 0);
	num += (bitArray[startLocation + 3] ? 1 : 0);

	std::cout <<
		(char)(num < 10 ?
			'0' + num : 'A' + num - 10);
}

void MyMacPackageDisplayer::nextLine()
{
	std::cout << std::endl;
}

void MyMacPackageDisplayer::seperate()
{
	std::cout << seperator;
}

void MyMacPackageDisplayer::showBit(bool bitArray[], unsigned int startLocation,
	unsigned int countNum)
{
	for (unsigned int i = 0; i < countNum; ++i) {
		showBit(bitArray, startLocation + i * 4);

		seperate();
	}
}

void MyMacPackageDisplayer::showBit(bool bitArray[], unsigned int startLocation)
{
	std::cout << (bitArray[startLocation] ? 1 : 0)
		<< (bitArray[startLocation + 1] ? 1 : 0)
		<< (bitArray[startLocation + 2] ? 1 : 0)
		<< (bitArray[startLocation + 3] ? 1 : 0);
}
