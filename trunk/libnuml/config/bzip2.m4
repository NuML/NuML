﻿dnl
dnl Filename    : bzip2.m4
dnl Description : Autoconf macro to check for existence of bzip2 library
dnl Author(s)   : NUML Team <numl-team@caltech.edu>
dnl Organization: California Institute of Technology
dnl Created     : 2008-07-04
dnl Revision    : $Id: bzip2.m4 8826 2009-01-12 23:56:28Z ajouraku $
dnl $HeadURL: https://numl.svn.sourceforge.net/svnroot/numl/branches/rel-4-0-0/config/bzip2.m4 $
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
# This bzip2 check code is based on the zlib check code in configure.ac
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

AC_DEFUN([CONFIG_LIB_BZ2],
[
  AC_ARG_WITH([bzip2],
    AC_HELP_STRING([--with-bzip2=PREFIX], 
	           [Enable reading/writing files compressed with bzip2 [[default=autodetect]] ]
              ),
    [with_bzip2="$withval"], 
    [with_bzip2=autodetect]
  )

  if test "x$with_bzip2" = "xautodetect"; then
    if test "x$enable_compression" = "xno"; then
      with_bzip2=no
    fi
  fi

  AC_MSG_CHECKING(for bzip2 library)
  if test "x$with_bzip2" != "xno" ; then
    AC_MSG_RESULT(yes)

    if test "x$with_bzip2" != "xyes" -a "x$with_bzip2" != "xautodetect"; then
      if test -d "$with_bzip2/lib"; then
        BZ2_LDFLAGS="-L${with_bzip2}/lib"
      else
        BZ2_LDFLAGS="-L${with_bzip2}"
      fi
    fi
  
    if test -d "$with_bzip2/include"; then
      BZ2_CPPFLAGS="-I${with_bzip2}/include"
    fi
  
    BZ2_LIBS="-lbz2"
  
    saved_CPPFLAGS=$CPPFLAGS
    saved_LDFLAGS=$LDFLAGS
    saved_LIBS=$LIBS

    AC_CHECK_LIB(bz2, BZ2_bzopen, ,
  	       [
  		dnl Check default bzip2 install dir
  		LDFLAGS="-L/usr/lib -L/usr/local/lib ${LDFLAGS} ${BZ2_LDFLAGS}"
  		CPPFLAGS="-I/usr/include -I/usr/local/include ${CPPFLAGS} ${BZ2_CPPFLAGS}"
                  LIBS="${LIBS} ${BZ2_LIBS}"
  		AC_TRY_LINK_FUNC(BZ2_bzopen, 
                  [
                    libbz2_detected=yes
                    AC_DEFINE(HAVE_BZ2)
                  ],
  		  [
                    libbz2_detected=no
                    if test "x$with_bzip2" != "xautodetect"; then
                      AC_MSG_ERROR([*** bzip2 missing - please install bzip2 first or check config.log.
                    *** Please run the configure command with "--with-bzip2=no" option if you
                    *** want to build libNUML without support for bzip2 compressed NUML file.])
                    else
                     AC_MSG_WARN([*** bzip2 missing.])
                    fi
  		  ]
  		)
  	]
     )
  
    AC_CHECK_HEADER([bzlib.h], bzlib_h_detected=yes,
  		    [
                      bzlib_h_detected="no"
                      if test "x$with_bzip2" != "xautodetect"; then
                        AC_MSG_ERROR([*** bzlib.h missing - please install bzip2 first or check config.log.
                  *** Please run the configure command with "--with-bzip2=no" option if you
                  *** want to build libNUML without support for bzip2 compressed NUML file.])
                      else
                        AC_MSG_WARN([*** bzlib.h missing.])
                      fi
  		    ]
    )
  
    CPPFLAGS=$saved_CPPFLAGS
    LDFLAGS=$saved_LDFLAGS
    LIBS=$saved_LIBS

    if test "x$libbz2_detected" != "xno" -a "x$bzlib_h_detected" != "xno"; then  
      AC_DEFINE([USE_BZ2], 1, [Define to 1 to use the bzip2 library])
      AC_SUBST(USE_BZ2, 1)
      AC_SUBST(BZ2_CPPFLAGS)
      AC_SUBST(BZ2_LDFLAGS)
      AC_SUBST(BZ2_LIBS)
  
      dnl We record the USE_XXX flag, for later testing in Makefiles.
  
      LIBNUML_OPTIONS="$LIBNUML_OPTIONS USE_BZ2"
    else
      AC_MSG_WARN([bzip2 was not found by autodetection.]) 
      with_bzip2=no
      BZ2_LIBS=""
    fi
  else
    AC_MSG_RESULT(no)
  fi
])
