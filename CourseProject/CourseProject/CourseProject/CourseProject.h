#pragma once

#include "resource.h"

#include <Windows.h>
#include <wlanapi.h>
#include <objbase.h>
#include <wtypes.h>
#include <math.h>

#include <stdio.h>
#include <stdlib.h>

#pragma comment(lib, "wlanapi.lib")
#pragma comment(lib, "ole32.lib")

void wifi_detect(double* parr)
{
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

    //variables for WlanGetAvailableNetworkList
    PWLAN_AVAILABLE_NETWORK_LIST pBssList = NULL;
    PWLAN_AVAILABLE_NETWORK pBssEntry = NULL;
    int iRSSI = 0;

    //check wireless LAN interfaces
    dwResult = WlanOpenHandle(dwMaxClient, NULL, &dwCurVersion, &hClient);
    if (dwResult != ERROR_SUCCESS)
    {
        //wprintf_s(L"WlanOpenHandle failed with error: %u\n", dwResult);
        return;
    }
    //printf_s("WlanOpen success\n");
    dwResult = WlanEnumInterfaces(hClient, NULL, &pIfList);
    if (dwResult != ERROR_SUCCESS)
    {
        //wprintf_s(L"WlanEnumInterfaces failed with error: %u\n", dwResult);
        return;
    }
    else
    {
        if (pIfList->dwNumberOfItems < 1)
        {
            throw "no available wlan interface detected.";
        }
        //detect available wifi
        pIfInfo = (WLAN_INTERFACE_INFO*)&pIfList->InterfaceInfo[0];
        dwResult = WlanGetAvailableNetworkList(hClient, &pIfInfo->InterfaceGuid, 0, NULL, &pBssList);
        if (dwResult != ERROR_SUCCESS)
        {
            //wprintf_s(L"WlanGetAvailableNetworkList failed with error: %u\n", dwResult);
            dwRetVal = 1;
        }
        else
        {
            if (pBssList->dwNumberOfItems < 3)
            {
                throw "available wifi less than 3.";
            }
            else
            {
                for (int j = 0; j < 3; j++)
                {
                    pBssEntry = (WLAN_AVAILABLE_NETWORK*)&pBssList->Network[j];
                    iRSSI = 0;
                    if (pBssEntry->wlanSignalQuality == 0) iRSSI = -100;
                    else if (pBssEntry->wlanSignalQuality == 100) iRSSI = -50;
                    else iRSSI = -100 + (pBssEntry->wlanSignalQuality / 2);
                    double y = -(iRSSI + 50) / 20;
                    parr[j] = pow(10, y);
                }
            }
        }
    }
}