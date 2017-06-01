#include "stdafx.h"
#include "Tools.h"
using namespace std;

//0		�Ƿ���������
//1		�����˳���Ϣ							"Exit"
//2		������ʾMac��װЧ��						"Show"
//3		��������ԴMac��ַ						"SetSourceMac: "
//4		��������Ŀ��mac��ַ						"SetTargetMac: "
//5		��������Mac֡���ݲ���					"SetData: "
//6		��������Mac֡�Ƿ���䵽64λ				"FillTo64: " + "True"/"False"
//7		����������ʾЧ����16���ơ�����2����		"Mode: " + "Hex"/"Bin"
//8		��������CRC_32У��						"UseCRC_32: " + "True"/"False"
//9		������ʾ������Ϣ						"Help"
//command ��������ָ�
//detail �����洢ָ���е���ϸ��Ϣ������洢���ݲ��ֵ��ַ�����
unsigned int analysis(char* command, char* detail)
{
	unsigned int loopPointer, findLocation;
	switch (command[0])
	{
		//�˳���Ϣ	
	case 'E':
	case 'e':
		return 1;
		break;

		//����Mac֡�Ƿ���䵽64λ	
	case 'F':
	case 'f':
		//�ҵ���:���Լ��ո�֮���������š�
		findLocation = findDeclar(command);

		//û���ҵ���ȷ��ð��λ��ʱ������0��
		//��ʾ�Ƿ�ָ�
		if (!findLocation)
		{
			return 0;
		}

		switch (command[findLocation])
		{
		case 'T':
		case 't':
		case '1':
			detail[0] = true;
			break;
		default:
			detail[0] = false;
		}
		return 6;
		break;

		//����������ʾЧ����16���ơ�����2����
	case 'M':
	case 'm':
		//�ҵ���:���Լ��ո�֮���������š�
		findLocation = findDeclar(command);

		//û���ҵ���ȷ��ð��λ��ʱ������0��
		//��ʾ�Ƿ�ָ�
		if (!findLocation)
		{
			return 0;
		}

		switch (command[findLocation]) {
			//����Ϊ16����
		case 'H':
		case 'h':
			detail[0] = true;
			break;
			//����Ϊ2����
		case 'B':
		case 'b':
			detail[0] = false;
			break;
			//Ĭ����Ϊ16����
		default:
			detail[0] = true;
		}
		return 7;
		break;

	case 'S':
	case 's':
		switch (command[3])
		{
			//��ʾMac��װЧ��	
		case 'W':
		case 'w':
			return 2;
			break;

			//����ԴMac��ַ
		case 'S':
		case 's':
			//�ҵ���:���Լ��ո�֮���������š�
			findLocation = findDeclar(command);

			//û���ҵ���ȷ��ð��λ��ʱ������0��
			//��ʾ�Ƿ�ָ�
			if (!findLocation)
			{
				return 0;
			}

			for (loopPointer = findLocation;
				loopPointer < findLocation + 12;
				++loopPointer)
			{
				if (command[loopPointer])
				{
					//����Mac��ַ
					detail[loopPointer - findLocation] =
						command[loopPointer];
				}//if
				else
				{
					//Mac��ַδ�ﵽҪ��ͽ�����
					//mac��ַ����ʧ�ܡ�
					return 0;
				}//else
			}//for ����Mac��ַ
			 //���ý�β���š�
			detail[12] = '\0';
			return 3;
			break;

			//����Ŀ��Mac��ַ
		case 'T':
		case 't':
			//�ҵ���:���Լ��ո�֮���������š�
			findLocation = findDeclar(command);

			//û���ҵ���ȷ��ð��λ��ʱ������0��
			//��ʾ�Ƿ�ָ�
			if (!findLocation)
			{
				return 0;
			}

			for (loopPointer = findLocation;
				loopPointer < findLocation + 12;
				++loopPointer)
			{
				if (command[loopPointer])
				{
					//����Mac��ַ
					detail[loopPointer - findLocation] =
						command[loopPointer];
				}//if
				else
				{
					//Mac��ַδ�ﵽҪ��ͽ�����
					//mac��ַ����ʧ�ܡ�
					return 0;
				}//else
			}//for ����Mac��ַ
			 //���ý�β���š�
			detail[12] = '\0';
			return 4;
			break;

			//����Mac֡���ݲ���
		case 'D':
		case 'd':
			//�ҵ���:���Լ��ո�֮���������š�
			findLocation = findDeclar(command);

			//û���ҵ���ȷ��ð��λ��ʱ������0��
			//��ʾ�Ƿ�ָ�
			if (!findLocation)
			{
				return 0;
			}
			for (loopPointer = findLocation;
				command[loopPointer];			//ֱ��ָ��Ľ�β
				++loopPointer)
			{
				detail[loopPointer - findLocation] =
					command[loopPointer];
			}//for
			 //���ý�β���š�
			detail[loopPointer - findLocation] = '\0';
			return 5;
			break;
		}//switch(command[3])
		break;

		//�����Ƿ�����CRC_32������У��
	case 'U':
	case 'u':
		//�ҵ���:���Լ��ո�֮���������š�
		findLocation = findDeclar(command);

		//û���ҵ���ȷ��ð��λ��ʱ������0��
		//��ʾ�Ƿ�ָ�
		if (!findLocation)
		{
			return 0;
		}

		switch (command[findLocation])
		{
		case 'T':
		case 't':
		case '1':
			detail[0] = true;
			break;
		default:
			detail[0] = false;
		}
		return 8;
		break;

		//��ʾ������Ϣ
	case 'H':
	case 'h':
		return 9;
		break;

	default:
		return 0;
	}//switch(command[0])
	return 0;
}

