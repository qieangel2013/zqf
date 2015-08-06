php扩展 全局变量适用于高并发抢购、秒杀等
===================================
###使用方法如下：
            首先安装php扩展zqf.so
            phpize来安装
            然后在php文件调用（声明只针对多线程）
            dl('zqf.so');或者phpini里加载
            $counter=zqf(0,1,0);
            echo $counter;
### 有什么问题可以及时联系我 qieangel@hotmail.com
