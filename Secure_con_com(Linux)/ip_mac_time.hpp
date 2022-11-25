#include <sys/time.h>
#include <string>
using namespace std;
string getTimeStamp()
{
       struct timeval tv;
    gettimeofday(&tv, NULL);
  return to_string(tv.tv_sec);
}

#include <iostream>
#include <set>
#include <map>
#include <cstring>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <unistd.h>

int getEthNames(set<string> &ethName)
{
    FILE *fp = NULL;
    char *p = NULL;
    char linebuf[512];
    char devname[128];
    string tmp;

    fp = fopen("/proc/net/dev", "r");
    if(fp == NULL)
    {
        return -1;
    }

    memset(linebuf, 0x00, sizeof(linebuf));
    memset(devname, 0x00, sizeof(devname));

    while(fgets(linebuf, 511, fp) != NULL)
    {
        p = strstr(linebuf, ":");
        if(p == NULL)
        {
            memset(linebuf, 0x00, sizeof(linebuf));
            continue;
        }

        p[0] = 0x00;

        memset(devname, 0x00, sizeof(devname));

        strncpy(devname, linebuf, 127);

        tmp = string(devname);
        tmp.erase(0, tmp.find_first_not_of(" "));
        tmp.erase(tmp.find_last_not_of(" ")+1);

        if(strncmp(tmp.c_str(), "lo", 2) != 0 )
        {
            if(strncmp(tmp.c_str(), "eth", 3) == 0 || strncmp(tmp.c_str(), "ens", 3) == 0 || \
                strncmp(tmp.c_str(), "enp", 3) == 0 || strncmp(tmp.c_str(), "en", 2) == 0)
            {
                ethName.insert(tmp);
            }
        }

        memset(linebuf, 0x00, sizeof(linebuf));
    }

    fclose(fp);

    return 0;
}

int getIPMACs(set<string> &ethName, map<string, pair<string, string>> &macs)
{
    set<string>::iterator it;
    struct ifreq ifr;
    struct sockaddr_in *sin;
    char ip_addr[30];
    char mac_addr[30];
    int sockfd = -1;
    int nRes = -1;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd < 0)
    {
        return -1;
    }

    for(it=ethName.begin(); it!=ethName.end(); it++)
    {
        nRes = -1;

        memset(ip_addr, 0x00, sizeof(ip_addr));
        memset(mac_addr, 0x00, sizeof(mac_addr));

        memset(&ifr, 0x00, sizeof(ifr));

        strcpy(ifr.ifr_name, (*it).c_str());

        nRes = ioctl(sockfd, SIOCGIFADDR, &ifr);
        if(nRes < 0)
        {
            strcpy(ip_addr, "");
        }
        else
        {
            sin = (struct sockaddr_in *)&ifr.ifr_addr;
            strcpy(ip_addr, inet_ntoa(sin->sin_addr));
        }

        nRes = ioctl(sockfd, SIOCGIFHWADDR, &ifr);
        if(nRes < 0)
        {
            strcpy(mac_addr, "00:00:00:00:00:00");
        }
        else
        {
            sprintf(mac_addr, "%02x:%02x:%02x:%02x:%02x:%02x",
                (unsigned char)ifr.ifr_hwaddr.sa_data[0],
                (unsigned char)ifr.ifr_hwaddr.sa_data[1],
                (unsigned char)ifr.ifr_hwaddr.sa_data[2],
                (unsigned char)ifr.ifr_hwaddr.sa_data[3],
                (unsigned char)ifr.ifr_hwaddr.sa_data[4],
                (unsigned char)ifr.ifr_hwaddr.sa_data[5]);
        }

        macs.insert(make_pair(string(mac_addr), make_pair(string(ifr.ifr_name), string(ip_addr))));
    }

    close(sockfd);

    return 0;
}


string getIpMacTime()
{
    set<string> eth;
    map<string, pair<string, string>> macs;
    map<string, pair<string, string>>::iterator it;

    getEthNames(eth);
    getIPMACs(eth, macs);

    string ans;
    for(it=macs.begin(); it!=macs.end(); it++)
    //it=macs.begin();
    {
        cout << (*it).first << endl;
       // cout << (*it).second.first << endl;
        cout << (*it).second.second << endl;
        ans = ans + (*it).second.second  + (*it).first;
    }
    cout<< "IpMac = " << ans <<endl;
    ans += getTimeStamp() ;
    return ans;
}


