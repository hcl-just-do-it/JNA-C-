#pragma once
#include <WinSock2.h>
#include <Iphlpapi.h>
#include <iostream>
#include <string>

using namespace std;
#pragma comment(lib,"Iphlpapi.lib") //需要添加Iphlpapi.lib库


string getTimeStamp() {
    time_t tt;
    time(&tt);
    return to_string(tt);
}

string getIpMac() {
    string ipmac;
    //PIP_ADAPTER_INFO结构体指针存储本机网卡信息
    PIP_ADAPTER_INFO pIpAdapterInfo = new IP_ADAPTER_INFO();
    //得到结构体大小,用于GetAdaptersInfo参数
    unsigned long stSize = sizeof(IP_ADAPTER_INFO);
    //调用GetAdaptersInfo函数,填充pIpAdapterInfo指针变量;其中stSize参数既是一个输入量也是一个输出量
    int nRel = GetAdaptersInfo(pIpAdapterInfo, &stSize);
    //记录网卡数量
    DWORD netCardNum = 0;
    GetNumberOfInterfaces(&netCardNum);
    if (ERROR_BUFFER_OVERFLOW == nRel)
    {
        //如果函数返回的是ERROR_BUFFER_OVERFLOW
        //则说明GetAdaptersInfo参数传递的内存空间不够,同时其传出stSize,表示需要的空间大小
        //这也是说明为什么stSize既是一个输入量也是一个输出量
        //释放原来的内存空间
        delete pIpAdapterInfo;
        //重新申请内存空间用来存储所有网卡信息
        pIpAdapterInfo = (PIP_ADAPTER_INFO)new BYTE[stSize];
        //再次调用GetAdaptersInfo函数,填充pIpAdapterInfo指针变量
        nRel = GetAdaptersInfo(pIpAdapterInfo, &stSize);
    }
    if (ERROR_SUCCESS == nRel)
    {
        //输出网卡信息
        //可能有多网卡,因此通过循环去判断
        while (pIpAdapterInfo)
        {
            char mac[256] = { 0 };
            char ip[256] = { 0 };
            //可能网卡有多IP,因此通过循环去判断
            IP_ADDR_STRING* pIpAddrString = &(pIpAdapterInfo->IpAddressList);
            do
            {
                snprintf(ip, sizeof(ip), "%s", pIpAddrString->IpAddress.String);
                if (!strcmp(pIpAddrString->IpAddress.String, "0.0.0.0")) {
                    pIpAddrString = pIpAddrString->Next;
                    continue;
                }
                ipmac += (string)ip;
                pIpAddrString = pIpAddrString->Next;
            } while (pIpAddrString);
            if (!strcmp(ip, "0.0.0.0")) {
                pIpAdapterInfo = pIpAdapterInfo->Next;
                continue;
            }
            for (DWORD i = 0; i < pIpAdapterInfo->AddressLength; i++) {
                int r2 = snprintf(mac + i * 2, sizeof(ipmac), "%02X", pIpAdapterInfo->Address[i]);
            }
            cout << "ip = " << ip << endl;
            cout << "mac = " << mac << endl;
            ipmac += (string)mac;
            pIpAdapterInfo = pIpAdapterInfo->Next;
            cout << endl;
        }
    }
    //释放内存空间
    if (pIpAdapterInfo)
    {
        delete pIpAdapterInfo;
    }
    cout << "ipmac = " << ipmac << endl;
    return ipmac;
}

string getIpMacTime() {
    return getIpMac() + getTimeStamp();
}