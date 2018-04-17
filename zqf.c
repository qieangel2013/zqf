/*
  +----------------------------------------------------------------------+
  | PHP Version 5                                                        |
  +----------------------------------------------------------------------+
  | Copyright (c) 1997-2015 The PHP Group                                |
  +----------------------------------------------------------------------+
  | This source file is subject to version 3.01 of the PHP license,      |
  | that is bundled with this package in the file LICENSE, and is        |
  | available through the world-wide-web at the following url:           |
  | http://www.php.net/license/3_01.txt                                  |
  | If you did not receive a copy of the PHP license and are unable to   |
  | obtain it through the world-wide-web, please send a note to          |
  | license@php.net so we can mail you a copy immediately.               |
  +----------------------------------------------------------------------+
  | Author:    zqf  904208360@qq.com                                                          |
  +----------------------------------------------------------------------+
*/

/* $Id$ */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#include <gd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "php.h"
#include "php_ini.h"
#include "ext/standard/info.h"
#include "php_zqf.h"
#include <qrencode.h>
#define ZQF_RES_NAME "zqf_resource"
#define gdImageCreate gdImageCreate
#define gdImagePng gdImagePng
#define gdImageDestroy gdImageDestroy
#define gdImageColorAllocate gdImageColorAllocate
#define gdImageColorAllocateAlpha gdImageColorAllocateAlpha
#define gdImageFill gdImageFill
#define gdImageFilledRectangle gdImageFilledRectangle
#define gdImageCopyResampled  gdImageCopyResampled
#define gdImageCreateFromPng  gdImageCreateFromPng
#define gdImageTrueColorToPalette  gdImageTrueColorToPalette
#define INT_MAX 2147483647   
#define E_MAX   255 
/* If you declare any globals in php_zqf.h uncomment this:
ZEND_DECLARE_MODULE_GLOBALS(zqf)
*/
ZEND_DECLARE_MODULE_GLOBALS(zqf)
/* True global resources - no need for thread safety here */
static int le_zqf;
zend_class_entry *zqf_ce;
typedef struct _qrencode {
    QRcode *code;
}qrencode;
ZEND_BEGIN_ARG_INFO_EX(zqf_autoadd_arginfo, 0, 0, 1)
    ZEND_ARG_INFO(0,zqfjishu)
    ZEND_ARG_INFO(0,zqfsort)
    ZEND_ARG_INFO(0,is_zqfsets)
ZEND_END_ARG_INFO()
ZEND_BEGIN_ARG_INFO_EX(zqf_savefile_arginfo, 0, 0, 1)
    ZEND_ARG_INFO(0, str)
    ZEND_ARG_INFO(0, path)
    ZEND_ARG_INFO(0, size)
    ZEND_ARG_INFO(0, is_tr)
    ZEND_ARG_INFO(0, logopath)
    ZEND_ARG_INFO(0, level)
    ZEND_ARG_INFO(0, hint)
    ZEND_ARG_INFO(0, red)
    ZEND_ARG_INFO(0, green)
    ZEND_ARG_INFO(0, blue)
ZEND_END_ARG_INFO()
ZEND_BEGIN_ARG_INFO_EX(zqf_findrepetition_arginfo, 0, 0, 1)
    ZEND_ARG_INFO(0,zqf_arr)
ZEND_END_ARG_INFO()
ZEND_BEGIN_ARG_INFO_EX(zqf_findval_arginfo, 0, 0, 1)
    ZEND_ARG_INFO(0,zqfarr)
    ZEND_ARG_INFO(0,zqfval)
ZEND_END_ARG_INFO()
ZEND_BEGIN_ARG_INFO_EX(zqf_hongbao_arginfo, 0, 0, 1)
    ZEND_ARG_INFO(0,zqfmoney)
    ZEND_ARG_INFO(0,zqfcount)
    ZEND_ARG_INFO(0,zqftype)
ZEND_END_ARG_INFO()
ZEND_BEGIN_ARG_INFO_EX(zqf_quicksort_arginfo, 0, 0, 1)
    ZEND_ARG_INFO(0,zqf_arr)
ZEND_END_ARG_INFO()

