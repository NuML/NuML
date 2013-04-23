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


#ifndef XMLMemoryBuffer_h
#define XMLMemoryBuffer_h

#include <numl/xml/XMLBuffer.h>

LIBNUML_CPP_NAMESPACE_BEGIN

/** @cond doxygen-libnuml-internal */

class XMLMemoryBuffer : public XMLBuffer
{
public:

  /**
   * Creates a XMLBuffer based on the given sequence of bytes in buffer.
   * This class copies the given character to its local buffer to avoid
   * a potential segmentation fault which could happen if the given
   * character deleted outside during the lifetime of this XMLMemoryBuffer object.
   */
  XMLMemoryBuffer (const char* buffer, unsigned int length);


  /**
   * Destroys this XMLMemoryBuffer.
   */
  virtual ~XMLMemoryBuffer ();


  /**
   * Copies at most nbytes from this XMLMemoryBuffer to the memory pointed
   * to by destination.
   *
   * @return the number of bytes actually copied (may be 0).
   */
  virtual unsigned int copyTo (void* destination, unsigned int bytes);


  /**
   * @return true if there was an error reading from the underlying buffer
   * (i.e. it's null), false otherwise.
   */
  virtual bool error ();


private:

  XMLMemoryBuffer ();
  XMLMemoryBuffer (const XMLMemoryBuffer&);
  XMLMemoryBuffer& operator= (const XMLMemoryBuffer&);


  const char*   mBuffer;
  unsigned int  mLength;
  unsigned int  mOffset;
};

/** @endcond doxygen-libnuml-internal */

LIBNUML_CPP_NAMESPACE_END

#endif  /* XMLMemoryBuffer_h */
