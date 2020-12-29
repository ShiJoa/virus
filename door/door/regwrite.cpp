#include<stdio.h>
#include<Windows.h>

void regwrite(void)
{
	//根键，子键名称和到子键的句柄
	HKEY hRoot = HKEY_LOCAL_MACHINE;
	LPWSTR szSubKey=(LPWSTR) L"Software\\Microsoft\\Windows\\CurrentVersion\\Run";
	HKEY hKey;//打开指定子键
	DWORD dwDisposition = REG_OPENED_EXISTING_KEY;
	//如果不存在就创建
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
	//得到当前执行文件的文件名（包含路径）
	LPWSTR szModule=NULL;
	GetModuleFileName(NULL, szModule, MAX_PATH);
	//创建一个新的键值，设置键值数据为文件名
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
	//关闭子键句柄
	RegCloseKey(hKey);
}