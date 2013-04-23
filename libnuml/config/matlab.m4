<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.0 Transitional//EN">
<HTML>
<HEAD>
	<META HTTP-EQUIV="CONTENT-TYPE" CONTENT="text/html; charset=utf-8">
	<TITLE></TITLE>
	<META NAME="GENERATOR" CONTENT="LibreOffice 3.4  (Linux)">
	<META NAME="CREATED" CONTENT="0;0">
	<META NAME="CHANGED" CONTENT="20130403;11503300">
</HEAD>
<BODY LANG="en-GB" DIR="LTR">
<P STYLE="margin-bottom: 0cm">dnl dnl Filename : matlab.m4 dnl
Description : Autoconf macro for MATLAB configuration dnl Author(s) :
Mike Hucka dnl Created : 2004-08-02 dnl Revision : $Id: matlab.m4
8909 2009-01-19 07:16:58Z mhucka $ dnl $HeadURL:
https://numl.svn.sourceforge.net/svnroot/numl/branches/rel-4-0-0/config/matlab.m4
$ dnl dnl<!------------------------------------------------------------------------- dnl This file is part of libSBRML.  Please visit http://sbrml.org for more
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
dnl --------------------------------------------------------------------- -->
*/ AC_DEFUN([CONFIG_PROG_MATLAB], [ AC_ARG_WITH([matlab],
AC_HELP_STRING([--with-matlab=PREFIX], [Generate MATLAB interface
library [[default=no]]]), [with_matlab=$withval], [with_matlab=no])
if test $with_matlab != no; then if test $with_matlab != yes; then
dnl Remove needless trailing slashes because it can confuse tests
later. with_matlab=`echo $with_matlab | sed -e 's,\(.*\)/$,\1,g'`
AC_PATH_PROG([MEX], [mex], [no], [$with_matlab/bin])
AC_PATH_PROG([MATLAB], [matlab], [no], [$with_matlab/bin]) else
AC_PATH_PROG([MEX], [mex]) AC_PATH_PROG([MATLAB], [matlab]) fi if
test -z &quot;$MATLAB&quot; -o &quot;$MATLAB&quot; = &quot;no&quot;;
then AC_MSG_ERROR([Could not find 'matlab' executable for MATLAB.])
elif test -z &quot;$MEX&quot; -o &quot;$MEX&quot; = &quot;no&quot;;
then AC_MSG_ERROR([Could not find 'mex' executable for MATLAB.]) fi
dnl The mex extension really should be obtained using matlab's dnl
&quot;mexext&quot;, but it lives in the matlab directory and there's
no way dnl to know a priori where that is. After all, users may only
have dnl provided --with-matlab during configuration, without telling
us the dnl matlab installation directory. case $host in
*86-*-darwin*) MEXEXT=&quot;mexmaci&quot; ;; *powerpc-*-darwin*)
MEXEXT=&quot;mexmac&quot; ;; *cygwin*) MEXEXT=&quot;dll&quot; ;;
*x86_64*) MEXEXT=&quot;mexa64&quot; ;; dnl Default is x86. *)
MEXEXT=&quot;mexglx&quot; ;; esac AC_DEFINE([USE_MATLAB], 1, [Define
to 1 to use Matlab]) AC_SUBST(USE_MATLAB, 1)
AC_SUBST(MATLAB_CPPFLAGS) AC_SUBST(MATLAB_LDFLAGS)
AC_SUBST(MATLAB_LIBS) AC_SUBST(MEX_FLAGS) AC_SUBST(MEXEXT) fi dnl We
record the USE_XXX flag, for later testing in Makefiles.
LIBNUML_OPTIONS=&quot;$LIBNUML_OPTIONS USE_MATLAB&quot; ]) 
</P>
</BODY>
</HTML>