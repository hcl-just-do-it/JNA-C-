#pragma once

// 添加要在此处预编译的标头
#include "framework.h"

//定义宏
#ifdef IMPORT_DLL
#else
#define IMPORT_DLL extern "C" _declspec(dllimport) //指的是允许将其给外部调用。
#endif	//C和C++模块互相调用时，C++模块需要extern "C"。
		//__declspec(dllexport)的作用就是让编译器按照某种预定的方式来输出导出函数及变量的符号


IMPORT_DLL bool sendTo(char* serviceCode, char* address, char* business, char* api, char* spare);
