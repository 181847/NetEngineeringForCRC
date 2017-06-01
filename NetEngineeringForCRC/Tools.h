#pragma once
//0		非法控制命令
//1		代表退出消息							"Exit"
//2		代表显示Mac封装效果						"Show"
//3		代表设置源Mac地址						"SetSourceMac: "
//4		代表设置目的mac地址						"SetTargetMac: "
//5		代表设置Mac帧数据部分					"SetData: "
//6		代表设置Mac帧是否填充到64位				"FillTo64: " + "True"/"False"
//7		代表设置显示效果是16进制、还是2进制		"Mode: " + "Hex"/"Bin"
//8		代表显示帮助信息						"Help"
//command 用来放置指令，
//detail 用来存储指令中的详细消息，比如存储数据部分的字符串。
unsigned int analysis(char* command, char* detail);

//找到字符串中“:” + 空格之后的一个元素的序号，
//如果没有找到就返回0。
unsigned int findDeclar(char* command);

//显示退出信息
void showExit();

//显示操作成功
void showSuccess();

//显示未知指令
void showUnknownCommand();

//显示帮助信息
void showHelp();

//计算字符串长度
unsigned int lengthOf(char* charArray);

void convert_string_to_charArray(std::string original, char* target);
