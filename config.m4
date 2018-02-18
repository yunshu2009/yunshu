dnl $Id$
dnl config.m4 for extension yunshu

dnl Comments in this file start with the string 'dnl'.
dnl Remove where necessary. This file will not work
dnl without editing.

dnl If your extension references something external, use with:

dnl PHP_ARG_WITH(yunshu, for yunshu support,
dnl Make sure that the comment is aligned:
dnl [  --with-yunshu             Include yunshu support])

dnl Otherwise use enable:

PHP_ARG_ENABLE(yunshu, whether to enable yunshu support,
Make sure that the comment is aligned:
[  --enable-yunshu           Enable yunshu support])

if test "$PHP_YUNSHU" != "no"; then
  dnl Write more examples of tests here...

  dnl # --with-yunshu -> check with-path
  dnl SEARCH_PATH="/usr/local /usr"     # you might want to change this
  dnl SEARCH_FOR="/include/yunshu.h"  # you most likely want to change this
  dnl if test -r $PHP_YUNSHU/$SEARCH_FOR; then # path given as parameter
  dnl   YUNSHU_DIR=$PHP_YUNSHU
  dnl else # search default path list
  dnl   AC_MSG_CHECKING([for yunshu files in default path])
  dnl   for i in $SEARCH_PATH ; do
  dnl     if test -r $i/$SEARCH_FOR; then
  dnl       YUNSHU_DIR=$i
  dnl       AC_MSG_RESULT(found in $i)
  dnl     fi
  dnl   done
  dnl fi
  dnl
  dnl if test -z "$YUNSHU_DIR"; then
  dnl   AC_MSG_RESULT([not found])
  dnl   AC_MSG_ERROR([Please reinstall the yunshu distribution])
  dnl fi

  dnl # --with-yunshu -> add include path
  dnl PHP_ADD_INCLUDE($YUNSHU_DIR/include)

  dnl # --with-yunshu -> check for lib and symbol presence
  dnl LIBNAME=yunshu # you may want to change this
  dnl LIBSYMBOL=yunshu # you most likely want to change this 

  dnl PHP_CHECK_LIBRARY($LIBNAME,$LIBSYMBOL,
  dnl [
  dnl   PHP_ADD_LIBRARY_WITH_PATH($LIBNAME, $YUNSHU_DIR/$PHP_LIBDIR, YUNSHU_SHARED_LIBADD)
  dnl   AC_DEFINE(HAVE_YUNSHULIB,1,[ ])
  dnl ],[
  dnl   AC_MSG_ERROR([wrong yunshu lib version or lib not found])
  dnl ],[
  dnl   -L$YUNSHU_DIR/$PHP_LIBDIR -lm
  dnl ])
  dnl
  dnl PHP_SUBST(YUNSHU_SHARED_LIBADD)

  PHP_NEW_EXTENSION(yunshu, yunshu.c, $ext_shared,, -DZEND_ENABLE_STATIC_TSRMLS_CACHE=1)
fi
