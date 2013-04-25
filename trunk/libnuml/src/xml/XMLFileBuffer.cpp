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

#include <cstdio>
#include<iostream>
#include<fstream>

#include <numl/xml/XMLFileBuffer.h>
#include <numl/compress/CompressCommon.h>
#include <numl/compress/InputDecompressor.h>

/** @cond doxygen-ignored */

using namespace std;

/** @endcond doxygen-ignored */

LIBNUML_CPP_NAMESPACE_BEGIN

/** @cond doxygen-libnuml-internal */

/*
 * Creates a XMLBuffer based on the given file.  The file will be opened
 * for reading.
 */
XMLFileBuffer::XMLFileBuffer (const string& filename) :
   mFilename( filename )
{
  mStream = NULL;

  try
  {
    // open an uncompressed XML file
    if ( string::npos != filename.find(".xml", filename.length() -  4) )
    {
      mStream = new(std::nothrow) std::ifstream(filename.c_str());
    }
    // open a gzip file
    else if ( string::npos != filename.find(".gz", filename.length() -  3) )
    {
      mStream = InputDecompressor::openGzipIStream(filename);
    }
    // open a bz2 file
    else if ( string::npos != filename.find(".bz2", filename.length() - 4) )
    {
      mStream = InputDecompressor::openBzip2IStream(filename);
    }
    // open a zip file
    else if ( string::npos != filename.find(".zip", filename.length() - 4) )
    {
      mStream = InputDecompressor::openZipIStream(filename);
    }
    else
    {
      // open an uncompressed file
      mStream = new(std::nothrow) std::ifstream(filename.c_str());
    }
  }
  catch ( ZlibNotLinked& zlib)
  {
    // liBNUML is not linked with zlib.
    throw;
  }
  catch ( Bzip2NotLinked& bz2)
  {
    // liBNUML is not linked with bzip2.
    throw;
  }

  if(mStream != NULL)
  {
    // invoke peek() to set a badbit when the given compressed file is unreadable
    mStream->peek();
  }

}


/*
 * Destroys this XMLFileBuffer and closes the underlying file.
 */
XMLFileBuffer::~XMLFileBuffer ()
{
  if(mStream) delete mStream;
}


/*
 * Copies at most nbytes from this XMLFileBuffer to the memory pointed to
 * by destination.
 *
 * @return the number of bytes actually copied (may be 0).
 */
unsigned int
XMLFileBuffer::copyTo (void* destination, unsigned int bytes) 
{
  if (mStream)
  {
    mStream->read( static_cast<char*>(destination), bytes);
    return mStream->gcount();
  }
  else
  {
    return 0;
  }
}


/*
 * @return true if there was an error reading from the underlying buffer,
 * false otherwise.
 */
bool
XMLFileBuffer::error ()
{
  if (mStream) return (!mStream->eof() && mStream->fail());
  else return true;
}

/** @endcond doxygen-libnuml-internal */

LIBNUML_CPP_NAMESPACE_END

