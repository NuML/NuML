/**
* Begin svn Header
* $Rev::		$:	Revision of last commit
* $Author::		$:	Author of last commit
* $Date::		$:	Date of last commit
* $HeadURL::	$
* $Id::			$
* End svn Header
* ****************************************************************************
* This file is part of libNUML.  Please visit http://code.google.com/p/numl/for more
* information about NUML, and the latest version of libNUML.
* Copyright (c) 2013 The University of Manchester.
*
* This library is free software; you can redistribute it and/or modify it
* under the terms of the GNU Lesser General Public License as published
* by the Free Software Foundation.  A copy of the license agreement is
* provided in the file named "LICENSE.txt" included with this software
* distribution and also available online as http://www.gnu.org/licenses/lgpl.html
*
* The original code was initially developed by:
*
*      SBML Team
*      Control and Dynamical Systems, MC 107-81
*      California Institute of Technology
*      Pasadena, CA, 91125, USA
*
*      http://www.sbml.org
*      mailto:sbml-team@caltech.edu
*
* Adapted for NUML by:
*
*   NUML Team
*   Computational Systems Biology Group
*   School of Computer Science
*   The University of Manchester
*   Manchester, UK
*
*   Contributor(s):
*   Joseph O. Dada, The University of Manchester - initial LIBNUML API and implementation
* ****************************************************************************
**/

#ifndef XercesTranscode_h
#define XercesTranscode_h

#ifdef __cplusplus

#include <string>
#include <xercesc/util/XMLString.hpp>
#include <numl/common/libnuml-namespace.h>

LIBNUML_CPP_NAMESPACE_BEGIN

#if XERCES_VERSION_MAJOR <= 2
typedef unsigned int XercesSize_t;
typedef XMLSSize_t   XercesFileLoc;
#else
typedef XMLSize_t    XercesSize_t;
typedef XMLFileLoc   XercesFileLoc;
#endif

/** @cond doxygen-libnuml-internal */

/**
 * Transcodes a Xerces-C++ XMLCh* string to the UTF8 string.  This
 * class offers implicit conversion to a C++ string and destroys the
 * transcoded buffer when the XercesTranscode object goes out of scope.
 */
class XercesTranscode
{
public:

  XercesTranscode (const XMLCh* s) :
    mBuffer( transcodeToUTF8(s) ) { }

  ~XercesTranscode     () { delete [] mBuffer; }
  operator std::string () { return std::string(mBuffer); }


private:

  char* mBuffer;

  XercesTranscode  ();
  XercesTranscode  (const XercesTranscode&);
  XercesTranscode& operator= (const XercesTranscode&);

 /**
  * convert the given internal XMLCh* string to the UTF-8 char* string.
  */
  char* transcodeToUTF8(const XMLCh* src_str);

};

/** @endcond doxygen-libnuml-internal */

LIBNUML_CPP_NAMESPACE_END

#endif  /* __cplusplus */
#endif  /* XercesTranscode_h */
