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
	std::cout << "以太网帧头部：\n";
	if (showInHex) {
		//一行显示4个字节，显示8个16进制数，每两个空一格
		showHex(etherHead, 0, 8);
		nextLine();
		showHex(etherHead, 32, 8);
		nextLine();
	}
	else
	{
		for (int i = 0; i < 4; ++i)
		{
			//一行显示两个字节，每四个字为一个单位，显示4个单位
			showBit(etherHead, i * 16, 4);
			nextLine();
		}
	}
}

void MyMacPackageDisplayer::showMacHead()
{
	std::cout << "Mac帧头部：\n";
	if (showInHex)
	{
		//源Mac地址
		showHex(macPackage->bit_array, 0, 12);
		nextLine();
		//目标Mac地址
		showHex(macPackage->bit_array, 12 * 4, 12);
		nextLine();
	}
	else
	{
		//源Mac地址
		showBit(macPackage->bit_array, 0, 12);
		nextLine();
		//目标Mac地址
		showBit(macPackage->bit_array, 12 * 4, 12);
		nextLine();
	}
}

void MyMacPackageDisplayer::showMacDataLength()
{
	std::cout << "Mac帧数据部分长度/类型：\n";
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
	std::cout << "Mac帧数据字段：\n";
	std::cout << ("是否填充数据，来保证Mac帧长度不小于64：")
		<< (macPackage->fillTo64 ? "是" : "否")
		<< std::endl;

	//开始输出的字的位置。
	unsigned int startLocation = (12 + 2) * 8;

	//数据部分字节长度，
	//这个变量用于存储还未显示完的数据字节。
	unsigned int dataLength = macPackage->dataLength;

	//每行的字节数
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
	std::cout << "FCS校验和：\n";
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

		//i为奇数表明当前已经显示了偶数个16进制数，
		//现在空一格。
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
