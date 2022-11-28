package com.hcl.jna;

import com.alibaba.fastjson.JSON;

import java.util.HashMap;

public class Test {
    public static void main(String[] args) {
        HashMap<String,String>mp = new HashMap<String,String>();
        mp.put("a","1");
        String str = JSON.toJSONString(mp);
        System.out.println(str);
        boolean ans = CLibrary.INSTANCE.sendTo("1","qx",str,"/engine/rest/areas","spare");
        System.out.println("调用返回值:"+ans);

    }
}
