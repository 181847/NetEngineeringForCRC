#include "stdafx.h"
#include "Tools.h"
using namespace std;

//0		非法控制命令
//1		代表退出消息							"Exit"
//2		代表显示Mac封装效果						"Show"
//3		代表设置源Mac地址						"SetSourceMac: "
//4		代表设置目的mac地址						"SetTargetMac: "
//5		代表设置Mac帧数据部分					"SetData: "
//6		代表设置Mac帧是否填充到64位				"FillTo64: " + "True"/"False"
//7		代表设置显示效果是16进制、还是2进制		"Mode: " + "Hex"/"Bin"
//8		代表启用CRC_32校验						"UseCRC_32: " + "True"/"False"
//9		代表显示帮助信息						"Help"
//command 用来放置指令，
//detail 用来存储指令中的详细消息，比如存储数据部分的字符串。
unsigned int analysis(char* command, char* detail)
{
	unsigned int loopPointer, findLocation;
	switch (command[0])
	{
		//退出消息	
	case 'E':
	case 'e':
		return 1;
		break;

		//设置Mac帧是否填充到64位	
	case 'F':
	case 'f':
		//找到‘:’以及空格之后的数组序号。
		findLocation = findDeclar(command);

		//没有找到正确的冒号位置时，返回0，
		//表示非法指令。
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

		//代表设置显示效果是16进制、还是2进制
	case 'M':
	case 'm':
		//找到‘:’以及空格之后的数组序号。
		findLocation = findDeclar(command);

		//没有找到正确的冒号位置时，返回0，
		//表示非法指令。
		if (!findLocation)
		{
			return 0;
		}

		switch (command[findLocation]) {
			//设置为16进制
		case 'H':
		case 'h':
			detail[0] = true;
			break;
			//设置为2进制
		case 'B':
		case 'b':
			detail[0] = false;
			break;
			//默认设为16进制
		default:
			detail[0] = true;
		}
		return 7;
		break;

	case 'S':
	case 's':
		switch (command[3])
		{
			//显示Mac封装效果	
		case 'W':
		case 'w':
			return 2;
			break;

			//设置源Mac地址
		case 'S':
		case 's':
			//找到‘:’以及空格之后的数组序号。
			findLocation = findDeclar(command);

			//没有找到正确的冒号位置时，返回0，
			//表示非法指令。
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
					//复制Mac地址
					detail[loopPointer - findLocation] =
						command[loopPointer];
				}//if
				else
				{
					//Mac地址未达到要求就结束，
					//mac地址设置失败。
					return 0;
				}//else
			}//for 复制Mac地址
			 //设置结尾符号。
			detail[12] = '\0';
			return 3;
			break;

			//设置目的Mac地址
		case 'T':
		case 't':
			//找到‘:’以及空格之后的数组序号。
			findLocation = findDeclar(command);

			//没有找到正确的冒号位置时，返回0，
			//表示非法指令。
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
					//复制Mac地址
					detail[loopPointer - findLocation] =
						command[loopPointer];
				}//if
				else
				{
					//Mac地址未达到要求就结束，
					//mac地址设置失败。
					return 0;
				}//else
			}//for 复制Mac地址
			 //设置结尾符号。
			detail[12] = '\0';
			return 4;
			break;

			//设置Mac帧数据部分
		case 'D':
		case 'd':
			//找到‘:’以及空格之后的数组序号。
			findLocation = findDeclar(command);

			//没有找到正确的冒号位置时，返回0，
			//表示非法指令。
			if (!findLocation)
			{
				return 0;
			}
			for (loopPointer = findLocation;
				command[loopPointer];			//直到指令的结尾
				++loopPointer)
			{
				detail[loopPointer - findLocation] =
					command[loopPointer];
			}//for
			 //设置结尾符号。
			detail[loopPointer - findLocation] = '\0';
			return 5;
			break;
		}//switch(command[3])
		break;

		//设置是否启用CRC_32来进行校验
	case 'U':
	case 'u':
		//找到‘:’以及空格之后的数组序号。
		findLocation = findDeclar(command);

		//没有找到正确的冒号位置时，返回0，
		//表示非法指令。
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

		//显示帮助信息
	case 'H':
	case 'h':
		return 9;
		break;

	default:
		return 0;
	}//switch(command[0])
	return 0;
}

//找到字符串中“:” + 空格之后的一个元素的序号，
//如果没有找到就返回0。
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
	cout << "按任意键退出程序" << endl;
}

//显示操作成功
void showSuccess()
{
	cout << endl << "操作成功" << endl << endl;
}

//显示未知指令
void showUnknownCommand()
{
	cout << endl << "未知指令！" << endl
		<< "请输入Help来获取帮助" << endl << endl;
}

//显示帮助信息
void showHelp()
{
	cout << endl << "帮助："
		<< "1.\"Exit\"\t\t\t\t退出程序。 " << endl
		<< "2.\"Show\"\t\t\t\t显示Mac封装效果。" << endl
		<< "3.\"SetSourceMac: \"\t\t\t\t设置源Mac地址" << endl
		<< "4.\"SetTargetMac: \"\t\t\t\t代表设置目的mac地址" << endl
		<< "5.\"SetData: \"\t\t\t\t设置Mac帧数据部分" << endl
		<< "6.\"FillTo64: \" + \"True\"或者\"False\" \t\t\t\t代表设置Mac帧是否填充到64位" << endl
		<< "7.\"Mode: \" + \"Hex\"或者\"Bin\"\t\t\t\t设置显示效果是16进制、还是2进制" << endl
		<< "8.\"UseCRC_32: \" + \"True\"或者\"False\" \t\t\t\t代表是否使用CRC_32来进行校验，如果选False，就会使用CRC_8。" << endl
		<< "9.\"Help\"\t\t\t\t显示帮助信息" << endl;
}

//计算字符串长度
unsigned int lengthOf(char* charArray)
{
	unsigned int length = 0;
	while (charArray[length])
	{
		++length;
	}
	return length;
}

//将original中的第一行字符复制到target中，
//将换行符替换成终止符。
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
		<< "******************** 以 太 网 帧 开始 ******************"
		<< endl;
}

void showEtherEnd()
{
	std::cout
		<< "******************** 以 太 网 帧 结束 ******************"
		<< endl << endl << endl;
}
