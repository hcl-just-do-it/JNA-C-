// pch.cpp: 与预编译标头对应的源文件
#include "httplib.h"
#include "pch.h"
#include "sm3.hpp"
#include "ip_mac_time.hpp"
#include <iostream>
#include <cstring>
#include <cmath>
using namespace std;





bool http_post(string biz_content,string api) {

    string ip = "192.168.0.130";
    int port = 8090;
    httplib::Client cli(ip, port);
    httplib::Headers headers;
    httplib::Params params;
    params.insert({ "access_key","ffxt" });
    params.insert({ "format","json" });
    params.insert({ "request_id","3fc89826ad5c4e8fbf40" });
    
    params.insert({ "version","1.0" });
    
    params.insert({ "timestamp","1553737749174" });
    params.insert({"sign","public_key"});
    params.insert({"biz_content",biz_content});
    cout<<"start send message!"<<endl;
    if (auto res = cli.Post(api,params)) {
        cout << res->status << endl;
        cout << res->get_header_value("Content-Type") << endl;
        cout << res->body << endl;
    }
    else {
        cout << "post fail, error code: " << res.error() << std::endl;
        return false;
    }

    return true;
}

const char* getVersion(){
    return "1.0";
}
bool sendTo(char* serviceCode,char *address, char *business, char *api ,char *spare){
    cout<<"address = "<<address<<" business = "<<business<<endl;
    string biz_content = getVersion();
    cout<<"version = "<<biz_content<<endl;
    string ipMacTime = getIpMacTime() ;
    string mingw = ipMacTime+ (string)address;
    biz_content += mingw;
    cout<<"mingw = "<<mingw<<endl;
    biz_content += sm3(mingw);
    biz_content+=business;
    cout<<"post body = "<<biz_content<<endl;
    return http_post(biz_content,api);
}



