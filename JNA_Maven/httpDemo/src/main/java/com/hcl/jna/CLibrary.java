package com.hcl.jna;
import com.sun.jna.Library;
import com.sun.jna.Native;

import static com.sun.jna.Native.loadLibrary;

public interface CLibrary extends Library {
    CLibrary INSTANCE = loadLibrary("Secure_con_com(Windows).dll", com.hcl.jna.CLibrary.class);
    //CLibrary INSTANCE = loadLibrary("Secure_con_com.so", com.hcl.jna.CLibrary.class);
    boolean sendTo(String serviceCode,String address, String business,String api, String spare);
    // 函数是动态库中定义的， Windows下调dll，Linux下调so


}






