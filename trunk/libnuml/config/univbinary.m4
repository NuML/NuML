dnl
dnl Filename    : univbinary.m4
dnl Description : Autoconf macro to check for the options for creating universal binaries
dnl Author(s)   : SBRML Team <sbrml-team@caltech.edu>
dnl Organization: California Institute of Technology
dnl Created     : 2008-11-25
dnl Revision    : $Id: univbinary.m4 9686 2009-06-30 17:37:35Z ajouraku $
dnl $HeadURL: https://sbrml.svn.sourceforge.net/svnroot/sbrml/branches/rel-4-0-0/config/univbinary.m4 $
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
dnl Supports --enable-universal-binary[=ARG]
dnl

AC_DEFUN([CONFIG_LIB_UNIVBINARY],
[
  AC_ARG_VAR([UNIVBINARY])

  AC_ARG_ENABLE(universal-binary,
              AC_HELP_STRING([--enable-universal-binary@<:@=ARG@:>@],
                             [Generate universal binaries on MacOSX [[default=no]] 
                              ("-arch i386 -arch ppc" used when enabled without ARG) ]),
	      [enable_univbinary=$enableval],
	      [enable_univbinary=no])

  if test "x$enable_univbinary" != xno; then

    dnl this option can be used only on MacOSX.

    case $host in
    *darwin*) 
        ;;
    *)
        AC_MSG_ERROR([*** --enable-universal-binary can be used only on MacOSX. ***])
	;;
    esac


    if test "x$enable_univbinary" != xyes;
    then
      LDFLAGS="${LDFLAGS} $enable_univbinary"
      CFLAGS="${CFLAGS} $enable_univbinary"
      CXXFLAGS="${CXXFLAGS} $enable_univbinary"
    else
      default_OPTS="-arch i386 -arch ppc"
      LDFLAGS="${LDFLAGS} ${default_OPTS}"
      CFLAGS="${CFLAGS} ${default_OPTS}"
      CXXFLAGS="${CXXFLAGS} ${default_OPTS}"
    fi

    AC_DEFINE([USE_UNIVBINARY], 1, [Define to 1 to add options for creating universal binaries])
    AC_SUBST(USE_UNIVBINARY, 1)
  fi

  dnl We record the USE_XXX flag, for later testing in Makefiles.

  LIBSBRML_OPTIONS="$LIBSBRML_OPTIONS USE_UNIVBINARY"

])

