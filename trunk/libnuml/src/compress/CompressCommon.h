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

#ifndef CompressCommon_h
#define CompressCommon_h

#include <exception>
#include <numl/common/extern.h>


LIBNUML_CPP_NAMESPACE_BEGIN

/**
 *
 *  This exception will be thrown if a function which depends on
 *  some library invoked and underlying libNUML is not linked with
 *  the library.
 *
 */
class LIBNUML_EXTERN NotLinked : public std::exception
{
public:
   NotLinked() throw() { }
   virtual ~NotLinked() throw() {}
};


/**
 *
 * This exception will be thrown if a function which depends on 
 * zlib invoked and underlying libNUML is not linked with zlib.
 *
 */
class LIBNUML_EXTERN ZlibNotLinked : public NotLinked
{
public:
   ZlibNotLinked() throw() { }
   virtual ~ZlibNotLinked() throw() {}
};


/**
 *
 *  This exception will be thrown if a function which depends on 
 *  bzip2 library invoked and underlying libNUML is not linked with
 *  bzip2.
 *
 */
class LIBNUML_EXTERN Bzip2NotLinked : public NotLinked
{
public:
   Bzip2NotLinked() throw() { }
   virtual ~Bzip2NotLinked() throw() {}
};


/**
 * Predicate returning @c true or @c false depending on whether
 * underlying libNUML is linked with zlib.
 *
 * @return @c true if libNUML is linked with zlib, @c false otherwise.
 */
LIBNUML_EXTERN
bool hasZlib(); 


/**
 * Predicate returning @c true or @c false depending on whether
 * underlying libNUML is linked with bzip2.
 *
 * @return @c true if libNUML is linked with bzip2, @c false otherwise.
 */
LIBNUML_EXTERN
bool hasBzip2();

LIBNUML_CPP_NAMESPACE_END

#endif //CompressCommon_h

/** @endcond doxygen-libnuml-internal */
