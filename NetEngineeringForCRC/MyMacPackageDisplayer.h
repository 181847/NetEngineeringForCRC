#pragma once
class MyMacPackageDisplayer
{
protected:
	MyMacPackage* macPackage;

	bool showInHex;

	//分隔每两个16进制和每四个2进制之间的分隔符。
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
	//显示Mac帧中的数据
	void display();

	//设置是否用16进制显示，
	//16进制显示时，每两个数字显示为一组，
	//非16进制就是2进制显示，每4个数字显示为一组。
	void setShowInHex(bool showInHex);

	//显示以太网帧的头部同步控制信息。
	void showEtherHead();

	//显示Mac帧的头部，
	//即Mac帧的源地址和目的地址。
	void showMacHead();

	//显示Mac帧的数据长度,
	//注意这个长度不包含FCS的4字节。
	void showMacDataLength();

	//显示Mac帧的数据部分。
	void showMacData();

	//显示Mac帧的FCS校验码。
	void showMacFCS();

	//从bitArray的startLocation开始，
	//每四个数组元素识别为一个16进制数，
	//显示countNum个16进制数，
	//每显示两个16进制数就空一格，
	//不换行。
	void showHex(bool bitArray[], unsigned int startLocation,
		unsigned int countNum);

	//从bitArray的startLocation开始，
	//将读取到的4个数组元素变为16进制数，
	//输出到控制台上，
	//不换行。
	void showHex(bool bitArray[], unsigned int startLocation);

	//控制台换行。
	void nextLine();

	//控制台输出一个空格。
	void seperate();

	//从bitArray的startLocation开始，
	//每个数组元素视为一个字，
	//以每4个字为一个单位
	//显示countNum个单位的字，
	//每个单位之间空一格，
	//不换行。
	void showBit(bool bitArray[], unsigned int startLocation,
		unsigned int countNum);

	//从bitArray的startLocation开始，
	//将连续的四个元素以0和1的形式输出到控制台。
	void showBit(bool bitArray[], unsigned int startLocation);
};

