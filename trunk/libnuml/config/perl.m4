dnl
dnl Filename    : perl.m4
dnl Description : Autoconf macro to check for existence of Perl
dnl Author(s)   : Mike Hucka
dnl Organization: SBRML Team
dnl Created     : 2005-05-01
dnl Revision    : $Id: perl.m4 8909 2009-01-19 07:16:58Z mhucka $
dnl $HeadURL: https://sbrml.svn.sourceforge.net/svnroot/sbrml/branches/rel-4-0-0/config/perl.m4 $
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
dnl Check --with-perl[=PREFIX]
dnl

AC_DEFUN([CONFIG_PROG_PERL],
[
  AC_ARG_VAR([PERL])

  AC_ARG_WITH(perl,
              AC_HELP_STRING([--with-perl=PREFIX],
                             [Generate Perl interface library [[default=no]]]),
	      [with_perl=$withval],
	      [with_perl=no])

  if test $with_perl != no; then

    dnl Find a perl executable.

    if test $with_perl != yes; then
      AC_PATH_PROG([PERL], [perl], [no], [$with_perl/bin])
    else
      AC_PATH_PROG([PERL], [perl])
    fi

    if test $PERL != "perl" && ! test -f $PERL;
    then
      AC_MSG_ERROR([*** $PERL missing - please install first or check config.log ***])
    fi

    CHECK_MK=`($PERL -mExtUtils::MakeMaker -e '{print "OK"}') 2>/dev/null`
    if test x$CHECK_MK != xOK;
    then
      AC_MSG_ERROR([*** ExtUtils::MakeMaker module is missing - please install first or check config.log ***])
    fi

    AC_DEFINE([USE_PERL], 1, [Define to 1 to use Perl])
    AC_SUBST(USE_PERL, 1)

    AC_SUBST(PERL_CPPFLAGS)
    AC_SUBST(PERL_LDFLAGS)
    AC_SUBST(PERL_LIBS)

  fi

  dnl We record the USE_XXX flag, for later testing in Makefiles.

  LIBSBRML_OPTIONS="$LIBSBRML_OPTIONS USE_PERL"

])
