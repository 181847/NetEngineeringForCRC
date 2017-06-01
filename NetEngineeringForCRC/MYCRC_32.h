#pragma once
class MYCRC_32
{
protected:
	bool buffer[32];
	const bool checkBuffer[32] =
	{
		false, false, false, false,  false, true, false, false,
		true, true, false, false,  false, false, false, true,
		false, false, false, true,  true, true, false, true,
		true, false, true, true,  false, true, true, true
	};
public:
	MYCRC_32();
	~MYCRC_32();

	/**
	* 为data中的数据进行检查，得到的校验码将会存在buffer中。
	*/
	void checkData(bool* data, int bitLength);

	//左移buffer中的数据一位，
	//末尾的数据由data[checkPointer + 32]来不足，
	//如果checkPointer + 32 >= bitLength，
	//就补false。
	void leftMove(int checkPointer, bool* data, int bitLength);

	//buffer中存储的32位与对比数组进行异或运算,
	//由于最高位的1被省去，
	//这里只需要后面的32位运算。
	void compareWithCheckerBuffer();

	const bool * getResult();
};