static void php_zqf_init_globals(zend_zqf_globals *zqf_globals)
{
    zqf_globals->zqfflag = 0;
}
/*static void qrencode_dtor(zend_rsrc_list_entry *rsrc TSRMLS_DC) {
    qrencode *q = (qrencode *)rsrc->ptr;
    if (q->code != NULL) {
        //QRcode_free(q->code);
        q->code = NULL;
    }
    efree(q);
} 
/* }}} */

/** {{{ PHP_INI
 */
/*PHP_INI_BEGIN()
	STD_PHP_INI_ENTRY("zqfbase","0", PHP_INI_ALL, OnUpdateLong, zqfbase, zend_zqf_globals, zqf_globals)
	STD_PHP_INI_ENTRY("zqftype","0", PHP_INI_ALL, OnUpdateLong, zqftype, zend_zqf_globals, zqf_globals)
PHP_INI_END();*/







/* {{{ PHP_INI
 */
/* Remove comments and fill if you need to have entries in php.ini
PHP_INI_BEGIN()
    STD_PHP_INI_ENTRY("zqf.global_value",      "42", PHP_INI_ALL, OnUpdateLong, global_value, zend_zqf_globals, zqf_globals)
    STD_PHP_INI_ENTRY("zqf.global_string", "foobar", PHP_INI_ALL, OnUpdateString, global_string, zend_zqf_globals, zqf_globals)
PHP_INI_END()
*/
/* }}} */

/* Remove the following function when you have successfully modified config.m4
   so that your module can be compiled into PHP, it exists only for testing
   purposes. */

/* Every user-visible function in PHP should document itself in the source */
/* {{{ proto string confirm_zqf_compiled(string arg)
   Return a string to confirm that the module is compiled in */
/* }}} */
/* The previous line is meant for vim and emacs, so it can correctly fold and 
   unfold functions in source code. See the corresponding marks just before 
   function definition, where the functions purpose is also documented. Please 
   follow this convention for the convenience of others editing your code.
*/


/* {{{ php_zqf_init_globals
 */
/* Uncomment this function if you have INI entries
static void php_zqf_init_globals(zend_zqf_globals *zqf_globals)
{
	zqf_globals->global_value = 0;
	zqf_globals->global_string = NULL;
}
*/
/* }}} */

/* {{{ PHP_MINIT_FUNCTION
 */

int my_rand(int min, int max)
{
    static int _seed = 0;
    assert(max > min);

    if (_seed == 0)
    {
        _seed = time(NULL);
        srand(_seed);
    }
    int _rand = rand();
    _rand = min + (int) ((double) ((double) (max) - (min) + 1.0) * ((_rand) / ((RAND_MAX) + 1.0)));
    return _rand;
}
/* }}} */

/* {{{ PHP_MINFO_FUNCTION
 */
/*红包简单算法*/
PHP_METHOD(zqf,hongbao)
{
  zval *zqfmoney;
  double moneyss;
  long zqfcount;
  long zqftype=0;
  const double min=0.01;
  double safe_total;
  double moneys;
  int i;
  char buf[10];
  char* pEnd;
  if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "zl|l", &zqfmoney,&zqfcount,&zqftype) == FAILURE) {
      php_error_docref(NULL TSRMLS_CC, E_WARNING, "参数不正确!!!");
        RETURN_FALSE;
    }
    switch(Z_TYPE_P(zqfmoney)){
      case IS_LONG:
        moneyss=(double)Z_LVAL_P(zqfmoney);
        break;
      case IS_DOUBLE:
        moneyss=((int)Z_DVAL_P(zqfmoney)*100)/100.0;
       break;
      default:
        php_error_docref(NULL TSRMLS_CC, E_WARNING, "参数不正确!!!");
        RETURN_FALSE;
        break;
    }
    array_init(return_value);
     if(zqftype){
        moneys=((int)(moneyss*100/zqfcount))/100.0;
        for (i = 0; i < zqfcount; ++i)
       {
       	  sprintf(buf, "%.2f", moneys);
	        sscanf(buf, "%f", &moneys);
#if PHP_MAJOR_VERSION <7
          add_index_string(return_value,i,buf,1);
#else
          add_index_string(return_value,i,buf);
#endif
          moneys=strtof(buf, &pEnd);
          memset(buf,0,sizeof(buf));
        }
    }else{
      for (i = 1; i < zqfcount; ++i)
    {
      safe_total=(moneyss-(zqfcount-i)*min)/(zqfcount-i);
      moneys=my_rand((int)(min*100),(int)(safe_total*100))/100.0;
      moneyss -=moneys;
      sprintf(buf, "%.2f", moneys);
      sscanf(buf, "%f", &moneys);
#if PHP_MAJOR_VERSION <7
          add_index_string(return_value,i-1,buf,1);
#else
          add_index_string(return_value,i-1,buf);
#endif
      moneys=strtof(buf, &pEnd);
      memset(buf,0,sizeof(buf));
    }
    sprintf(buf, "%.2f", moneyss);
    sscanf(buf, "%f", &moneyss);
#if PHP_MAJOR_VERSION <7
          add_index_string(return_value,zqfcount-1,buf,1);
#else
          add_index_string(return_value,zqfcount-1,buf);
#endif
    memset(buf,0,sizeof(buf));
    }
  /*efree(zqfmoney);*/
}

