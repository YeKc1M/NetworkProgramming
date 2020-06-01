// CourseProject.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <Windows.h>
#include <wlanapi.h>
#include <objbase.h>
#include <wtypes.h>

#include <stdio.h>
#include <stdlib.h>

#pragma comment(lib, "wlanapi.lib")
#pragma comment(lib, "ole32.lib")

void testWlanAPI1()
{
    //initialize variables
    HANDLE hClient = NULL;
    DWORD dwMaxClient = 2;
    DWORD dwCurVersion = 0;
    DWORD dwResult = 0;
    DWORD dwRetVal = 0;
    int iRet = 0;
    WCHAR GuidString[40] = { 0 };
    unsigned int i, j, k;
    
    //variables used for WlanEnumInterfaces
    PWLAN_INTERFACE_INFO_LIST pIfList = NULL; //contain an array of NIC interface information(class PWLAN_INTERFACE_INFO)
    PWLAN_INTERFACE_INFO pIfInfo = NULL; //contain information about a wireless LAN interface
    //isState: WLAN_INTERFACE_STATE. value: wlan_interface_state_connected, wlan_interface_state_disconnected, wlan_interface_state_authenticating
    printf_s("Check wireless LAN Interfaces\n");
    dwResult = WlanOpenHandle(dwMaxClient, NULL, &dwCurVersion, &hClient); // open a connection to the server
    if (dwResult != ERROR_SUCCESS)
    {
        wprintf_s(L"WlanOpenHandle failed with error: %u\n", dwResult);
        return;
    }
    printf_s("WlanOpen success\n");
    dwResult = WlanEnumInterfaces(hClient, NULL, &pIfList);
    if (dwResult != ERROR_SUCCESS)
    {
        wprintf_s(L"WlanEnumInterfaces failed with error: %u\n", dwResult);
        return;
    }
    else
    {
        wprintf_s(L"Num Entries: %lu\n", pIfList->dwNumberOfItems);
        wprintf_s(L"Current Index: %lu\n", pIfList->dwIndex);
        for (i = 0; i < (int)pIfList->dwNumberOfItems; i++)
        {
            pIfInfo = (WLAN_INTERFACE_INFO*)&pIfList->InterfaceInfo[i];
            wprintf_s(L"Interface Index[%d]:\t%lu\n", i, i);
            iRet = StringFromGUID2(pIfInfo->InterfaceGuid, (LPOLESTR)&GuidString, 39);
            if (iRet == 0)
            {
                wprintf_s(L"StringFromGUID2 failed\n");
            }
            else
            {
                wprintf_s(L"InterfaceGUID[%d]:%ws\n", i, GuidString);
            }
            wprintf_s(L"Interface Description[%d]:%ws\n", i, pIfInfo->strInterfaceDescription);
            wprintf_s(L"Interface State[%d]:\t", i);
            switch (pIfInfo->isState)
            {
            case wlan_interface_state_not_ready:
                wprintf_s(L"Not ready\n");
                break;
            case wlan_interface_state_connected:
                wprintf_s(L"Connected\n");
                break;
            case wlan_interface_state_ad_hoc_network_formed:
                wprintf_s(L"First node in a ad hoc network");
                break;
            case wlan_interface_state_disconnecting:
                wprintf_s(L"Disconnecting\n");
                break;
            case wlan_interface_state_disconnected:
                wprintf_s(L"Not connected\n");
                break;
            case wlan_interface_state_associating:
                wprintf_s(L"Attemping to associate with a network\n");
                break;
            case wlan_interface_state_discovering:
                wprintf_s(L"Auto configuaration is discovering settings for the network\n");
                break;
            case wlan_interface_state_authenticating:
                wprintf_s(L"In process of authenticating\n");
                break;
            default:
                wprintf_s(L"Unknown state %ld\n", pIfInfo->isState);
                break;
            }
        }
    }
    if (pIfList != NULL)
    {
        WlanFreeMemory(pIfList);
        pIfList = NULL;
    }
}

int main()
{
    //printf_s("hello world!\n");
    testWlanAPI1();
    return 0;
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
