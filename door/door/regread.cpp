#include<stdio.h>
#include<Windows.h>

void regread(void)
{
	long lRet;
	HKEY hKey;
	TCHAR tchData[64];
	DWORD dwSize;
	lRet = RegOpenKeyEx(
		HKEY_LOCAL_MACHINE,
		L"Hardware\\Description\\System\\CentralProcessor\\0",
		0,
		KEY_QUERY_VALUE,
		&hKey);//打开注册表
	if (lRet == ERROR_SUCCESS)//读操作成功
	{
		dwSize = sizeof(tchData);
		lRet = RegQueryValueEx(
			hKey,
			L"ProcessorNameString",
			NULL,
			NULL,
			(LPBYTE)tchData,
			&dwSize
		);						//如果打开成功，则读
		if (lRet == ERROR_SUCCESS)
		{
			printf("\n CPU INFO:");
			printf("%s\n", tchData);
		}
		//以下是读取失败
		else
		{
			printf("\nCPU INFO:");
			printf("UNKNOWN\n");
		}
	}
	//以下是打开失败
	else
	{
		printf("\n CPU INFO:");
		printf("UNKNOWN\n");
	}
	RegCloseKey(hKey);//注意，这里一定要记得关闭句柄
}