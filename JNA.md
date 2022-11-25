# 动态库制作

```c++
生成动态库（Shared Object）
g++ -shared -fpic -o libmax4.so max.cpp 
配置库文件
sudo vi /etc/ld.so.conf.d/my.conf		//	/so文件所在目录路径
sudo ldconfig

    
解释如下
-fPIC 	表示告诉编译器生成位置无关代码，也就是这些代码可以在任意位置执行
-g	产生能被GNU调试器使用的调试信息，以调试程序
-Wall 	表示尽可能检查错误
-shared 	为链接库  让编译器知道是要编译一个共享库
 -L: 指定库所在的目录,-L.	在当前路径下寻找.so文件(相对或者绝对路径)
 -l: 指定库的名字，掐头 (lib) 去尾 (.so) 是动态库的名字，-lmax	要链接这个libmax.so文件
libmax.so	表示在当前路径下生成libmax.so文件
使用 extern “C” 告诉编译以 C 方式编译，否则会出现编译报错的问题（C++方式生成会导致函数名变化）
/etc/ld.so.conf.d/my.conf	配置环境变量
ldconfig	该命令会重建/etc/ld.so.cache文件
动态链接器搜索动态库的顺序（按优先级从高到低）：
1.可执行文件内部的 DT_RPATH 段
2.系统的环境变量 LD_LIBRARY_PATH
3.系统动态库的缓存文件 /etc/ld.so.cache
4.存储动态库 / 静态库的系统目录 /lib/, /usr/lib 等

Windows下用VS直接创建DLL项目，httplib库放在根目录下，同时项目属性里面添加C++的附加目录 ./ 。

```



# JNA调用动态库

```java
package com.hcl.jna;
import com.sun.jna.Library;
import static com.sun.jna.Native.loadLibrary;
public interface CLibrary extends Library {  
	/*有两种方式，一种是开源框架jna，一种是jdk自带的原生代码jni
	看见别人和自己碰到的bug如下：
    VS生成JDK位数一致的dll
    dependency里添加两个jna的jar包（maven项目里添加坐标也可）
    dll文件最好放在java.library.path（之一的jdk/bin下），resources目录下或者项目根目录下都行，只需要一个dll文件名，以及最好是引用绝对路径。
    Windows下VS需要勾选通用Windows开发和桌面C++开发
    Windows下，我64位电脑，VS必须生成X64位dll，jdk的32和64位都能用。X86生成的32位dll，jdk32位用不了。
    
    Linux和Windows下Java代码只需修改dll和so的文件名差异。
    */
    CLibrary INSTANCE = loadLibrary("Dll1.dll",CLibrary.class);
    public int max(int a, int b);//同动态库定义，数据类型注意匹配
}
```





# 不同平台代码的差异

ip_mac_time.hpp文件

可能有多个ip，mac时，合并成一个字符串。



