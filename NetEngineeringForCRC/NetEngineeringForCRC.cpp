// NetEngineeringForCRC.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
using namespace std;


//��¼�Ǵ������С����
bool IS_BIG_ENDIAN;

inline void check_BIG_ENDIAN() {
	U_U16_CHAR4 transport;
	transport.C4.C0 = 0x80;

	if (transport.U16 == 0x80000000)
	{//�����
		IS_BIG_ENDIAN = true;
	}
	else if (transport.U16 == 0x00000080)
	{//С����
		IS_BIG_ENDIAN = false;
	}
}

int main()
{
	//����Ǵ������С����
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
		//���ڶ�ȡ����һ����һ�����з���
		//����һ���и��Ƶ�command�У��������з��滻����ֹ����
		convert_string_to_charArray(command_string, command);
		switch (analysis(command, detail))
		{
		case 1:
			showExit();
			exitFlag = 1;
			break;

			//��ʾ����
		case 2:
			std::cout << endl << endl
				<< "******************** M A C ֡ ��ʼ ******************" 
				<< endl;
			newMacPack->checkCRC();
			newDisplayer->display();
			std::cout 
				<< "******************** M A C ֡ ���� ******************"
				<< endl << endl << endl;
			break;

			//����ԴMac��ַ	
		case 3:
			newMacPack->setSourceMac(detail);
			showSuccess();
			break;

			//����Ŀ��mac��ַ	
		case 4:
			newMacPack->setTargetMac(detail);
			showSuccess();
			break;
			
			//����Mac֡���ݲ���	
		case 5:
			newMacPack->setData(detail, lengthOf(detail));
			showSuccess();
			break;

			//����Mac֡�Ƿ���䵽64λ
		case 6:
			newMacPack->setFillTo64(detail[0]);
			showSuccess();
			break;

			//������ʾЧ����16���ơ�����2����	
		case 7:
			newDisplayer->setShowInHex(detail[0]);
			showSuccess();
			break;

			//�Ƿ�����CRC32У��
		case 8:
			newMacPack->enable_CRC_32(detail[0]);
			showSuccess();
			break;

			//��ʾ������Ϣ
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


