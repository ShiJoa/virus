#include<stdio.h>
#include<Windows.h>

void regwrite(void)
{
	//�������Ӽ����ƺ͵��Ӽ��ľ��
	HKEY hRoot = HKEY_LOCAL_MACHINE;
	LPWSTR szSubKey=(LPWSTR) L"Software\\Microsoft\\Windows\\CurrentVersion\\Run";
	HKEY hKey;//��ָ���Ӽ�
	DWORD dwDisposition = REG_OPENED_EXISTING_KEY;
	//��������ھʹ���
	LONG lRet = RegCreateKeyEx(
		hRoot,
		szSubKey,
		0,
		NULL,
		REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS,
		NULL,
		&hKey,
		&dwDisposition
	);
	if (lRet != ERROR_SUCCESS)
		return;
	//�õ���ǰִ���ļ����ļ���������·����
	LPWSTR szModule=NULL;
	GetModuleFileName(NULL, szModule, MAX_PATH);
	//����һ���µļ�ֵ�����ü�ֵ����Ϊ�ļ���
	lRet = RegSetValueEx(
		hKey,
		L"SelfRunDemo",
		0,
		REG_SZ,
		(BYTE*)szModule,
		wcslen(szModule)
	);
	if (lRet == ERROR_SUCCESS)
	{
		printf("self run success\n");
	}
	//�ر��Ӽ����
	RegCloseKey(hKey);
}