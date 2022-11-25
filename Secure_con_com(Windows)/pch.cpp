
#pragma once
#include "httplib.h"
#include "pch.h"
#include "sm3.hpp"
#include "ip_mac_time.hpp"

#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <time.h>

using namespace std;




string sm3(string str) {
    cout << "加密之前： " + str << endl;
    cout << endl;
    string paddingValue = padding(str);
    // for (int i = 0; i < paddingValue.size() / 64; i++) {
    // 	for (int j = 0; j < 8; j++) {
    // 		cout << paddingValue.substr(i * 64 + j * 8, 8) << "  ";
    // 	}
    // 	cout << endl;
    // }
    // cout << endl;
    string result = iteration(paddingValue);
    cout << "加密之后：" << endl;
    for (int i = 0; i < 8; i++) {
        cout << result.substr(i * 8, 8) << "  ";
    }
    cout << endl;
    return result;
}


bool http_post(string biz_content, string api) {

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
    params.insert({ "sign","public_key" });
    params.insert({ "biz_content",biz_content });
    cout << "start send message!" << endl;
    if (auto res = cli.Post(api, params)) {
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

const char* getVersion() {
    return "1.0";
}
bool sendTo(char* serviceCode, char* address, char* business, char* api, char* spare) {
    cout << "address = " << address << " business = " << business << endl;
    string biz_content = getVersion();
    cout << "version = " << biz_content << endl;
    string ipMacTime = getIpMacTime();
    string mingw = ipMacTime + (string)address;
    biz_content += mingw;
    cout << "mingw = " << mingw << endl;
    biz_content += sm3(mingw);
    biz_content += business;
    cout << "post body = " << biz_content << endl;
    return http_post(biz_content, api);
}



