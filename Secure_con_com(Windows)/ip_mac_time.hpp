#pragma once
#include <WinSock2.h>
#include <Iphlpapi.h>
#include <iostream>
#include <string>

using namespace std;
#pragma comment(lib,"Iphlpapi.lib") //��Ҫ���Iphlpapi.lib��


string getTimeStamp() {
    time_t tt;
    time(&tt);
    return to_string(tt);
}

string getIpMac() {
    string ipmac;
    //PIP_ADAPTER_INFO�ṹ��ָ��洢����������Ϣ
    PIP_ADAPTER_INFO pIpAdapterInfo = new IP_ADAPTER_INFO();
    //�õ��ṹ���С,����GetAdaptersInfo����
    unsigned long stSize = sizeof(IP_ADAPTER_INFO);
    //����GetAdaptersInfo����,���pIpAdapterInfoָ�����;����stSize��������һ��������Ҳ��һ�������
    int nRel = GetAdaptersInfo(pIpAdapterInfo, &stSize);
    //��¼��������
    DWORD netCardNum = 0;
    GetNumberOfInterfaces(&netCardNum);
    if (ERROR_BUFFER_OVERFLOW == nRel)
    {
        //����������ص���ERROR_BUFFER_OVERFLOW
        //��˵��GetAdaptersInfo�������ݵ��ڴ�ռ䲻��,ͬʱ�䴫��stSize,��ʾ��Ҫ�Ŀռ��С
        //��Ҳ��˵��ΪʲôstSize����һ��������Ҳ��һ�������
        //�ͷ�ԭ�����ڴ�ռ�
        delete pIpAdapterInfo;
        //���������ڴ�ռ������洢����������Ϣ
        pIpAdapterInfo = (PIP_ADAPTER_INFO)new BYTE[stSize];
        //�ٴε���GetAdaptersInfo����,���pIpAdapterInfoָ�����
        nRel = GetAdaptersInfo(pIpAdapterInfo, &stSize);
    }
    if (ERROR_SUCCESS == nRel)
    {
        //���������Ϣ
        //�����ж�����,���ͨ��ѭ��ȥ�ж�
        while (pIpAdapterInfo)
        {
            char mac[256] = { 0 };
            char ip[256] = { 0 };
            //���������ж�IP,���ͨ��ѭ��ȥ�ж�
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
    //�ͷ��ڴ�ռ�
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