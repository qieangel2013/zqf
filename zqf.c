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
  | Author:                                                              |
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

/* If you declare any globals in php_zqf.h uncomment this:*/
ZEND_DECLARE_MODULE_GLOBALS(zqf)


/* True global resources - no need for thread safety here */
static int le_zqf;

/* {{{ PHP_INI
 */
/* Remove comments and fill if you need to have entries in php.ini*/
PHP_INI_BEGIN()
	PHP_INI_ENTRY("zqf.greeting", "zqf",
PHP_INI_ALL, NULL)
    STD_PHP_INI_ENTRY("zqf.zqfflag","1", PHP_INI_ALL, OnUpdateLong, zqfflag, zend_zqf_globals, zqf_globals)
PHP_INI_END()
static void php_zqf_init_globals(zend_zqf_globals *zqf_globals)
{
zqf_globals->zqfflag = 0;
}
/* }}} */

/* Remove the following function when you have successfully modified config.m4
   so that your module can be compiled into PHP, it exists only for testing
   purposes. */

/* Every user-visible function in PHP should document itself in the source */
/* {{{ proto string confirm_zqf_compiled(string arg)
   Return a string to confirm that the module is compiled in */
PHP_FUNCTION(zqf)
{
	long *zqfjishu=NULL;/*代表基数默认为0*/
	long *zqfsort=NULL;/*0代表递减 1代表递增*/
	long *is_zqfsets=NULL;/*代表是否设置基数0代表不设置 1代表设置*/
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "lll", &zqfjishu,&zqfsort,&is_zqfsets) == FAILURE) {
		return;
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
		RETURN_LONG(ZQF_G(counter));
}


/* }}} */
/* The previous line is meant for vim and emacs, so it can correctly fold and 
   unfold functions in source code. See the corresponding marks just before 
   function definition, where the functions purpose is also documented. Please 
   follow this convention for the convenience of others editing your code.
*/


/* {{{ php_zqf_init_globals */
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
PHP_MINIT_FUNCTION(zqf)
{
	/* If you have INI entries, uncomment these lines 
	REGISTER_INI_ENTRIES();
	*/
	ZQF_G(counter) = 0;
	ZQF_G(zqfflag) = 0;
	ZEND_INIT_MODULE_GLOBALS(zqf, php_zqf_init_globals,
NULL);
	REGISTER_INI_ENTRIES();
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MSHUTDOWN_FUNCTION
 */
PHP_MSHUTDOWN_FUNCTION(zqf)
{
	/* uncomment this line if you have INI entries*/
	UNREGISTER_INI_ENTRIES();
	
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
/* }}} */

/* {{{ PHP_MINFO_FUNCTION
 */
PHP_MINFO_FUNCTION(zqf)
{
	php_info_print_table_start();
	php_info_print_table_header(2, "zqf support", "enabled");
	php_info_print_table_end();

	/* Remove comments if you have entries in php.ini
	DISPLAY_INI_ENTRIES();
	*/
}
/* }}} */

/* {{{ zqf_functions[]
 *
 * Every user visible function must have an entry in zqf_functions[].
 */
const zend_function_entry zqf_functions[] = {
	PHP_FE(zqf,	NULL)		/* For testing, remove later. */
	PHP_FE_END	/* Must be the last line in zqf_functions[] */
};
/* }}} */

/* {{{ zqf_module_entry
 */
zend_module_entry zqf_module_entry = {
	STANDARD_MODULE_HEADER,
	"zqf",
	zqf_functions,
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