//�ҵ��ַ����С�:�� + �ո�֮���һ��Ԫ�ص���ţ�
//���û���ҵ��ͷ���0��
unsigned int findDeclar(char* command)
{
	for (int checkPointer = 0; command[checkPointer]; ++checkPointer)
	{
		if (command[checkPointer] == ':'
			&& command[checkPointer + 1] == ' ')
		{
			return checkPointer + 2;
		}
	}

	return 0;
}

void showExit()
{
	cout << "��������˳�����" << endl;
}

//��ʾ�����ɹ�
void showSuccess()
{
	cout << endl << "�����ɹ�" << endl << endl;
}

//��ʾδָ֪��
void showUnknownCommand()
{
	cout << endl << "δָ֪�" << endl
		<< "������Help����ȡ����" << endl << endl;
}

//��ʾ������Ϣ
void showHelp()
{
	cout << endl << "������"
		<< "1.\"Exit\"\t\t\t\t�˳����� " << endl
		<< "2.\"Show\"\t\t\t\t��ʾMac��װЧ����" << endl
		<< "3.\"SetSourceMac: \"\t\t\t\t����ԴMac��ַ" << endl
		<< "4.\"SetTargetMac: \"\t\t\t\t��������Ŀ��mac��ַ" << endl
		<< "5.\"SetData: \"\t\t\t\t����Mac֡���ݲ���" << endl
		<< "6.\"FillTo64: \" + \"True\"����\"False\" \t\t\t\t��������Mac֡�Ƿ���䵽64λ" << endl
		<< "7.\"Mode: \" + \"Hex\"����\"Bin\"\t\t\t\t������ʾЧ����16���ơ�����2����" << endl
		<< "8.\"UseCRC_32: \" + \"True\"����\"False\" \t\t\t\t�����Ƿ�ʹ��CRC_32������У�飬���ѡFalse���ͻ�ʹ��CRC_8��" << endl
		<< "9.\"Help\"\t\t\t\t��ʾ������Ϣ" << endl;
}

//�����ַ�������
unsigned int lengthOf(char* charArray)
{
	unsigned int length = 0;
	while (charArray[length])
	{
		++length;
	}
	return length;
}

//��original�еĵ�һ���ַ����Ƶ�target�У�
//�����з��滻����ֹ����
void convert_string_to_charArray(string original, char * target)
{
	unsigned int checkPointer = 0;
	for (; original[checkPointer] != '\n' && original[checkPointer] != '\0'; ++checkPointer)
	{
		target[checkPointer] = original[checkPointer];
	}
	target[checkPointer] = '\0';
}

void showEtherStart()
{

	std::cout << endl << endl
		<< "******************** �� ̫ �� ֡ ��ʼ ******************"
		<< endl;
}

void showEtherEnd()
{
	std::cout
		<< "******************** �� ̫ �� ֡ ���� ******************"
		<< endl << endl << endl;
}
