php扩展 全局变量适用于高并发抢购、秒杀等,致力于做工具类，其他的正在开发中
也适合开发php扩展的人读源码，很多写法我都注释了
===================================
###使用方法如下：
            首先安装php扩展zqf.so
            phpize来安装
            然后在php文件调用
            dl('zqf.so');或者phpini里加载
            $obj=new zqf();
            $counter= $obj->autoadd(0,1,0);（声明只针对多线程）
            echo $counter;
### 有什么问题可以及时联系我 qieangel@hotmail.com