void quiksort(int a[],int low,int high)
{
    int i = low;
    int j = high;
    int temp = a[i];
    if( low < high)
    {          
        while(i < j) 
        {
            while((a[j] >= temp) && (i < j))
            { 
                j--; 
            }
            a[i] = a[j];
            while((a[i] <= temp) && (i < j))
            {
                i++; 
            }  
            a[j]= a[i];
        }
        a[i] = temp;
        quiksort(a,low,i-1);
        quiksort(a,j+1,high);
    }
    else
    {
        return;
    }
}

/*快速排序算法*/
PHP_METHOD(zqf,quicksort)
{

    zval *zqf_arr;
    int   zqf_arr_count;
    HashTable *zqf_arr_hash;
    zval **zqf_item;
    zval *zqf_items;
    ulong i,idx;
    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "a", &zqf_arr) == FAILURE) {
      RETURN_NULL();
    }
    zqf_arr_hash = Z_ARRVAL_P(zqf_arr);
    zqf_arr_count = zend_hash_num_elements(zqf_arr_hash);
    int data[zqf_arr_count];  
#if PHP_MAJOR_VERSION <7
    zend_hash_internal_pointer_reset(zqf_arr_hash);
    for (i = 0; i < zqf_arr_count; ++i)
    {
        zqf_item=zqf_get_data(zqf_arr_hash); 
        data[i]=(int)Z_STRVAL_PP(zqf_item);  
        zend_hash_move_forward(zqf_arr_hash);  
    }
#else
ZEND_HASH_FOREACH_KEY_VAL(zqf_arr_hash,idx,i,zqf_items)
{   if(Z_TYPE_P(zqf_items) == IS_LONG) {
        data[idx]=Z_LVAL_P(zqf_items);
    }
  } ZEND_HASH_FOREACH_END();
#endif
    quiksort(data,0,zqf_arr_count-1);
    array_init(return_value);
     for (i = 0; i < zqf_arr_count; ++i)
    {
        add_index_long(return_value,i,data[i]);
    }
    /*efree(zqf_arr);*/
}
static int getzqfv(long val,int arr[],int len){
    int low;
    int high;
    int mid;
    low=0;
    high=(int)(len-1);
     while(low<=high){
        mid=(int)((low+high)/2);
        if(arr[mid]<val){
          low=(int)(mid+1);
        }else if(arr[mid]>val){
          high=(int)(mid-1);
        }else{
          return mid;
        }
    }
    return -1;
}


/*二分法查找一维数组一个数*/
PHP_METHOD(zqf,findval)
{
    zval *zqfarr;
    long zqfval;
    int   zqf_arr_count;
    HashTable *zqf_arr_hash;
    zval **zqf_item;
    zval *zqf_items;
    char* key;
    ulong idx;
    int rmid,i,j,tmp;
    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "al", &zqfarr,&zqfval) == FAILURE) {
      RETURN_NULL();
    }
    zqf_arr_hash = Z_ARRVAL_P(zqfarr);
    zqf_arr_count = zend_hash_num_elements(zqf_arr_hash);
    int data[zqf_arr_count];  
#if PHP_MAJOR_VERSION <7
    zend_hash_internal_pointer_reset(zqf_arr_hash);
    for (i = 0; i < zqf_arr_count; ++i)
    {
        zqf_item=zqf_get_data(zqf_arr_hash); 
        data[i]=(int)Z_STRVAL_PP(zqf_item);  
        zend_hash_move_forward(zqf_arr_hash);  
    }
