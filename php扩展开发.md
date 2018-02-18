## PHP7扩展开发之类型处理
zval变量相关的宏方法大部分定义在```Zend/zend_types.h```文件中。

类型相关宏方法
``Z_TYPE_P(zval *)``` 获取zval变量的类型。常见的类型都有：


```
#define IS_UNDEF                    0
#define IS_NULL                     1
#define IS_FALSE                    2
#define IS_TRUE                     3
#define IS_LONG                     4
#define IS_DOUBLE                   5
#define IS_STRING                   6
#define IS_ARRAY                    7
#define IS_OBJECT                   8
#define IS_RESOURCE                 9
#define IS_REFERENCE                10
```
```Z_STRLEN_P(zval *)``` 获取字符串的长度。

目前所有的```RETVAL```宏和```RETURN*```宏,定义在```zend/zend_API.h```文件中


```
#define RETVAL_BOOL(b)          ZVAL_BOOL(return_value, b)
#define RETVAL_NULL()           ZVAL_NULL(return_value)
#define RETVAL_LONG(l)          ZVAL_LONG(return_value, l)
#define RETVAL_DOUBLE(d)        ZVAL_DOUBLE(return_value, d)
#define RETVAL_STR(s)         ZVAL_STR(return_value, s)
#define RETVAL_INTERNED_STR(s)      ZVAL_INTERNED_STR(return_value, s)
#define RETVAL_NEW_STR(s)       ZVAL_NEW_STR(return_value, s)
#define RETVAL_STR_COPY(s)        ZVAL_STR_COPY(return_value, s)
#define RETVAL_STRING(s)        ZVAL_STRING(return_value, s)
#define RETVAL_STRINGL(s, l)      ZVAL_STRINGL(return_value, s, l)
#define RETVAL_EMPTY_STRING()       ZVAL_EMPTY_STRING(return_value)
#define RETVAL_RES(r)         ZVAL_RES(return_value, r)
#define RETVAL_ARR(r)         ZVAL_ARR(return_value, r)
#define RETVAL_OBJ(r)         ZVAL_OBJ(return_value, r)
#define RETVAL_ZVAL(zv, copy, dtor)   ZVAL_ZVAL(return_value, zv, copy, dtor)
#define RETVAL_FALSE            ZVAL_FALSE(return_value)
#define RETVAL_TRUE             ZVAL_TRUE(return_value)

#define RETURN_BOOL(b)          { RETVAL_BOOL(b); return; }
#define RETURN_NULL()           { RETVAL_NULL(); return;}
#define RETURN_LONG(l)          { RETVAL_LONG(l); return; }
#define RETURN_DOUBLE(d)        { RETVAL_DOUBLE(d); return; }
#define RETURN_STR(s)           { RETVAL_STR(s); return; }
#define RETURN_INTERNED_STR(s)      { RETVAL_INTERNED_STR(s); return; }
#define RETURN_NEW_STR(s)       { RETVAL_NEW_STR(s); return; }
#define RETURN_STR_COPY(s)        { RETVAL_STR_COPY(s); return; }
#define RETURN_STRING(s)        { RETVAL_STRING(s); return; }
#define RETURN_STRINGL(s, l)      { RETVAL_STRINGL(s, l); return; }
#define RETURN_EMPTY_STRING()       { RETVAL_EMPTY_STRING(); return; }
#define RETURN_RES(r)           { RETVAL_RES(r); return; }
#define RETURN_ARR(r)           { RETVAL_ARR(r); return; }
#define RETURN_OBJ(r)           { RETVAL_OBJ(r); return; }
#define RETURN_ZVAL(zv, copy, dtor)   { RETVAL_ZVAL(zv, copy, dtor); return; }
#define RETURN_FALSE            { RETVAL_FALSE; return; }
#define RETURN_TRUE             { RETVAL_TRUE; return; }
```
其实，除了这些标量类型，还有很多php语言中的复合类型我们需要在函数中返回，如数组和对象，我们可以通过```RETVAL_ZVAL```与```RETURN_ZVAL```来操作它们，有关它们的详细介绍我们将在后续章节中叙述。