#pragma once
//0		�Ƿ���������
//1		�����˳���Ϣ							"Exit"
//2		������ʾMac��װЧ��						"Show"
//3		��������ԴMac��ַ						"SetSourceMac: "
//4		��������Ŀ��mac��ַ						"SetTargetMac: "
//5		��������Mac֡���ݲ���					"SetData: "
//6		��������Mac֡�Ƿ���䵽64λ				"FillTo64: " + "True"/"False"
//7		����������ʾЧ����16���ơ�����2����		"Mode: " + "Hex"/"Bin"
//8		������ʾ������Ϣ						"Help"
//command ��������ָ�
//detail �����洢ָ���е���ϸ��Ϣ������洢���ݲ��ֵ��ַ�����
unsigned int analysis(char* command, char* detail);

//�ҵ��ַ����С�:�� + �ո�֮���һ��Ԫ�ص���ţ�
//���û���ҵ��ͷ���0��
unsigned int findDeclar(char* command);

//��ʾ�˳���Ϣ
void showExit();

//��ʾ�����ɹ�
void showSuccess();

//��ʾδָ֪��
void showUnknownCommand();

//��ʾ������Ϣ
void showHelp();

//�����ַ�������
unsigned int lengthOf(char* charArray);

void convert_string_to_charArray(std::string original, char* target);