#else
ZEND_HASH_FOREACH_KEY_VAL(zqf_arr_hash,idx,i,zqf_items)
{   if(Z_TYPE_P(zqf_items) == IS_LONG) {
        data[idx]=Z_LVAL_P(zqf_items);
    }
  } ZEND_HASH_FOREACH_END();
#endif  
    for (i = 0; i < zqf_arr_count; ++i)
    {
      for (j = 0; j < zqf_arr_count; ++j)
      {
        if(data[i]<data[j]){
          tmp=data[i];
          data[i]=data[j];
          data[j]=tmp;
        }
      }
    }
    array_init(return_value);
    rmid=getzqfv(zqfval,&data,zqf_arr_count);
    add_index_long(return_value,rmid,data[rmid]);
    zval *myiteam;
    MAKE_STD_ZVAL(myiteam);
    array_init(myiteam);
    for (i = 0;i<zqf_arr_count; ++i)
    {
        add_index_long(myiteam,i,data[i]);
                
    }
    add_assoc_zval(return_value,"result",myiteam);
    /*efree(zqfarr);
    efree(myiteam);*/
      
}
/*查找一维数组重复项*/
PHP_METHOD(zqf,findrepetition)
{
    zval *zqf_arr;
    int   zqf_arr_count;
    HashTable *zqf_arr_hash;
    zval **zqf_item;
    zval *zqf_items;
    char* key;
    ulong idx,i,j;
    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "a", &zqf_arr) == FAILURE) {
      RETURN_NULL();
    }
    zqf_arr_hash = Z_ARRVAL_P(zqf_arr);
    zqf_arr_count = zend_hash_num_elements(zqf_arr_hash);
    int data[zqf_arr_count];
  #if PHP_MAJOR_VERSION <7  
    zend_hash_internal_pointer_reset(zqf_arr_hash);
    for (i = 0; i < zqf_arr_count; ++i)
    {
        zqf_item=zqf_get_data(zqf_arr_hash); 
        data[i]=(int)Z_STRVAL_PP(zqf_item);  
        zend_hash_move_forward(zqf_arr_hash);  
    }
#else
ZEND_HASH_FOREACH_KEY_VAL(zqf_arr_hash,idx,i,zqf_items)
{   if(Z_TYPE_P(zqf_items) == IS_LONG) {
        data[idx]=Z_LVAL_P(zqf_items);
    }
  } ZEND_HASH_FOREACH_END();
#endif  
    array_init(return_value);
    for (i = 0; i < zqf_arr_count; ++i)
    {
      for (j = i+1; j < zqf_arr_count; ++j)
      {
        if(data[i]==data[j]){
          add_index_long(return_value,i,data[i]);
          add_index_long(return_value,j,data[j]);
        }
      }
    }
    /*efree(zqf_arr);*/
}

gdImagePtr qrcode_png(QRcode *code, int fg_color[3], int bg_color[3], int size, int margin,long is_tr,char *logopath,long logopath_len)
{
    int code_size = size / code->width;
    code_size = (code_size == 0)  ? 1 : code_size;
    int img_width = code->width * code_size + 2 * margin;
    gdImagePtr img = gdImageCreate (img_width,img_width); 
    int img_bgcolor;
    if(is_tr){
      img_bgcolor = gdImageColorAllocateAlpha(img,0,0,0,gdAlphaTransparent);
    }else{
      img_bgcolor = gdImageColorAllocate(img,bg_color[0],bg_color[1],bg_color[2]);
    }
    int img_fgcolor =  gdImageColorAllocate(img,fg_color[0],fg_color[1],fg_color[2]);
    gdImageFill(img,0,0,img_bgcolor);
    unsigned char *p = code->data;
    int x,y ,posx,posy;
    for (y = 0 ; y < code->width ; y++)
    {
        for (x = 0 ; x < code->width ; x++)
        {
            if (*p & 1)
            {
                posx = x * code_size + margin;
                posy = y * code_size + margin;
                gdImageFilledRectangle(img,posx,posy,posx + code_size,posy + code_size,img_fgcolor);
            }
            p++;
        }
    }
    if(logopath_len>0){
      FILE * logoinput = fopen(logopath,"rb");
      if (logoinput == NULL){
        php_error_docref (NULL TSRMLS_CC, E_WARNING, "can not open the file");
        return ;
      }
      gdImagePtr logoimg = gdImageCreateFromPng(logoinput);
      gdImageTrueColorToPalette(logoimg,0,65535);
      rewind(logoinput);              
      int  place = 0,index = 0,i;  
      char data;  
      int size[8];   
      while(place<=24)                                                               
       {  
            place++;  
            data = fgetc(logoinput);  
            if(place>16){  
                size[index] =(int) data;  
                index++;  
            }  
       }  
      for(i=0;i<4;i++) if(size[i]<0) size[i] = (size[i]&INT_MAX)&E_MAX;   
      int logo_width = 256*size[2]+size[3];
      int logo_height = 256*size[6]+size[7]; 
      int tmpwidth=img_width/5;
      int scale = logo_width/tmpwidth;
      gdImageCopyResampled(img,logoimg,(img_width-tmpwidth)/2,(img_width-tmpwidth)/2,0,0,tmpwidth,logo_height/scale,logo_width,logo_height);
      fclose(logoinput);
    }
    return img;
}



