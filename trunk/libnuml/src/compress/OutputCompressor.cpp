/**
* Begin svn Header
* $Rev::		$:	Revision of last commit
* $Author::		$:	Author of last commit
* $Date::		$:	Date of last commit
* $HeadURL::	$
* $Id::			$
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

#include <ostream>
#include <fstream>
#include <iostream>
#include <new>

#include <numl/compress/OutputCompressor.h>

#ifdef USE_ZLIB
#include <numl/compress/zfstream.h>
#include <numl/compress/zipfstream.h>
#endif //USE_ZLIB

#ifdef USE_BZ2
#include <numl/compress/bzfstream.h>
#endif //USE_BZ2

using namespace std;

LIBNUML_CPP_NAMESPACE_BEGIN

/**
 * Opens the given gzip file as a gzofstream (subclass of std::ofstream class) object
 * for write access and returned the stream object.
 *
 * @return a ostream* object bound to the given gzip file or NULL if the initialization
 * for the object failed.
 */
std::ostream* 
OutputCompressor::openGzipOStream(const std::string& filename)
{
#ifdef USE_ZLIB
  return new(std::nothrow) gzofstream(filename.c_str(), ios_base::out | ios_base::binary);
#else
  throw ZlibNotLinked();
  return NULL; // never reached
#endif
}


/**
 * Opens the given bzip2 file as a bzofstream (subclass of std::ofstream class) object
 * for write access and returned the stream object.
 *
 * @return a ostream* object bound to the given bzip2 file or NULL if the initialization
 * for the object failed.
 */
std::ostream* 
OutputCompressor::openBzip2OStream(const std::string& filename)
{
#ifdef USE_BZ2
  return new(std::nothrow) bzofstream(filename.c_str(), ios_base::out | ios_base::binary);
#else
  throw Bzip2NotLinked();
  return NULL; // never reached
#endif
}


/**
 * Opens the given zip file as a zipofstream (subclass of std::ofstream class) object
 * for write access and returned the stream object.
 *
 * @return a ostream* object bound to the given zip file or NULL if the initialization
 * for the object failed.
 */
std::ostream* 
OutputCompressor::openZipOStream(const std::string& filename, const std::string& filenameinzip)
{
#ifdef USE_ZLIB
  return new(std::nothrow) zipofstream(filename.c_str(), filenameinzip.c_str(), 
                                       ios_base::out | ios_base::binary);
#else
  throw ZlibNotLinked();
  return NULL; // never reached
#endif
}

LIBNUML_CPP_NAMESPACE_END

/** @endcond doxygen-libnuml-internal */
