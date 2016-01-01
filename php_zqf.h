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
  | Author:       zqf  904208360@qq.com                                                        |
  +----------------------------------------------------------------------+
*/

/* $Id$ */

#ifndef PHP_ZQF_H
#define PHP_ZQF_H

#define phpext_zqf_ptr &zqf_module_entry

#define ZQF_VERSION "2.0.0" /* Replace with version number for your extension */

#ifdef PHP_WIN32
#	define PHP_ZQF_API __declspec(dllexport)
#elif defined(__GNUC__) && __GNUC__ >= 4
#	define PHP_ZQF_API __attribute__ ((visibility("default")))
#else
#	define PHP_ZQF_API
#endif

#ifdef ZTS
#include "TSRM.h"
#endif
#if PHP_MAJOR_VERSION <7
  static zval* zqf_get_datas(HashTable *ht){
  zval **zqf_itemm;
  zend_hash_get_current_data(ht,(void**)&zqf_itemm);
  return zqf_itemm;
 }
#else
#define zqf_get_data zend_hash_get_current_data
#endif
/* 
  	Declare any global variables you may need between the BEGIN
	and END macros here:    */ 

ZEND_BEGIN_MODULE_GLOBALS(zqf)
  /*HashTable *configs;*/
  long  counter,zqfflag,level,hint,casesensitive;
ZEND_END_MODULE_GLOBALS(zqf)
/* In every utility function you add that needs to use variables 
   in php_zqf_globals, call TSRMLS_FETCH(); after declaring other 
   variables used by that function, or better yet, pass in TSRMLS_CC
   after the last function argument and declare your utility function
   with TSRMLS_DC after the last declared argument.  Always refer to
   the globals in your function as ZQF_G(variable).  You are 
   encouraged to rename these macros something shorter, see
   examples in any other php module directory.
*/

#ifdef ZTS
#define ZQF_G(v) TSRMG(zqf_globals_id, zend_zqf_globals *, v)
#else
#define ZQF_G(v) (zqf_globals.v)
#endif
extern zend_module_entry zqf_module_entry;
#define phpext_zqf_ptr &zqf_module_entry
#endif	/* PHP_ZQF_H */


/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