PHP_METHOD(zqf,savefile)
{
    char *str;
    int str_len;
    qrencode *qe;

    long level = 2;
    long hint  = 0;
    char *path;
    int path_len;
    char *logopath;
    int logopath_len;
    long is_tr = 0;
    int int_bg_color[3] = {255,255,255} ;
    
    int size = 100;
    int margin = 2;

    int red = 0;
    int green = 0;
    int blue = 0;
    int version = 3;
    int casesensitive = 1;
    gdImagePtr im;
    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "ssl|lslllll", &str,&str_len,&path, &path_len,&size,&is_tr,&logopath, &logopath_len,&level, &hint,&red, &green, &blue) == FAILURE) {
      php_error_docref(NULL TSRMLS_CC, E_WARNING, "参数不正确!!!");
        RETURN_FALSE;
    }
    QRecLevel q_level = (int)ZQF_G(level);
    //QRencodeMode q_hint = (int)ZQF_G(hint);
    QRencodeMode q_hint = QR_MODE_8;
    if (level >= 0 && level <= 3) {
        q_level = level;
    }else{
        q_level = 2;
    }

    if (hint){
        q_hint = hint;
    }else{
        q_hint = QR_MODE_8;
   }
    if (red<0 || red>255) {
        red = 0;
    }
    if (green<0 || green>255) {
        green = 0;
    }
    if (blue<0 || blue>255) {
        blue = 0;
    }
    if(is_tr){   
    }else{
      is_tr=0;
    }
    int int_fg_color [3] = {red,green,blue};
    QRcode *code = QRcode_encodeString(str, version, q_level, q_hint, casesensitive);
    if (code == NULL) {
        php_error_docref(NULL TSRMLS_CC, E_WARNING, "字符串编码错误!!!");
        RETURN_FALSE;
    }

    qe = emalloc(sizeof(qrencode));
    qe->code = code;
    FILE * out = fopen(path,"w+");
    if (out == NULL){
        php_error_docref (NULL TSRMLS_CC, E_WARNING, "can not open the file");
        RETURN_FALSE;
    }
    im = qrcode_png(qe->code,int_fg_color,int_bg_color,size,margin,is_tr,logopath,logopath_len);   
    gdImagePng(im,out);
    QRcode_free(qe->code);
    qe->code = NULL;
    gdImageDestroy(im);
    fclose(out);
    
    /*ZEND_REGISTER_RESOURCE(res,fp,zqf_resource_descriptor);
    fwrite(Z_STRVAL_P(zqfbasestatic), 1,Z_STRLEN_P(zqfbasestatic),fp);
    /*fprintf(fp,"%ld\n",Z_LVAL_P(zqfbasestatic));
    fclose(fp); */
    /*zend_hash_index_del(&EG(regular_list),res);*/
    RETURN_TRUE;


  /*zval *zqfbasee;
  /*if (zend_hash_find(ZQF_G(configs),"zqfbase",sizeof("zqfbase"), (void **)&zqfbasee) == SUCCESS) { */
  /*if(zend_hash_find(&EG(symbol_table),"zqfbase",sizeof("zqfbase"), (void **)&zqfbasee) == SUCCESS) { 
      convert_to_long(zqfbasee);
      /*RETURN_LONG(Z_LVAL_P(zqfbasee));
      /*php_printf(estrndup(Z_STRVAL_P(zqfbasee),Z_STRLEN_P(zqfbasee)));
      /*convert_to_long(zqfbasee); */
      /*convert_to_string(zqfbasee);*/
      /*zend_update_property(Z_OBJCE_P(getThis()), getThis(),ZEND_STRL("zqfbase"),zqfbasee TSRMLS_CC);
      /*php_printf("%ld",Z_LVAL_P(zqfbasee));
      /*zend_update_property(Z_OBJCE_P(getThis()), getThis(),"zqfbasestatic",sizeof("zqfbasestatic")-1,zqfbases TSRMLS_CC);  */
  /*}
    efree(zqfbasee);*/
      
}

