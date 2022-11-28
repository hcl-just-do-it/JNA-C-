#include "httplib.h"
#include "json.hpp"
#include <iostream>
#include <string>

using namespace std;
bool http_post(string ip, int port) {


	nlohmann::json biz_content;
	biz_content["pi"] = 3.141;
	biz_content["happy"] = true;
	biz_content["name"] = "Niels";

	string str = biz_content.dump();
	cout << str << endl;
	//auto j = nlohmann::json::parse(str);

	httplib::Client cli(ip, port);
	httplib::Params params;
	params.insert({ "access_key","spxtsms" });
	params.insert({ "format","json" });
	params.insert({ "request_id","1669358545219" });
	params.insert({ "sign","xxx" });
	params.insert({ "timestamp","1669358545219" });
	params.insert({ "version","1.0" });
	params.insert({ "biz_content",str });

	/*
	if (auto res = cli.Post("/engine/rest/areas", params)) {
		cout << res->status << endl;
		cout << res->get_header_value("Content-Type") << endl;
		cout << res->body << endl;
	}
	else {
		cout << "error code: " << res.error() << std::endl;
		return false;
	}
	*/


	return true;
}

int main() {
	http_post("192.168.0.130", 8090);
	return 0;
}