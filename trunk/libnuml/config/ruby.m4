dnl
dnl Filename    : ruby.m4
dnl Description : Autoconf macro to check for Ruby
dnl Author(s)   : SBRML Team <sbrml-team@caltech.edu>
dnl Organization: California Institute of Technology
dnl Created     : 2007-12-17
dnl Revision    : $Id: ruby.m4 8909 2009-01-19 07:16:58Z mhucka $
dnl $HeadURL: https://sbrml.svn.sourceforge.net/svnroot/sbrml/branches/rel-4-0-0/config/ruby.m4 $
dnl
dnl <!-------------------------------------------------------------------------
dnl This file is part of libSBRML.  Please visit http://sbrml.org for more
dnl information about SBRML, and the latest version of libSBRML.
dnl
dnl Copyright 2005-2009 California Institute of Technology.
dnl Copyright 2002-2005 California Institute of Technology and
dnl                     Japan Science and Technology Corporation.
dnl 
dnl This library is free software; you can redistribute it and/or modify it
dnl under the terms of the GNU Lesser General Public License as published by
dnl the Free Software Foundation.  A copy of the license agreement is provided
dnl in the file named "LICENSE.txt" included with this software distribution
dnl and also available online as http://sbrml.org/software/libsbrml/license.html
dnl --------------------------------------------------------------------- -->*/

dnl
dnl Provides --with-ruby[=PREFIX]
dnl

AC_DEFUN([CONFIG_PROG_RUBY],
[
  AC_ARG_VAR([RUBY])

  AC_ARG_WITH(ruby,
              AC_HELP_STRING([--with-ruby=PREFIX],
                             [Generate Ruby interface library [[default=no]]]),
	      [with_ruby=$withval],
	      [with_ruby=no])

  if test "x$with_ruby" != xno; then

    dnl Find a ruby executable.

    if test "x$with_ruby" != xyes;
    then
      dnl Remove needless trailing slashes because it can confuse tests later.
      with_ruby=`echo $with_ruby | sed -e 's,\(.*\)/$,\1,g'`

      AC_PATH_PROG([RUBY], [ruby], [no], [$with_ruby/bin])
    else
      AC_PATH_PROG([RUBY], [ruby])
    fi

    if test -z "$RUBY" -o "$RUBY" = "no" -o ! -f "$RUBY"; 
    then
      AC_MSG_ERROR([*** ruby missing - please install first or check config.log ***])
    fi  

    dnl check version if required
    m4_ifvaln([$1], [
        AC_MSG_CHECKING($RUBY version >= $1)
        if test `$RUBY -rrbconfig -e ["puts RUBY_VERSION >= \"$1\" ? \"OK\" : \"OLD\""]` = "OK"
        then
          AC_MSG_RESULT(ok)
        else
          AC_MSG_RESULT(no)
          AC_MSG_ERROR([*** ruby version $1 or later is required ***])
        fi
    ])

    AC_MSG_CHECKING(for ruby prefix)
    RUBY_PREFIX=`$RUBY -rrbconfig -e ["include Config; puts CONFIG['prefix']"]`
    AC_MSG_RESULT($RUBY_PREFIX)

    if test `$RUBY -rrbconfig -e ["puts RUBY_VERSION >= \"1.9.0\" ? \"OK\" : \"OLD\""]` = "OK"; 
    then
      RUBY_ARCHDIR=`$RUBY -rrbconfig -e ["include Config; print \"#{CONFIG['rubyhdrdir']} -I#{CONFIG['rubyhdrdir']}/#{CONFIG['arch']}\" "]`
      RUBY_H=`$RUBY -rrbconfig -e ["include Config; print \"#{CONFIG['rubyhdrdir']}\" "]`"/ruby.h"
    else
      RUBY_ARCHDIR=`$RUBY -rrbconfig -e ["include Config; puts CONFIG['archdir']"]`
      RUBY_H="${RUBY_ARCHDIR}/ruby.h"
    fi    

    AC_MSG_CHECKING(for ruby.h)
    if test -z "$RUBY_H" || ! test -f "$RUBY_H"; 
    then
      AC_MSG_RESULT(no)

      AC_MSG_ERROR([*** $RUBY_H missing - please install first or check config.log ***])
    fi
    AC_MSG_RESULT(yes)


    RUBY_LIBDIR=`$RUBY -rrbconfig -e ["include Config; puts CONFIG['libdir']"]` 
    RUBY_NAME=`$RUBY -rrbconfig -e ["include Config; puts CONFIG['RUBY_SO_NAME']"]`

    dnl Figure out the last bits for linking.
    dnl This comes in part from SWIG 1.3.31's configure.ac file.

    case $host in
    *darwin*) 
   	RUBY_CPPFLAGS="-I${RUBY_ARCHDIR}"
	RUBY_LDFLAGS="-L${RUBY_LIBDIR} -undefined dynamic_lookup"
	;;
    *cygwin* | *mingw*) 
	RUBY_CPPFLAGS="-I${RUBY_ARCHDIR} -DUSE_DL_IMPORT"
	RUBY_LDFLAGS="-L${RUBY_LIBDIR}"
        RUBY_LIBS="-l${RUBY_NAME}"
	CONFIG_ADD_LDPATH(${RUBY_PREFIX}/lib/${RUBY_NAME}/config)
	;;
    *)
	RUBY_CPPFLAGS="-I${RUBY_ARCHDIR}"
        RUBY_LDFLAGS="-L${RUBY_LIBDIR}"
        RUBY_LIBS="-l${RUBY_NAME}"
	;;
    esac

    AC_DEFINE([USE_RUBY], 1, [Define to 1 to use Ruby])
    AC_SUBST(USE_RUBY, 1)

    AC_SUBST(RUBY_CPPFLAGS)
    AC_SUBST(RUBY_LDFLAGS)
    AC_SUBST(RUBY_LIBS)

  fi

  dnl We record the USE_XXX flag, for later testing in Makefiles.

  LIBSBRML_OPTIONS="$LIBSBRML_OPTIONS USE_RUBY"

])