PHP_METHOD(zqf,autoadd)
{
    long *zqfjishu=NULL;/*代表基数默认为0*/
    long *zqfsort=NULL;/*0代表递减 1代表递增*/
    long *is_zqfsets=NULL;/*代表是否设置基数0代表不设置 1代表设置*/
    zval *zqflong;
    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "lll", &zqfjishu,&zqfsort,&is_zqfsets) == FAILURE) {
      RETURN_NULL();
    }
    if(is_zqfsets){
      if(ZQF_G(zqfflag)){
      }else{
        ZQF_G(counter)=zqfjishu;
        ZQF_G(zqfflag)=1;
      }
    }else{
      ZQF_G(zqfflag)=0;
    }
  
      if(zqfsort){
        ZQF_G(counter)++;
     }else{
        ZQF_G(counter)--;
      }
      /*MAKE_STD_ZVAL(zqflong);  
      ZVAL_LONG(zqflong,ZQF_G(counter));
      zend_update_property(Z_OBJCE_P(getThis()), getThis(),ZEND_STRL("zqfbasestatic"),zqflong TSRMLS_CC);*/
      RETURN_LONG(ZQF_G(counter));
    /*zval *zqfbase;
    zval *zqfbasestatic;
    zval *zqfbaseS;
    zval *zqfbasee;
    long basezqf;
    long basezqfstatic;
    zqfbase = zend_read_property(Z_OBJCE_P(getThis()), getThis(), ZEND_STRL("zqfbase"),0 TSRMLS_DC);
    /*convert_to_long(zqfbase);*/
    /*basezqf=Z_LVAL_P(zqfbase);
    php_printf("%ld",Z_LVAL_P(zqfbase));
    php_printf("%s","\n");
    zqfbasestatic = zend_read_static_property(Z_OBJCE_P(getThis()),ZEND_STRL("zqfbasestatic"),0 TSRMLS_DC);
    /*convert_to_long(zqfbasestatic);*/
    /*basezqfstatic=Z_LVAL_P(zqfbasestatic);
    ++basezqfstatic;
   	++basezqf;
   	MAKE_STD_ZVAL(zqfbaseS);  
    ZVAL_LONG(zqfbaseS,basezqf);
    php_printf("%ld",basezqf);
    php_printf("%s","\n");
    zend_update_property(Z_OBJCE_P(getThis()), getThis(),ZEND_STRL("zqfbase"),zqfbaseS TSRMLS_CC);
    /*zend_update_property(Z_OBJCE_P(getThis()), getThis(),ZEND_STRL("zqfbasestatic"),zqfbaseS TSRMLS_CC); */
    /*if(zend_hash_update(&EG(symbol_table), "zqfbase", sizeof("zqfbase"), (void*)&basezqf, sizeof(zval*), NULL)== SUCCESS){
    /*if(zend_hash_update(ZQF_G(configs), "zqfbase", sizeof("zqfbase"), (void*)&basezqf, sizeof(zval*), NULL)== SUCCESS){*/
        /*array_init(return_value);
        add_assoc_long(return_value,"zqfbase",basezqf);
        php_printf("%s","\n");
        if(zend_hash_find(&EG(symbol_table),"zqfbase",sizeof("zqfbase"), (void **)&zqfbasee) == SUCCESS){
        /*if (zend_hash_find(ZQF_G(configs),"zqfbase",sizeof("zqfbase"), (void **)&zqfbasee) == SUCCESS) { */
            /*convert_to_long(zqfbasee);
            php_printf("%ld",Z_LVAL_P(zqfbasee));
          }else{
            php_printf("%s","读取失败\n");
          }
      }else{
        php_printf("%s","更新失败\n");
      } 
    
    /*add_assoc_long(return_value,"zqfbasestatic",basezqfstatic);
   	/*efree(zqfbase);*/
   	/*efree(zqfbaseS);
   	efree(zqfbasestatic);
   	/*efree(zqfbasearr);
   	RETURN_LONG(basezqf);*/
}
 
