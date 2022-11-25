package com.hcl.jna;

public class Test {
    public static void main(String[] args) {
        boolean ans = CLibrary.INSTANCE.sendTo("1","qx","business Info","/engine/rest/orgSync","spare");
        System.out.println("调用返回值:"+ans);


    }
    /**
     * 1. 方式一
     * 从当前的类加载器的getResourcesAsStream来获取
     * InputStream inputStream = this.getClass().getResourceAsStream(name)
     */


}
