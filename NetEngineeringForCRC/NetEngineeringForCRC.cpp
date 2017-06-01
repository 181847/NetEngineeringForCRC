// NetEngineeringForCRC.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
using namespace std;


//记录是大端序还是小端序
bool IS_BIG_ENDIAN;

inline void check_BIG_ENDIAN() {
	U_U16_CHAR4 transport;
	transport.C4.C0 = 0x80;

	if (transport.U16 == 0x80000000)
	{//大端序
		IS_BIG_ENDIAN = true;
	}
	else if (transport.U16 == 0x00000080)
	{//小端序
		IS_BIG_ENDIAN = false;
	}
}

int main()
{
	//检查是大端序还是小端序
	check_BIG_ENDIAN();

	MyMacPackage* newMacPack = new MyMacPackage();

	newMacPack->setSourceMac("A402B9B3FCE0");
	newMacPack->setTargetMac("A402B9B3FCE0");
	newMacPack->setData("0123", 4);
	newMacPack->setFillTo64(false);
	newMacPack->enable_CRC_32(true);
	newMacPack->checkCRC();

	MyMacPackageDisplayer* newDisplayer;
	newDisplayer = new MyMacPackageDisplayer(newMacPack);

	newDisplayer->setShowInHex(true);
	newDisplayer->display();

	newMacPack->enable_CRC_32(false);
	newMacPack->checkCRC();
	newDisplayer->display();

	unsigned int exitFlag = 0;
	string command_string;
	char command[200];
	char detail[100];
	do
	{
		getline(cin, command_string);
		//由于读取到的一行有一个换行符，
		//将这一整行复制到command中，并将换行符替换成终止符。
		convert_string_to_charArray(command_string, command);
		switch (analysis(command, detail))
		{
		case 1:
			showExit();
			exitFlag = 1;
			break;

			//显示操作
		case 2:
			std::cout << endl << endl
				<< "******************** M A C 帧 开始 ******************" 
				<< endl;
			newMacPack->checkCRC();
			newDisplayer->display();
			std::cout 
				<< "******************** M A C 帧 结束 ******************"
				<< endl << endl << endl;
			break;

			//设置源Mac地址	
		case 3:
			newMacPack->setSourceMac(detail);
			showSuccess();
			break;

			//设置目的mac地址	
		case 4:
			newMacPack->setTargetMac(detail);
			showSuccess();
			break;
			
			//设置Mac帧数据部分	
		case 5:
			newMacPack->setData(detail, lengthOf(detail));
			showSuccess();
			break;

			//设置Mac帧是否填充到64位
		case 6:
			newMacPack->setFillTo64(detail[0]);
			showSuccess();
			break;

			//设置显示效果是16进制、还是2进制	
		case 7:
			newDisplayer->setShowInHex(detail[0]);
			showSuccess();
			break;

			//是否启用CRC32校验
		case 8:
			newMacPack->enable_CRC_32(detail[0]);
			showSuccess();
			break;

			//显示帮助信息
		case 9:
			showHelp();
			break;

		case 0:
		default:
			showUnknownCommand();
			break;
		}
	} while (exitFlag != 1);


	delete newDisplayer;
	delete newMacPack;

	getchar();
}


