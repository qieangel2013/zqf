PHP_ARG_WITH(zqf, for zqf support,
Make sure that the comment is aligned:
[  --with-zqf             Include zqf support])
PHP_ARG_ENABLE(zqf, whether to enable zqf support,
 [  --enable-zqf           Enable zqf support])
if test "$PHP_ZQF" != "no"; then
   SEARCH_PATH="/usr/local /usr"     
   SEARCH_FOR="/include/qrencode.h"  
   if test -r $PHP_ZQF/$SEARCH_FOR; then # path given as parameter
     ZQF_DIR=$PHP_ZQF
   else 
     AC_MSG_CHECKING([for qrencode files in default path])
     for i in $SEARCH_PATH ; do
       if test -r $i/$SEARCH_FOR; then
         ZQF_DIR=$i
         AC_MSG_RESULT(found in $i)
       fi
     done
   fi
  
   if test -z "$ZQF_DIR"; then
     AC_MSG_RESULT([not found])
     AC_MSG_ERROR([Please reinstall the qrencode wget http://fukuchi.org/works/qrencode/qrencode-3.4.4.tar.gz])
   fi


   PHP_ADD_INCLUDE($ZQF_DIR/include)


   LIBNAME=qrencode
   LIBSYMBOL=QRcode_APIVersionString  

   PHP_CHECK_LIBRARY($LIBNAME,$LIBSYMBOL,
   [
     PHP_ADD_LIBRARY_WITH_PATH($LIBNAME, $ZQF_DIR/$PHP_LIBDIR, ZQF_SHARED_LIBADD)
     PHP_ADD_LIBRARY_WITH_PATH(gd, $ZQF_DIR/$PHP_LIBDIR, ZQF_SHARED_LIBADD)
     AC_DEFINE(HAVE_ZQFLIB,1,[ ])
   ],[
     AC_MSG_ERROR([wrong qrencode lib version or lib not found])
   ],[
     -L$ZQF_DIR/$PHP_LIBDIR -lm
   ])


   PHP_SUBST(ZQF_SHARED_LIBADD)

  PHP_NEW_EXTENSION(zqf, zqf.c, $ext_shared)
fi
if test -z "$PHP_DEBUG"; then 
  AC_ARG_ENABLE(debug,
  [ --enable-debug      compile with debugging symbols],[
    PHP_DEBUG=$enableval
  ],[ PHP_DEBUG=no
  ])
fi
