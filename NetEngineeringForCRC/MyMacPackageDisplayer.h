#pragma once
class MyMacPackageDisplayer
{
protected:
	MyMacPackage* macPackage;

	bool showInHex;

	//�ָ�ÿ����16���ƺ�ÿ�ĸ�2����֮��ķָ�����
	const char seperator = ' ';
	bool etherHead[64]=
		{1, 0, 1, 0, 1, 0, 1, 0, 
		1, 0, 1, 0, 1, 0, 1, 0,
		1, 0, 1, 0, 1, 0, 1, 0,
		1, 0, 1, 0, 1, 0, 1, 0,
		1, 0, 1, 0, 1, 0, 1, 0,
		1, 0, 1, 0, 1, 0, 1, 0,
		1, 0, 1, 0, 1, 0, 1, 0,
		1, 0, 1, 0, 1, 0, 1, 1};
	const unsigned int bitSize = 8;
public:
	MyMacPackageDisplayer(MyMacPackage* macPackage);
	~MyMacPackageDisplayer();
	//��ʾMac֡�е�����
	void display();

	//�����Ƿ���16������ʾ��
	//16������ʾʱ��ÿ����������ʾΪһ�飬
	//��16���ƾ���2������ʾ��ÿ4��������ʾΪһ�顣
	void setShowInHex(bool showInHex);

	//��ʾ��̫��֡��ͷ��ͬ��������Ϣ��
	void showEtherHead();

	//��ʾMac֡��ͷ����
	//��Mac֡��Դ��ַ��Ŀ�ĵ�ַ��
	void showMacHead();

	//��ʾMac֡�����ݳ���,
	//ע��������Ȳ�����FCS��4�ֽڡ�
	void showMacDataLength();

	//��ʾMac֡�����ݲ��֡�
	void showMacData();

	//��ʾMac֡��FCSУ���롣
	void showMacFCS();

	//��bitArray��startLocation��ʼ��
	//ÿ�ĸ�����Ԫ��ʶ��Ϊһ��16��������
	//��ʾcountNum��16��������
	//ÿ��ʾ����16�������Ϳ�һ��
	//�����С�
	void showHex(bool bitArray[], unsigned int startLocation,
		unsigned int countNum);

	//��bitArray��startLocation��ʼ��
	//����ȡ����4������Ԫ�ر�Ϊ16��������
	//���������̨�ϣ�
	//�����С�
	void showHex(bool bitArray[], unsigned int startLocation);

	//����̨���С�
	void nextLine();

	//����̨���һ���ո�
	void seperate();

	//��bitArray��startLocation��ʼ��
	//ÿ������Ԫ����Ϊһ���֣�
	//��ÿ4����Ϊһ����λ
	//��ʾcountNum����λ���֣�
	//ÿ����λ֮���һ��
	//�����С�
	void showBit(bool bitArray[], unsigned int startLocation,
		unsigned int countNum);

	//��bitArray��startLocation��ʼ��
	//���������ĸ�Ԫ����0��1����ʽ���������̨��
	void showBit(bool bitArray[], unsigned int startLocation);
};

