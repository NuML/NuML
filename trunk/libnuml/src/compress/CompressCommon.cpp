/**
* Begin svn Header
* $Rev$:	Revision of last commit
* $Author$:	Author of last commit
* $Date$:	Date of last commit
* $HeadURL$
* $Id$
* End svn Header
* ***************************************************************************
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
* 	SBML Team
* 	Control and Dynamical Systems, MC 107-81
* 	California Institute of Technology
* 	Pasadena, CA, 91125, USA
*
*  	http://www.sbml.org
* 	mailto:sbml-team@caltech.edu
*
* Adapted for NUML by:
*
* 	NUML Team
* 	Computational Systems Biology Group
* 	School of Computer Science
* 	The University of Manchester
* 	Manchester, M1 7DN UK
* 	mailto:josephodada@gmail.com
*
*   Contributor(s):
*   Joseph O. Dada, The University of Manchester - initial LIBNUML API and implementation
* ***************************************************************************
**/

#include <numl/compress/CompressCommon.h>

using namespace std;

LIBNUML_CPP_NAMESPACE_BEGIN

/**
 * Predicate returning @c true or @c false depending on whether
 * libNUML is linked with zlib at compile time.
 *
 * @return @c true if zlib is linked, @c false otherwise.
 */
LIBNUML_EXTERN
bool hasZlib() 
{
#ifdef USE_ZLIB
  return true;
#else
  return false;
#endif // USE_ZLIB
}

/**
 * Predicate returning @c true or @c false depending on whether
 * libNUML is linked with bzip2 at compile time.
 *
 * @return @c true if bzip2 is linked, @c false otherwise.
 */
LIBNUML_EXTERN
bool hasBzip2() 
{
#ifdef USE_BZ2
  return true;
#else
  return false;
#endif // USE_BZ2
}

LIBNUML_CPP_NAMESPACE_END

/** @endcond doxygen-libnuml-internal */
