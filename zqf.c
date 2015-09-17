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

#include "php.h"
#include "php_ini.h"
#include "ext/standard/info.h"
#include "php_zqf.h"
#define ZQF_RES_NAME "zqf_resource"
/* If you declare any globals in php_zqf.h uncomment this:
ZEND_DECLARE_MODULE_GLOBALS(zqf)
*/
ZEND_DECLARE_MODULE_GLOBALS(zqf)
/* True global resources - no need for thread safety here */
static int le_zqf;
zend_class_entry *zqf_ce;
static int zqf_resource_descriptor;
ZEND_BEGIN_ARG_INFO_EX(zqf_autoadd_arginfo, 0, 0, 1)
    ZEND_ARG_INFO(0,zqfjishu)
    ZEND_ARG_INFO(0,zqfsort)
    ZEND_ARG_INFO(0,is_zqfsets)
ZEND_END_ARG_INFO()
ZEND_BEGIN_ARG_INFO_EX(zqf_savefile_arginfo, 0, 0, 1)
    ZEND_ARG_INFO(0,path)
    ZEND_ARG_INFO(0,mode)
    ZEND_ARG_INFO(0,ext)
ZEND_END_ARG_INFO()




static void php_zqf_init_globals(zend_zqf_globals *zqf_globals)
{
    zqf_globals->zqfflag = 0;
}
static void php_myres_dtor(zend_rsrc_list_entry *rsrc TSRMLS_DC){  
    FILE *fp = (FILE*)rsrc->ptr;  
    fclose(fp);  
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





/* }}} */

/* {{{ PHP_MINFO_FUNCTION
 */
PHP_METHOD(zqf,savefile)
{
    zval *zqfbasestatic;
    zval *res;
    FILE *fp;
    char *path;
    int path_len;
    char *mode;
    int mode_len;
    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "ss", &path,&path_len,&mode,&mode_len) == FAILURE) {
      RETURN_BOOL(0);
    }
    zqfbasestatic = zend_read_static_property(Z_OBJCE_P(getThis()),ZEND_STRL("zqfbasestatic"),0 TSRMLS_CC);
    convert_to_string(zqfbasestatic);
    fp=fopen(estrndup(path,path_len),estrndup(mode,mode_len));
    /*ZEND_REGISTER_RESOURCE(res,fp,zqf_resource_descriptor);
    fwrite(Z_STRVAL_P(zqfbasestatic), 1,Z_STRLEN_P(zqfbasestatic),fp);
    /*fprintf(fp,"%ld\n",Z_LVAL_P(zqfbasestatic));
    fclose(fp); */
    /*zend_hash_index_del(&EG(regular_list),res);*/
    RETURN_BOOL(1);


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
      MAKE_STD_ZVAL(zqflong);  
      ZVAL_LONG(zqflong,ZQF_G(counter));
      zend_update_property(Z_OBJCE_P(getThis()), getThis(),ZEND_STRL("zqfbasestatic"),zqflong TSRMLS_CC);
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
  zqf_resource_descriptor=zend_register_list_destructors_ex(php_myres_dtor, NULL, ZQF_RES_NAME, module_number);
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
	php_info_print_table_row(2, "version", "1.0");
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
	PHP_ZQF_VERSION,
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
