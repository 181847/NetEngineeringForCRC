// NetEngineeringForCRC.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
using namespace std;


int main()
{
	bool data[] = { 0,0,0,0,1,0,0,1,1 };
	MYCRC_8 mycrc;
	mycrc.checkData(data, 9);
	mycrc.showAsBit();

	MyMacPackage newMacPack;;
	newMacPack.setSourceMac("");
	newMacPack.setTargetMac("");
	newMacPack.setData("");

	newMacPack.checkCRC();

	MyMacPackageDisplayer newDisplayer;
	newDisplayer = new MyMacPackageDisplayer(newMacPack);

	newDisplyer.refresh();

	getchar();
}



