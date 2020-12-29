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
		&hKey);//��ע���
	if (lRet == ERROR_SUCCESS)//�������ɹ�
	{
		dwSize = sizeof(tchData);
		lRet = RegQueryValueEx(
			hKey,
			L"ProcessorNameString",
			NULL,
			NULL,
			(LPBYTE)tchData,
			&dwSize
		);						//����򿪳ɹ������
		if (lRet == ERROR_SUCCESS)
		{
			printf("\n CPU INFO:");
			printf("%s\n", tchData);
		}
		//�����Ƕ�ȡʧ��
		else
		{
			printf("\nCPU INFO:");
			printf("UNKNOWN\n");
		}
	}
	//�����Ǵ�ʧ��
	else
	{
		printf("\n CPU INFO:");
		printf("UNKNOWN\n");
	}
	RegCloseKey(hKey);//ע�⣬����һ��Ҫ�ǵùرվ��
}