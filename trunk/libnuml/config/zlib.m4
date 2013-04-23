﻿dnl
dnl Filename    : zlib.m4
dnl Description : Autoconf macro to check for existence of zlib library
dnl Author(s)   : NUML Team <numl-team@caltech.edu>
dnl Organization: California Institute of Technology
dnl Created     : 2008-07-04
dnl Revision    : $Id: zlib.m4 8826 2009-01-12 23:56:28Z ajouraku $
dnl $HeadURL: https://numl.svn.sourceforge.net/svnroot/numl/branches/rel-4-0-0/config/zlib.m4 $
dnl
dnl <!-------------------------------------------------------------------------
dnl This file is part of libNUML.  Please visit http://numl.org for more
dnl information about NUML, and the latest version of libNUML.
dnl
dnl Copyright 2008 California Institute of Technology.
dnl 
dnl This library is free software; you can redistribute it and/or modify it
dnl under the terms of the GNU Lesser General Public License as published by
dnl the Free Software Foundation.  A copy of the license agreement is provided
dnl in the file named "LICENSE.txt" included with this software distribution
dnl and also available online as http://numl.org/software/libnuml/license.html
dnl --------------------------------------------------------------------- -->*/

#
# This zlib check code was borrowed heavily from configure.ac
# file of OpenSSH-5.0p1 (http://www.openssh.com/).
# The file is distributed under the following terms:
#
# ------------------------------------------------------------------------------ 
# Copyright (c) 1999-2004 Damien Miller
#
# Permission to use, copy, modify, and distribute this software for any
# purpose with or without fee is hereby granted, provided that the above
# copyright notice and this permission notice appear in all copies.
#
# THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
# WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
# MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
# ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
# WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
# ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
# OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
# ------------------------------------------------------------------------------ 

AC_DEFUN([CONFIG_LIB_ZLIB],
[

  AC_ARG_WITH([zlib],
	      AC_HELP_STRING([--with-zlib=PREFIX], 
                             [Enable reading/writing files compressed with zlib [[default=autodetect]] ]
              ),
	      [with_zlib="$withval"], [with_zlib=autodetect]
  )

  if test "x$with_zlib" = "xautodetect"; then
    if test "x$enable_compression" = "xno"; then
      with_zlib=no
    fi
  fi

  AC_MSG_CHECKING(for zlib library)
  if test "x$with_zlib" != "xno"; then
    AC_MSG_RESULT(yes)
    if test "x$with_zlib" != "xyes" -a "x$with_zlib" != "xautodetect"; then
      if test -d "$with_zlib/lib"; then
        ZLIB_LDFLAGS="-L${with_zlib}/lib"
      else
        ZLIB_LDFLAGS="-L${with_zlib}"
      fi
    fi
  
    if test -d "$with_zlib/include"; then
      ZLIB_CPPFLAGS="-I${with_zlib}/include"
    fi
  
    ZLIB_LIBS="-lz"
  
    saved_CPPFLAGS=$CPPFLAGS
    saved_LDFLAGS=$LDFLAGS
    saved_LIBS=$LIBS

    AC_CHECK_LIB(z, deflate, ,
  	       [
  		dnl Check default zlib install dir
  		LDFLAGS="-L/usr/lib -L/usr/local/lib ${LDFLAGS} ${ZLIB_LDFLAGS}"
  		CPPFLAGS="-I/usr/include -I/usr/local/include ${CPPFLAGS} ${ZLIB_CPPFLAGS}"
                  LIBS="${LIBS} ${ZLIB_LIBS}"
  		AC_TRY_LINK_FUNC(deflate, 
                 [
                    libz_detected=yes
                    AC_DEFINE(HAVE_LIBZ)
                 ], 
                 [ 
                   libz_detected=no 
                   if test "x$with_zlib" != "xautodetect"; then
                    AC_MSG_ERROR([*** zlib missing - please install zlib first or check config.log.
                  *** Please run the configure command with "--with-zlib=no" option if you 
                  *** want to build libNUML without support for gzip/zip compressed NUML file.])
                   else
                     AC_MSG_WARN([*** zlib missing.])
                   fi
                 ]
               )
  	]
      )

    AC_CHECK_HEADER([zlib.h], zlib_h_detected=yes, 
                    [
                      zlib_h_detected="no"
                      if test "x$with_zlib" != "xautodetect"; then
                        AC_MSG_ERROR([*** zlib.h missing - please install zlib first or check config.log.
                  *** Please run the configure command with "--with-zlib=no" option if you 
                  *** want to build libNUML without support for gzip/zip compressed NUML file.])
                      else
                        AC_MSG_WARN([*** zlib.h missing.])
                      fi
                    ]
    )
  
    AC_ARG_WITH(zlib-version-check,
            AC_HELP_STRING([--without-zlib-version-check], [Disable zlib version check]),
      	  [  if test "x$withval" = "xno"; then
  		zlib_check_nonfatal=1
  	     fi
  	  ]
    )
  
    AC_MSG_CHECKING(for possibly buggy zlib)
    AC_RUN_IFELSE([AC_LANG_SOURCE([[
      #include <stdio.h>
      #include <stdlib.h>
      #include <zlib.h>
      int main()
      {
  
      int a=0, b=0, c=0, d=0, n, v;
  	n = sscanf(ZLIB_VERSION, "%d.%d.%d.%d", &a, &b, &c, &d);
  	if (n != 3 && n != 4)
  		exit(1);
  	v = a*1000000 + b*10000 + c*100 + d;
  	fprintf(stderr, "found zlib version %s (%d)\n", ZLIB_VERSION, v);
  
  	/* 1.1.4 is OK */
  	if (a == 1 && b == 1 && c >= 4)
  		exit(0);
  
  	/* 1.2.3 and up are OK */
  	if (v >= 1020300)
  		exit(0);
  
  	exit(2);
      }
      ]])],
      AC_MSG_RESULT(no),
      [ AC_MSG_RESULT(yes)
        if test -z "$zlib_check_nonfatal"; then
          if test "x$with_zlib" != "xautodetect"; then
  	    AC_MSG_ERROR([*** zlib too old - check config.log ***
Your reported zlib version has known security problems.  It's possible your
vendor has fixed these problems without changing the version number.  If you
are sure this is the case, you can disable the check by running
"./configure --without-zlib-version-check".
If you are in doubt, upgrade zlib to version 1.2.3 or greater.
See http://www.gzip.org/zlib/ for details.])
          fi
        else
          AC_MSG_WARN([zlib version may have security problems])
        fi
       ],
       [	AC_MSG_WARN([cross compiling: not checking zlib version]) ]
     )
  
  
    CPPFLAGS=$saved_CPPFLAGS
    LDFLAGS=$saved_LDFLAGS
    LIBS=$saved_LIBS
  
    if test "x$libz_detected" != "xno" -a "x$zlib_h_detected" != "xno"; then
      AC_DEFINE([USE_ZLIB], 1, [Define to 1 to use the Zlib library])
      AC_SUBST(USE_ZLIB, 1)
      AC_SUBST(ZLIB_CPPFLAGS)
      AC_SUBST(ZLIB_LDFLAGS)
      AC_SUBST(ZLIB_LIBS)
  
      dnl We record the USE_XXX flag, for later testing in Makefiles.
  
      LIBNUML_OPTIONS="$LIBNUML_OPTIONS USE_ZLIB"
    else
      AC_MSG_WARN([zlib was not found by autodetection.]) 
      with_zlib=no
      ZLIB_LIBS=""
    fi
  else
    AC_MSG_RESULT([no])
  fi
])
