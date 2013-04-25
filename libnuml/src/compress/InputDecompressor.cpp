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


#include <istream>
#include <fstream>
#include <sstream>
#include <iostream>
#include <new>
#include <algorithm>
#include <cstring>

#include <numl/compress/InputDecompressor.h>

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
 * Opens the given gzip file as a gzifstream (subclass of std::ifstream class) object
 * for read access and returned the stream object.
 *
 * @return a istream* object bound to the given gzip file or NULL if the initialization
 * for the object failed.
 */
std::istream* 
InputDecompressor::openGzipIStream (const std::string& filename)
{
#ifdef USE_ZLIB
  return new(std::nothrow) gzifstream(filename.c_str(), ios_base::in | ios_base::binary);
#else
  throw ZlibNotLinked();
  return NULL; // never reached
#endif
}


/**
 * Opens the given bzip2 file as a bzifstream (subclass of std::ifstream class) object
 * for read access and returned the stream object.
 *
 * @return a istream* object bound to the given bzip2 file or NULL if the initialization
 * for the object failed.
 */
std::istream* 
InputDecompressor::openBzip2IStream (const std::string& filename)
{
#ifdef USE_BZ2
  return new(std::nothrow) bzifstream(filename.c_str(), ios_base::in | ios_base::binary);
#else
  throw Bzip2NotLinked();
  return NULL; // never reached
#endif
}


/**
 * Opens the given zip file as a zipifstream (subclass of std::ifstream class) object
 * for read access and returned the stream object.
 *
 * @return a istream* object bound to the given zip file or NULL if the initialization
 * for the object failed.
 *
 * @note The first file in the given zip archive file will be opened if the zip archive
 * contains two or more files.
 */
std::istream* 
InputDecompressor::openZipIStream (const std::string& filename)
{
#ifdef USE_ZLIB
  return new(std::nothrow) zipifstream(filename.c_str(), ios_base::in | ios_base::binary);
#else
  throw ZlibNotLinked();
  return NULL; // never reached
#endif
}


/**
 * Opens the given gzip file and returned the string in the file.
 *
 * @return a string, the string in the given file, or empty string if 
 * failed to open the file.
 */
char* 
InputDecompressor::getStringFromGzip (const std::string& filename) 
{
#ifdef USE_ZLIB
  std::ostringstream oss;
  gzifstream in(filename.c_str(), ios_base::in | ios_base::binary);
  istreambuf_iterator<char> in_itr(in);
  ostreambuf_iterator<char> out_itr(oss);

  std::copy(in_itr, istreambuf_iterator<char>(), out_itr);

  return strdup(oss.str().c_str());
#else
  throw ZlibNotLinked();
  return NULL; // never reached
#endif
}


/**
 * Opens the given bzip2 file and returned the string in the file.
 *
 * @return a string, the string in the given file, or empty string if failed to open
 * the file.
 */
char* 
InputDecompressor::getStringFromBzip2 (const std::string& filename) 
{
#ifdef USE_BZ2
  std::ostringstream oss;
  bzifstream in(filename.c_str(), ios_base::in | ios_base::binary);
  istreambuf_iterator<char> in_itr(in);
  ostreambuf_iterator<char> out_itr(oss);

  std::copy(in_itr, istreambuf_iterator<char>(), out_itr);

  return strdup(oss.str().c_str());
#else
  throw Bzip2NotLinked();
  return NULL; // never reached
#endif
}


/**
 * Opens the given zip file and returned the string in the file.
 *
 * @return a string, the string in the given file, or empty string if failed to open
 * the file.
 *
 * @note The first file in the given zip archive file will be opened if the zip archive
 * contains two or more files.
 */
char* 
InputDecompressor::getStringFromZip (const std::string& filename) 
{
#ifdef USE_ZLIB
  std::ostringstream oss;
  zipifstream in(filename.c_str(), ios_base::in | ios_base::binary);
  istreambuf_iterator<char> in_itr(in);
  ostreambuf_iterator<char> out_itr(oss);

  std::copy(in_itr, istreambuf_iterator<char>(), out_itr);

  return strdup(oss.str().c_str());
#else
  throw ZlibNotLinked();
  return NULL; // never reached
#endif
}

LIBNUML_CPP_NAMESPACE_END

/** @endcond doxygen-libnuml-internal */
