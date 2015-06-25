PHP_ARG_WITH(zqf, for zqf support,
Make sure that the comment is aligned:
[  --with-zqf             Include zqf support])
if test "$PHP_ZQF" != "no"; then
  
   PHP_SUBST(ZQF_SHARED_LIBADD)

  PHP_NEW_EXTENSION(zqf, zqf.c, $ext_shared)
fi
