php扩展 全局变量适用于高并发抢购、秒杀等,致力于做工具类，其他的正在开发中
也适合开发php扩展的人读源码，很多写法我都注释了
===================================
###高并发计数器使用方法如下：
            首先安装php扩展zqf.so
            phpize来安装
            然后在php文件调用
            dl('zqf.so');或者phpini里加载
            $obj=new zqf();
            $counter= $obj->autoadd(0,1,0);（声明只针对多线程）
            echo $counter;
###查找数组重复元素使用方法如下：
            $arr=array(10,20,4,12,69,1,90,56,23,12,89,78);
            $obj=new zqf();
            $result= $obj->findrepetition($arr);查找$arr重复项算法
            var_dump($result);//结果是Array ( [3] => 12 [9] => 12 )
###二分法查找数组元素使用方法如下：
            $arr=array(10,20,4,12,69,1,90,56,23,12,89,78);
            $obj=new zqf();
            $result= $obj->findval($arrs,69);二分法快速查找$arr里的元素69，c底层会给数据进行排序
            var_dump($result);//结果是Array ( [8] => 69 [result] => Array ( [0] => 1 [1] => 4 [2] => 10 [3] => 12 [4] => 12 [5] => 20 [6] => 23 [7] => 56 [8] => 69 [9] => 78 [10] => 89 [11] => 90 ) )
### 有什么问题可以及时联系我 qieangel@hotmail.com
