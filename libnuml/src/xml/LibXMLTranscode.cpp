/**
* Begin svn Header
* $Rev$:	Revision of last commit
* $Author$:	Author of last commit
* $Date$:	Date of last commit
* $HeadURL$
* $Id$
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

#include <numl/xml/LibXMLTranscode.h>

/** @cond doxygen-ignored */

using namespace std;

/** @endcond doxygen-ignored */

LIBNUML_CPP_NAMESPACE_BEGIN

/** @cond doxygen-libnuml-internal */

static const string NCRAmp = "&#38;"; 

/**
 * replaces each substring of "str" that matches "tstr" with "rstr". 
 */
int replaceAll(string& str, const string& tstr, const string& rstr)
{
  int    count = 0;
  size_t found = 0;
  const size_t tstrlen = tstr.length(); 

  while (1)
  {
    found = str.find(tstr,found);
    if ( found != string::npos )
    {
      str.replace(found, tstrlen, rstr);
      ++count;
    }
    else
    {
      break;
    }
  }
  
  return count;
}


LibXMLTranscode::operator string ()
{
  if (mBuffer == 0)
  {
    return "";
  }
  else
  {
    string str =  (mLen == -1) ? string(mBuffer) : string(mBuffer, mLen);

    if ( mReplaceNCR )
    {
      //
      // replaces &#38; (numeric character reference of '&') with '&'
      // 
      if ( str.length() >= NCRAmp.length() ) 
        LIBNUML_CPP_NAMESPACE ::replaceAll(str, NCRAmp,"&");
    }

    return str;
  }
}


/** @endcond doxygen-libnuml-internal */

LIBNUML_CPP_NAMESPACE_END

