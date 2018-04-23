### php扩展zqf （兼容php7）
	    全局变量适用于高并发抢购、秒杀，红包生成，数组算法处理等,由于添加了二维码生成功能
	    安装本扩展之前需要安装libqrencode
	    依赖安装方法如下：
            wget http://fukuchi.org/works/qrencode/qrencode-3.4.4.tar.gz
            tar zxvf qrencode-3.4.4.tar.gz
            cd qrencode-3.4.4/
            ./configure
            make && make install
            如果没有安装libpng和libgd，也需要安装
            安装方法如下：
            sudo apt-get install libpng-dev
            sudo apt-get install libgd-dev
            致力于做工具类，其他的正在开发中
	    zqf扩展安装（兼容php7）
	    首先下载源码git clone https://github.com/qieangel2013/zqf.git或者composer安装
	    然后cd到当前目录/usr/local/php/bin/phpize
	    ./configure --with-php-config=/usr/local/php/bin/php-config
	    make && make install
	    make过程中如果出现
	    error: expected ‘=’, ‘,’, ‘;’, ‘asm’ or ‘__attribute__’ before ‘qrcode_png’
	    /home/zqf-master/zqf.c: In function ‘zim_zqf_savefile’:
	    /home/zqf-master/zqf.c:525: error: ‘gdImagePtr’ undeclared (first use in this function)
	    /home/zqf-master/zqf.c:525: error: (Each undeclared identifier is reported only once
	    /home/zqf-master/zqf.c:525: error: for each function it appears in.)
	    /home/zqf-master/zqf.c:525: error: expected ‘;’ before ‘im’
	    /home/zqf-master/zqf.c:571: error: ‘im’ undeclared (first use in this function)
	    说明没有安装gd库
	    yum install gd-devel
	    然后重新make && make install
	    修改php.ini添加extension=zqf.so
	    重启php-fpm
===================================
### 红包生成算法（拼手气红包和普通红包）
            $obj=new zqf();
            第一个参数是红包总额，第二个人参数红包数量，第三个参数默认代表拼手气红包，设置为1的话为普通红包
            拼手气红包
            $hongb= $obj->hongbao(10,8);或者$hongb= $obj->hongbao(10,8,0);返回数组为Array ( [0] => 1.33 [1] => 1.02 [2] => 1.28 [3] => 0.44 [4] => 1.37 [5] => 0.81 [6] => 1.81 [7] => 1.94 )
            普通红包，每个人数额一样设置第三个参数
            $hongb= $obj->hongbao(10,8,1);返回数组为Array ( [0] => 1.25 [1] => 1.25 [2] => 1.25 [3] => 1.25 [4] => 1.25 [5] => 1.25 [6] => 1.25 [7] => 1.25 )
            var_dump($hongb);
### 高并发计数器使用方法如下：
            首先安装php扩展zqf.so
            phpize来安装
            然后在php文件调用
            dl('zqf.so');或者phpini里加载
            $obj=new zqf();
            $counter= $obj->autoadd(0,1,0);（声明只针对多线程）
            echo $counter;
### 数组快速排序使用方法如下：
            $asd=array(23,1,21,4,19,89,200,1,78,3,4,7,1,0,88);
            $obj=new zqf();
            $quick= $obj->quicksort($asd);
            print_r($quick);Array ( [0] => 0 [1] => 1 [2] => 1 [3] => 1 [4] => 3 [5] => 4 [6] => 4 [7] => 7 [8] => 19 [9] => 21 [10] => 23 [11] => 78 [12] => 88 [13] => 89 [14] => 200 )
### 查找数组重复元素使用方法如下：
            $arr=array(10,20,4,12,69,1,90,56,23,12,89,78);
            $obj=new zqf();
            $result= $obj->findrepetition($arr);查找$arr重复项算法
            var_dump($result);//结果是Array ( [3] => 12 [9] => 12 )
### 二分法查找数组元素使用方法如下：
            $arr=array(10,20,4,12,69,1,90,56,23,12,89,78);
            $obj=new zqf();
            $result= $obj->findval($arr,69);二分法快速查找$arr里的元素69，c底层会给数据进行排序
            var_dump($result);//结果是Array ( [8] => 69 [result] => Array ( [0] => 1 [1] => 4 [2] => 10 [3] => 12 [4] => 12 [5] => 20 [6] => 23 [7] => 56 [8] => 69 [9] => 78 [10] => 89 [11] => 90 ) )
### 二维码生成使用方法如下：
            $obj=new zqf();
            $obj->savefile('https://www.baidu.com/s?wd=昌平香堂','./test.png',500);第一个参数是url，第二参数是保存路径，第三个参数是二维码长或者宽
            生成透明二维码：
             $obj->savefile('https://www.baidu.com/s?wd=昌平香堂','./test.png',500,1);第四个参数默认不生成透明，要想生成透明得传一个参数
	     生成带有logo的二维码：
	     $obj->savefile('https://www.baidu.com/s?wd=昌平香堂','./test.png',500,0,"./logo.png");第五个参数是logo的路径，现在只支持png格式的logo图片
### 和phpqrcode对比
	php-qrencode代码:
	<?php
	$t1 = microtime(true);
	$obj=new zqf();
	$obj->savefile('https://www.baidu.com/s?wd=昌平香堂','./test.png',500);
	$t2 = microtime(true);
	echo (($t2-$t1)*1000).':ms';
	?>
	
	运行时间:0.60701370239258:ms
	
	phpqrcode代码:

	<?php
	include('./phpqrcode/phpqrcode.php'); 
	$t1 = microtime(true);
	QRcode::png("https://www.baidu.com/s?wd=昌平香堂",'./test.png',QR_ECLEVEL_Q,500);
	$t2 = microtime(true);
	echo (($t2-$t1)*1000).':ms';
	?>
	运行时间:23.189067840576:ms
### 项目地址
	github：https://github.com/qieangel2013/zqf
	oschina：https://gitee.com/qieangel2013/zqf
### 交流使用
	交流群：337937322
### 如果你对我的辛勤劳动给予肯定，请给我捐赠，你的捐赠是我最大的动力
![](https://github.com/qieangel2013/zys/blob/master/public/images/pw.jpg)
![](https://github.com/qieangel2013/zys/blob/master/public/images/pay.png)
[项目捐赠列表](https://github.com/qieangel2013/zys/wiki/%E9%A1%B9%E7%9B%AE%E6%8D%90%E8%B5%A0)
