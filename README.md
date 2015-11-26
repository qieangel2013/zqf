###php扩展zqf 
            全局变量适用于高并发抢购、秒杀，数组算法处理等,由于添加了二维码生成功能，安装本扩展之前需要安装libqrencode，
            安装方法如下：
            wget http://fukuchi.org/works/qrencode/qrencode-3.4.4.tar.gz
            tar zxvf qrencode-3.4.4.tar.gz
            cd qrencode-3.4.4/
            ./configure
            make&make install
            如果没有安装libpng和libgd，也需要安装
            安装方法如下：
            sudo apt-get install libpng-dev
            sudo apt-get install libgd-dev
            致力于做工具类，其他的正在开发中
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
            $result= $obj->findval($arr,69);二分法快速查找$arr里的元素69，c底层会给数据进行排序
            var_dump($result);//结果是Array ( [8] => 69 [result] => Array ( [0] => 1 [1] => 4 [2] => 10 [3] => 12 [4] => 12 [5] => 20 [6] => 23 [7] => 56 [8] => 69 [9] => 78 [10] => 89 [11] => 90 ) )
###二维码生成使用方法如下：
            $obj=new zqf();
            $obj->savefile('https://www.baidu.com/s?wd=昌平香堂','./test.png',500);第一个参数是url，第二参数是保存路径，第三个参数是二维码长或者宽
            生成透明二维码：
             $obj->savefile('https://www.baidu.com/s?wd=昌平香堂','./test.png',500,1);第四个参数默认不生成透明，要想生成透明得传一个参数
### 有什么问题可以及时联系我 qieangel@hotmail.com
