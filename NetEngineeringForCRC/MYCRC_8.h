#pragma once
class MYCRC_8
{
protected:
	bool buffer[8];
	const bool checkBuffer[8] = 
		{ false, false, false, false, false, true, true, true };
	
	//G（X）=X8+X2+X1+1,第九位的true被省去。
public:
	MYCRC_8();
	~MYCRC_8();
	/**
	* 为data中的数据进行检查，得到的校验码将会存在buffer中。
	*/
	void checkData(bool* data, int bitLength);

	//左移buffer中的数据一位，
	//末尾的数据由data[checkPointer + 8]来不足，
	//如果checkPointer + 8 >= bitLength，
	//就补false。
	void leftMove(int checkPointer, bool* data, int bitLength);

	//buffer中存储的8位与对比数组进行异或运算,
	//由于最高位的1被省去，
	//这里只需要后面的8位运算。
	void compareWithCheckerBuffer();

	//以01比特流的形式将检验码输出到控制台上，
	void showAsBit();

	const bool * getResult();
};