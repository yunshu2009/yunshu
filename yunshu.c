/*
  +----------------------------------------------------------------------+
  | PHP Version 7                                                        |
  +----------------------------------------------------------------------+
  | Copyright (c) 1997-2018 The PHP Group                                |
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
#include "php_yunshu.h"

/* If you declare any globals in php_yunshu.h uncomment this:
ZEND_DECLARE_MODULE_GLOBALS(yunshu)
*/

/* True global resources - no need for thread safety here */
static int le_yunshu;

/* {{{ PHP_INI
 */
/* Remove comments and fill if you need to have entries in php.ini
PHP_INI_BEGIN()
    STD_PHP_INI_ENTRY("yunshu.global_value",      "42", PHP_INI_ALL, OnUpdateLong, global_value, zend_yunshu_globals, yunshu_globals)
    STD_PHP_INI_ENTRY("yunshu.global_string", "foobar", PHP_INI_ALL, OnUpdateString, global_string, zend_yunshu_globals, yunshu_globals)
PHP_INI_END()
*/
/* }}} */

/*获取变量长度,只支持字符串和数组*/
PHP_FUNCTION(get_length) 
{
    zval *val;
    size_t size;
    HashTable *myht;
 
    if (zend_parse_parameters(ZEND_NUM_ARGS(), "z", &val) == FAILURE) {
        return;
    }   
 
    if (Z_TYPE_P(val) == IS_STRING) {
        size = Z_STRLEN_P(val);
    } else if (Z_TYPE_P(val) == IS_ARRAY) {
        myht = Z_ARRVAL_P(val);
        size = zend_array_count(myht);
    } else {
        RETURN_BOOL(false);
    }   
         
    RETVAL_LONG(size);
}

/*获取客户端ip*/
PHP_FUNCTION(get_client_ip)
{
    zval *server, *field;
    zend_string *ip = NULL;

    /*
        $_SERVER['HTTP_CLIENT_IP'];
        // OR
        $_SERVER['HTTP_X_FORWARDED_FOR'];
        // OR
        $_SERVER['HTTP_X_REAL_IP'];  // 更多自定义的 key
        // OR
        $_SERVER['REMOTE_ADDR'];
    */
    server = zend_hash_str_find(&EG(symbol_table), "_SERVER", sizeof("_SERVER") - 1);
    if (Z_TYPE_P(server) == IS_ARRAY) {
        if ((field= zend_hash_str_find(Z_ARRVAL_P(server), "HTTP_CLIENT_IP", sizeof("HTTP_CLIENT_IP") - 1)) &&
                Z_TYPE_P(field) == IS_STRING) {
            ip = Z_STR_P(field);
        } else if ((field = zend_hash_str_find(Z_ARRVAL_P(server), "HTTP_X_FORWARDED_FOR", sizeof("HTTP_X_FORWARDED_FOR") - 1)) &&
                Z_TYPE_P(field) == IS_STRING) {
            ip = Z_STR_P(field);
        } else if ((field = zend_hash_str_find(Z_ARRVAL_P(server), "REMOTE_ADDR", sizeof("REMOTE_ADDR") - 1)) &&
                Z_TYPE_P(field) == IS_STRING) {
            ip = Z_STR_P(field);
        }
    }
    if (ip) {
        zend_string_copy(ip);
    } else {
        ip = zend_string_init("0.0.0.0", sizeof("0.0.0.0") - 1, 0);  // 默认值
    }

    RETURN_STR(ip);
}


/* Remove the following function when you have successfully modified config.m4
   so that your module can be compiled into PHP, it exists only for testing
   purposes. */

/* Every user-visible function in PHP should document itself in the source */
/* {{{ proto string confirm_yunshu_compiled(string arg)
   Return a string to confirm that the module is compiled in */
PHP_FUNCTION(confirm_yunshu_compiled)
{
	char *arg = NULL;
	size_t arg_len, len;
	zend_string *strg;

	if (zend_parse_parameters(ZEND_NUM_ARGS(), "s", &arg, &arg_len) == FAILURE) {
		return;
	}

	strg = strpprintf(0, "Congratulations! You have successfully modified ext/%.78s/config.m4. Module %.78s is now compiled into PHP.", "yunshu", arg);

	RETURN_STR(strg);
}
/* }}} */
/* The previous line is meant for vim and emacs, so it can correctly fold and
   unfold functions in source code. See the corresponding marks just before
   function definition, where the functions purpose is also documented. Please
   follow this convention for the convenience of others editing your code.
*/


/* {{{ php_yunshu_init_globals
 */
/* Uncomment this function if you have INI entries
static void php_yunshu_init_globals(zend_yunshu_globals *yunshu_globals)
{
	yunshu_globals->global_value = 0;
	yunshu_globals->global_string = NULL;
}
*/
/* }}} */

/* {{{ PHP_MINIT_FUNCTION
 */
PHP_MINIT_FUNCTION(yunshu)
{
	/* If you have INI entries, uncomment these lines
	REGISTER_INI_ENTRIES();
	*/
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MSHUTDOWN_FUNCTION
 */
PHP_MSHUTDOWN_FUNCTION(yunshu)
{
	/* uncomment this line if you have INI entries
	UNREGISTER_INI_ENTRIES();
	*/
	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request start */
/* {{{ PHP_RINIT_FUNCTION
 */
PHP_RINIT_FUNCTION(yunshu)
{
#if defined(COMPILE_DL_YUNSHU) && defined(ZTS)
	ZEND_TSRMLS_CACHE_UPDATE();
#endif
	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request end */
/* {{{ PHP_RSHUTDOWN_FUNCTION
 */
PHP_RSHUTDOWN_FUNCTION(yunshu)
{
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MINFO_FUNCTION
 */
PHP_MINFO_FUNCTION(yunshu)
{
	php_info_print_table_start();
	php_info_print_table_header(2, "yunshu support", "enabled");
	php_info_print_table_end();

	/* Remove comments if you have entries in php.ini
	DISPLAY_INI_ENTRIES();
	*/
}
/* }}} */

/* {{{ yunshu_functions[]
 *
 * Every user visible function must have an entry in yunshu_functions[].
 */
const zend_function_entry yunshu_functions[] = {
    PHP_FE(get_length, NULL)
    PHP_FE(get_client_ip, NULL)
	PHP_FE(confirm_yunshu_compiled,	NULL)		/* For testing, remove later. */
	PHP_FE_END	/* Must be the last line in yunshu_functions[] */
};
/* }}} */

/* {{{ yunshu_module_entry
 */
zend_module_entry yunshu_module_entry = {
	STANDARD_MODULE_HEADER,
	"yunshu",
	yunshu_functions,
	PHP_MINIT(yunshu),
	PHP_MSHUTDOWN(yunshu),
	PHP_RINIT(yunshu),		/* Replace with NULL if there's nothing to do at request start */
	PHP_RSHUTDOWN(yunshu),	/* Replace with NULL if there's nothing to do at request end */
	PHP_MINFO(yunshu),
	PHP_YUNSHU_VERSION,
	STANDARD_MODULE_PROPERTIES
};
/* }}} */

#ifdef COMPILE_DL_YUNSHU
#ifdef ZTS
ZEND_TSRMLS_CACHE_DEFINE()
#endif
ZEND_GET_MODULE(yunshu)
#endif

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