PHP_METHOD(zqf,__construct)
{
	/*zval *zqfbasee;
	/*if (zend_hash_find(ZQF_G(configs),"zqfbase",sizeof("zqfbase"), (void **)&zqfbasee) == SUCCESS) { */
  /*if(zend_hash_find(&EG(symbol_table),"zqfbase",sizeof("zqfbase"), (void **)&zqfbasee) == SUCCESS) { 
      convert_to_long(zqfbasee);
      /*RETURN_LONG(Z_LVAL_P(zqfbasee));
      /*php_printf(estrndup(Z_STRVAL_P(zqfbasee),Z_STRLEN_P(zqfbasee)));
      /*convert_to_long(zqfbasee); */
      /*convert_to_string(zqfbasee);*/
    	/*zend_update_property(Z_OBJCE_P(getThis()), getThis(),ZEND_STRL("zqfbase"),zqfbasee TSRMLS_CC);
      /*php_printf("%ld",Z_LVAL_P(zqfbasee));
    	/*zend_update_property(Z_OBJCE_P(getThis()), getThis(),"zqfbasestatic",sizeof("zqfbasestatic")-1,zqfbases TSRMLS_CC);  */
	/*}
   	efree(zqfbasee);*/
      
}

static zend_function_entry zqf_method[] = {
  PHP_ME(zqf,quicksort,zqf_quicksort_arginfo,ZEND_ACC_PUBLIC)
  PHP_ME(zqf,hongbao,zqf_hongbao_arginfo,ZEND_ACC_PUBLIC)
  PHP_ME(zqf,findval,zqf_findval_arginfo,ZEND_ACC_PUBLIC)
  PHP_ME(zqf,findrepetition,zqf_findrepetition_arginfo,ZEND_ACC_PUBLIC)
  PHP_ME(zqf,savefile,zqf_savefile_arginfo,ZEND_ACC_PUBLIC)
	PHP_ME(zqf,autoadd,zqf_autoadd_arginfo,ZEND_ACC_PUBLIC)
  PHP_ME(zqf,__construct,NULL,ZEND_ACC_PUBLIC|ZEND_ACC_CTOR)
    { NULL, NULL, NULL }
};
PHP_MINIT_FUNCTION(zqf)
{
	/* If you have INI entries, uncomment these lines 
	REGISTER_INI_ENTRIES();
	*/
	zend_class_entry ce;
	INIT_CLASS_ENTRY(ce,"zqf",zqf_method);
	zqf_ce=zend_register_internal_class(&ce TSRMLS_CC);
  zend_declare_property_long(zqf_ce, ZEND_STRL("zqfbase"),0,ZEND_ACC_PUBLIC TSRMLS_CC);
  zend_declare_property_long(zqf_ce, ZEND_STRL("zqfbasestatic"),0,ZEND_ACC_STATIC TSRMLS_CC);
    /*REGISTER_LONG_CONSTANT("QRENCODE_QRECLEVEL_L", QR_ECLEVEL_L, CONST_CS|CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("QRENCODE_QRECLEVEL_M", QR_ECLEVEL_M, CONST_CS|CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("QRENCODE_QRECLEVEL_Q", QR_ECLEVEL_Q, CONST_CS|CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("QRENCODE_QRECLEVEL_H", QR_ECLEVEL_H, CONST_CS|CONST_PERSISTENT);

    REGISTER_LONG_CONSTANT("QRENCODE_MODE_NUL", QR_MODE_NUL, CONST_CS|CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("QRENCODE_MODE_NUM", QR_MODE_NUM, CONST_CS|CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("QRENCODE_MODE_AN", QR_MODE_AN, CONST_CS|CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("QRENCODE_MODE_8", QR_MODE_8, CONST_CS|CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("QRENCODE_MODE_KANJI", QR_MODE_KANJI, CONST_CS|CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("QRENCODE_MODE_STRUCTURE", QR_MODE_STRUCTURE, CONST_CS|CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("QRENCODE_MODE_ECI", QR_MODE_ECI, CONST_CS|CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("QRENCODE_MODE_FNC1FIRST", QR_MODE_FNC1FIRST, CONST_CS|CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("QRENCODE_MODE_FNC1SECOND", QR_MODE_FNC1SECOND, CONST_CS|CONST_PERSISTENT);

  //zqf_resource_descriptor=zend_register_list_destructors_ex(qrencode_dtor, NULL, ZQF_RES_NAME, module_number);
    /*zend_declare_property_null(zqf_ce, "zqftype", sizeof("zqftype"), ZEND_ACC_PUBLIC TSRMLS_CC);*/
    /*if (!ZQF_G(configs)) {
    ZQF_G(configs) = (HashTable *)pemalloc(sizeof(HashTable), 1);
    zend_hash_init(ZQF_G(configs), 8, NULL, NULL, 1);
  }
  zval *zqflong;
    MAKE_STD_ZVAL(zqflong); 
    ZVAL_LONG(zqflong,0);
    convert_to_string(zqflong);
    zend_hash_add(&EG(symbol_table), "zqfbase", sizeof("zqfbase"), (void**)&zqflong, sizeof(zval*), NULL);
    /*zend_hash_add(ZQF_G(configs), "zqfbase", sizeof("zqfbase"), (void**)&zqflong, sizeof(zval*), NULL);
    /*zend_hash_add(ZQF_G(configs), "zqftype", sizeof("zqftype"), (void**)&ZQF_G(zqftype), sizeof(zval*), NULL);*/
    ZEND_INIT_MODULE_GLOBALS(zqf,php_zqf_init_globals,NULL);
    /*efree(zqflong);*/
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MSHUTDOWN_FUNCTION
 */
PHP_MSHUTDOWN_FUNCTION(zqf)
{
	/* uncomment this line if you have INI entries
	UNREGISTER_INI_ENTRIES();
	*/
	/*if (ZQF_G(configs)) {
		zend_hash_destroy(ZQF_G(configs));
		pefree(ZQF_G(configs), 1);
	}*/
	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request start */
/* {{{ PHP_RINIT_FUNCTION
 */
PHP_RINIT_FUNCTION(zqf)
{
	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request end */
/* {{{ PHP_RSHUTDOWN_FUNCTION
 */
PHP_RSHUTDOWN_FUNCTION(zqf)
{
	return SUCCESS;
}

PHP_MINFO_FUNCTION(zqf)
{
	php_info_print_table_start();
	php_info_print_table_header(2, "zqf support", "enabled");
	php_info_print_table_row(2, "version", "2.0.1");
	php_info_print_table_row(2, "Author", "qieangel2013");
	php_info_print_table_row(2, "adress", "904208360@qq.com");
	php_info_print_table_end();
	/*DISPLAY_INI_ENTRIES();*/
	/* Remove comments if you have entries in php.ini
	DISPLAY_INI_ENTRIES();
	*/
}
/* }}} */

/* {{{ zqf_functions[]
 *
 * Every user visible function must have an entry in zqf_functions[].
 */
/*const zend_function_entry zqf_functions[] = {
	PHP_FE(confirm_zqf_compiled,	NULL)		/* For testing, remove later. */
	/*PHP_FE_END	/* Must be the last line in zqf_functions[] */
/*};
/* }}} */

/* {{{ zqf_module_entry
 */
zend_module_entry zqf_module_entry = {
	STANDARD_MODULE_HEADER,
	"zqf",
	NULL,
	PHP_MINIT(zqf),
	PHP_MSHUTDOWN(zqf),
	PHP_RINIT(zqf),		/* Replace with NULL if there's nothing to do at request start */
	PHP_RSHUTDOWN(zqf),	/* Replace with NULL if there's nothing to do at request end */
	PHP_MINFO(zqf),
	ZQF_VERSION,
	STANDARD_MODULE_PROPERTIES
};
/* }}} */

#ifdef COMPILE_DL_ZQF
ZEND_GET_MODULE(zqf)
#endif

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
