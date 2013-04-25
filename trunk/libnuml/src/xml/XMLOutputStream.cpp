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

#include <iostream>
#include <sstream>
#include <fstream>

#include <cstdio>
#include <numl/xml/XMLTriple.h>
#include <numl/xml/XMLOutputStream.h>
#include <numl/util/util.h>
#include <numl/common/common.h>
#include <numl/common/libnuml-version.h>

/** @cond doxygen-ignored */

using namespace std;

/** @endcond doxygen-ignored */

LIBNUML_CPP_NAMESPACE_BEGIN

/**
 * Checks if the given string has a character reference at index in the string.
 *
 * character reference is expressed as follows:
 *
 *  CharRef ::=  '&#' [0-9]+ ';' | '&#x' [0-9a-fA-F]+ ';'
 *
 * This function is internal implementation.
 */
bool hasCharacterReference(const std::string &chars, size_t index)
{
  const std::string decChars = "0123456789";
  const std::string hexChars = "0123456789abcdefABCDEF";

  if ((chars.length() - 1) <= index)
  {
    return false;
  }
  else if (chars.at(index) != '&')
  {
    return false;
  }
  else if (chars.at(index+1) != '#')
  {
    return false;
  }
  else if (chars.at(index+2) == 'x')
  {
    //
    // the character reference uses hex characters (e.g. &#x00A8; ) if any
    //
    size_t pos = chars.find_first_not_of(hexChars, index+3);
    
    if (pos == std::string::npos)
    {
      // ';' is not found
      return false;
    }    
    else if (pos < index + 4)
    {
      // hex characters are not found
      return false;
    }
    else if (chars.at(pos) != ';')
    {
      // ';' is not found immediately after hex characters
      return false;
    }
  }
  else
  {
    //
    // the character reference uses deciaml characters (e.g. &#0185; ) if any
    //
    size_t pos = chars.find_first_not_of(decChars, index+2);
    
    if (pos == std::string::npos)
    {
      // ';' is not found
      return false;
    }    
    else if (pos < index + 3)
    {
      // decimal characters are not found
      return false;
    }
    else if (chars.at(pos) != ';')
    {
      // ';' is not found immediately after decimal characters
      return false;
    }
  }

  return true;
}   


/**
 * Checks if the given string has a predefined entity at index in the string.
 *
 * predefined entities are expressed as follows:
 *
 *  1) &amp;
 *  2) &apos;
 *  3) &lt;
 *  4) &gt;
 *  5) &quot;
 *
 * This function is internal implementation.
 */
bool hasPredefinedEntity(const std::string &chars, size_t index)
{
  if ((chars.length() - 1) <= index)
  {
    return false;
  }

  if (chars.find("&amp;",index) == index)
  {
    return true;
  }
  else if (chars.find("&apos;",index) == index)
  {
    return true;
  }
  else if (chars.find("&lt;",index) == index)
  {
    return true;
  }
  else if (chars.find("&gt;",index) == index)
  {
    return true;
  }
  else if (chars.find("&quot;",index) == index)
  {
    return true;
  }
     
  return false;
}   


/*
 * Creates a new XMLOutputStream that wraps stream.
 */
XMLOutputStream::XMLOutputStream (  std::ostream&       stream
                                  , const std::string&  encoding
                                  , bool                writeXMLDecl
                                  , const std::string&  programName
                                  , const std::string&  programVersion) :
   mStream  ( stream   )
 , mEncoding( encoding )
 , mInStart ( false    )
 , mDoIndent( true     )
 , mIndent  ( 0        )
 , mInText  ( false    )
 , mSkipNextIndent ( false    )
 , mNextAmpersandIsRef( false )
{
  unsetStringStream();
  mStream.imbue( locale::classic() );
  if (writeXMLDecl) this->writeXMLDecl();
  this->writeComment(programName, programVersion);
}


/*
 * Writes the given XML end element name to this XMLOutputStream.
 */
void
XMLOutputStream::endElement (const std::string& name)
{
  if (mInStart)
  {
    mInStart = false;
    mStream << '/' << '>';
  }
  else if (mInText)
  {
    mInText = false;
    mSkipNextIndent = false;
    mStream << '<' << '/';
    writeName(name);
    mStream << '>';
  }
  else
  {
    downIndent();
    writeIndent(true); 

    mStream << '<' << '/';
    writeName(name);
    mStream << '>';
  }
}


/*
 * Writes the given XML end element 'prefix:name' to this
 * XMLOutputStream.
 */
void
XMLOutputStream::endElement (const XMLTriple& triple)
{
  if (mInStart)
  {
    mInStart = false;
    mStream << '/' << '>';
  }
  else if (mInText)
  {
    mInText = false;
    mSkipNextIndent = false;
    mStream << '<' << '/';
    writeName(triple);
    mStream << '>';
  }
  else
  {
    downIndent();
    writeIndent(true); 

    mStream << '<' << '/';
    writeName(triple);
    mStream << '>';
  }
}


/*
 * Turns automatic indentation on or off for this XMLOutputStream.
 */
void
XMLOutputStream::setAutoIndent (bool indent)
{
  mDoIndent = indent;
}


/*
 * Writes the given XML start element name to this XMLOutputStream.
 */
void
XMLOutputStream::startElement (const std::string& name)
{
  if (mInStart)
  {
    mStream << '>';
    upIndent();
  }

  mInStart = true;

  if (mInText && mSkipNextIndent)
  {
    mSkipNextIndent = false;
  }
  else
  {
    writeIndent();
  }

  mStream << '<';
  writeName(name);
}


/*
 * Writes the given XML start element 'prefix:name' to this
 * XMLOutputStream.
 */
void
XMLOutputStream::startElement (const XMLTriple& triple)
{
  if (mInStart)
  {
    mStream << '>';
    upIndent();
  }

  mInStart = true;

  if (mInText && mSkipNextIndent)
  {
    mSkipNextIndent = false;
  }
  else
  {
    writeIndent();
  }

  mStream << '<';
  writeName(triple);
}


/*
 * Writes the given XML start and end element name to this XMLOutputStream.
 */
void
XMLOutputStream::startEndElement (const std::string& name)
{
  if (mInStart)
  {
    mStream << '>';
    upIndent();
  }

  if (mSkipNextIndent)
    mSkipNextIndent = false;

  mInStart = false;

  if (mInText && mSkipNextIndent)
  {
    mSkipNextIndent = false;
  }
  else
  {
    writeIndent();
  }

  mStream << '<';
  writeName(name);
  mStream << '/' << '>';
}


/*
 * Writes the given XML start and end element 'prefix:name' to this
 * XMLOutputStream.
 */
void
XMLOutputStream::startEndElement (const XMLTriple& triple)
{
  if (mInStart)
  {
    mStream << '>';
    upIndent();
  }

  if (mSkipNextIndent)
    mSkipNextIndent = false;

  mInStart = false;

  if (mInText && mSkipNextIndent)
  {
    mSkipNextIndent = false;
  }
  else
  {
    writeIndent();
  }

  mStream << '<';
  writeName(triple);
  mStream << '/' << '>';
}


/*
 * Writes the given attribute, name="value" to this XMLOutputStream.
 */
void
XMLOutputStream::writeAttribute (const std::string& name, const std::string& value)
{
  if ( value.empty() ) return;

  mStream << ' ';

  writeName ( name  );
  writeValue( value );
}


/*
 * Writes the given attribute, prefix:name="value" to this
 * XMLOutputStream.
 */
void
XMLOutputStream::writeAttribute (const XMLTriple& triple, const std::string& value)
{
  mStream << ' ';

  writeName ( triple );
  writeValue( value  );
}


/*
 * Writes the given attribute, name="true" or name="false" to this
 * XMLOutputStream.
 */
void
XMLOutputStream::writeAttribute (const std::string& name, const bool& value)
{
  mStream << ' ';

  writeName ( name  );
  writeValue( value );
}


/*
 * Writes the given attribute, prefix:name="true" or prefix:name="false" to
 * this XMLOutputStream.
 */
void
XMLOutputStream::writeAttribute (const XMLTriple& triple, const bool& value)
{
  mStream << ' ';

  writeName ( triple );
  writeValue( value  );
}


/*
 * Writes the given attribute, name="value" to this XMLOutputStream.
 */
void
XMLOutputStream::writeAttribute (const std::string& name, const double& value)
{
  mStream << ' ';

  writeName ( name  );
  writeValue( value );
}


/*
 * Writes the given attribute, prefix:name="value" to this XMLOutputStream.
 */
void
XMLOutputStream::writeAttribute (const XMLTriple& triple, const double& value)
{
  mStream << ' ';

  writeName ( triple );
  writeValue( value  );
}


/*
 * Writes the given attribute, name="value" to this XMLOutputStream.
 */
void
XMLOutputStream::writeAttribute (const std::string& name, const long& value)
{
  mStream << ' ';

  writeName ( name  );
  writeValue( value );
}


/*
 * Writes the given attribute, prefix:name="value" to this XMLOutputStream.
 */
void
XMLOutputStream::writeAttribute (const XMLTriple& triple, const long& value)
{
  mStream << ' ';

  writeName ( triple );
  writeValue( value  );
}


/*
 * Writes the given attribute, name="value" to this XMLOutputStream.
 */
void
XMLOutputStream::writeAttribute (const std::string& name, const int& value)
{
  mStream << ' ';

  writeName ( name  );
  writeValue( value );
}


/*
 * Writes the given attribute, prefix:name="value" to this
 * XMLOutputStream.
 */
void
XMLOutputStream::writeAttribute (const XMLTriple& triple, const int& value)
{
  mStream << ' ';

  writeName ( triple );
  writeValue( value  );
}


/*
 * Writes the given attribute, name="value" to this XMLOutputStream.
 */
void
XMLOutputStream::writeAttribute (const std::string& name, const unsigned int& value)
{
  mStream << ' ';

  writeName ( name  );
  writeValue( value );
}


/*
 * Writes the given attribute, prefix:name="value" to this
 * XMLOutputStream.
 */
void
XMLOutputStream::writeAttribute (  const XMLTriple&     triple
                                 , const unsigned int&  value )
{
  mStream << ' ';

  writeName ( triple );
  writeValue( value  );
}


/*
 * Decreases the indentation level for this XMLOutputStream.
 */
void
XMLOutputStream::downIndent ()
{
  if (mDoIndent && mIndent) --mIndent;
}


/*
 * Increases the indentation level for this XMLOutputStream.
 */
void
XMLOutputStream::upIndent ()
{
  if (mDoIndent) ++mIndent;
}


/** @cond doxygen-libnuml-internal */
/*
 * Outputs indentation whitespace.
 */
void
XMLOutputStream::writeIndent (bool isEnd)
{
  if (mDoIndent)
  {
    if (mIndent > 0 || isEnd) mStream << endl;
    for (unsigned int n = 0; n < mIndent; ++n) mStream << ' ' << ' ';
  }
}
/** @endcond doxygen-libnuml-internal */


/** @cond doxygen-libnuml-internal */
/*
 * Outputs the given characters to the underlying stream.
 */
void
XMLOutputStream::writeChars (const std::string& chars)
{
  for (size_t i=0; i < chars.length(); i++)
  {
    const char& c = chars.at(i);
    if ( c == '&' && 
        (LIBNUML_CPP_NAMESPACE ::hasCharacterReference(chars, i) ||
         LIBNUML_CPP_NAMESPACE ::hasPredefinedEntity(chars,i)) )
      mNextAmpersandIsRef = true;

    *this << c;
  }
}
/** @endcond doxygen-libnuml-internal */


/** @cond doxygen-libnuml-internal */
/*
 * Outputs name.
 */
void
XMLOutputStream::writeName (const std::string& name)
{
  writeChars(name);
}
/** @endcond doxygen-libnuml-internal */


/** @cond doxygen-libnuml-internal */
/*
 * Outputs prefix:name.
 */
void
XMLOutputStream::writeName (const XMLTriple& triple)
{
  if ( !triple.getPrefix().empty() )
  {
    writeChars( triple.getPrefix() );
    mStream << ':';
  }

  writeChars( triple.getName() );
}
/** @endcond doxygen-libnuml-internal */


/** @cond doxygen-libnuml-internal */
/*
 * Outputs value in quotes.
 */
void
XMLOutputStream::writeValue (const std::string& value)
{
  mStream << '=' << '"';
  writeChars(value);
  mStream << '"';
}
/** @endcond doxygen-libnuml-internal */


/** @cond doxygen-libnuml-internal */
/*
 * Outputs "true" or "false" in quotes.
 */
void
XMLOutputStream::writeValue (const bool& value)
{
  mStream << '=' << '"' << (value ? "true" : "false") << '"';
}
/** @endcond doxygen-libnuml-internal */


/** @cond doxygen-libnuml-internal */
/*
 * Outputs the double value in quotes, or "INF", "-INF", or "NaN".
 */
void
XMLOutputStream::writeValue (const double& value)
{
  mStream << '=' << '"';

  if (value != value)
  {
    mStream << "NaN";
  }
  else if (value == numeric_limits<double>::infinity())
  {
    mStream << "INF";
  }
  else if (value == - numeric_limits<double>::infinity())
  {
    mStream << "-INF";
  }
  else
  {
    mStream.precision(LIBNUML_DOUBLE_PRECISION);
    mStream <<   value;
  }

  mStream << '"';
}
/** @endcond doxygen-libnuml-internal */


/** @cond doxygen-libnuml-internal */
/*
 * Outputs the long value in quotes.
 */
void
XMLOutputStream::writeValue (const long& value)
{
  mStream << '=' << '"' << value << '"';
}
/** @endcond doxygen-libnuml-internal */


/** @cond doxygen-libnuml-internal */
/*
 * Outputs the int value in quotes.
 */
void
XMLOutputStream::writeValue (const int& value)
{
  mStream << '=' << '"' << value << '"';
}
/** @endcond doxygen-libnuml-internal */


/** @cond doxygen-libnuml-internal */
/*
 * Outputs the int value in quotes.
 */
void
XMLOutputStream::writeValue (const unsigned int& value)
{
  mStream << '=' << '"' << value << '"';
}
/** @endcond doxygen-libnuml-internal */


/*
 * Writes the XML declaration:
 * <?xml version="1.0" encoding="..."?>
 */
void
XMLOutputStream::writeXMLDecl ()
{
  mStream << "<?xml version=\"1.0\"";

  if ( !mEncoding.empty() ) writeAttribute("encoding", mEncoding);

  mStream << "?>";
  mStream << endl;
}


/*
 * Writes the XML comment:
 *   <!-- Created by <program name> version <program version>
 *   on yyyy-MM-dd HH:mm with libnuml version <libnuml version>. -->
 */
void
XMLOutputStream::writeComment (const std::string& programName, 
                               const std::string& programVersion)
{
  char formattedDateAndTime[17];
  time_t tim=time(NULL);
  tm *now=localtime(&tim);

  sprintf(formattedDateAndTime, "%d-%02d-%02d %02d:%02d",
    now->tm_year+1900, now->tm_mon+1, now->tm_mday, 
    now->tm_hour, now->tm_min);

  if (programName != "")
  {
    mStream << "<!-- Created by " << programName;
    if (programVersion != "")
    {
      mStream << " version " << programVersion;
    }
    mStream << " on " << formattedDateAndTime;
    mStream << " with libNUML version " << getLibNUMLDottedVersion();
    mStream << ". -->";
    mStream << endl;
  }
}


/*
 * Outputs the given characters to the underlying stream.
 */
XMLOutputStream&
XMLOutputStream::operator<< (const std::string& chars)
{
  if (mInStart)
  {
    mInStart = false;
    mStream << '>';
  }

  writeChars(chars);
  mInText = true;
  mSkipNextIndent = true;

  return *this;
}


/*
 * Outputs the given double to the underlying stream.
 */
XMLOutputStream&
XMLOutputStream::operator<< (const double& value)
{
  if (mInStart)
  {
    mInStart = false;
    mStream << '>';
  }

  mStream << value;

  return *this;
}


/*
 * Outputs the given long to the underlying stream.
 */
XMLOutputStream&
XMLOutputStream::operator<< (const long& value)
{
  if (mInStart)
  {
    mInStart = false;
    mStream << '>';
  }

  mStream << value;

  return *this;
}


/**
 * Outputs a single character to the underlying stream.
 */
XMLOutputStream& 
XMLOutputStream::operator<< (const char& c)
{
  if (c == '&' && mNextAmpersandIsRef)
  {
    // outputs '&' as-is because the '&' is the first letter
    // of a character reference (e.g. &#0168; )
    mStream << c;
    mNextAmpersandIsRef = false;
    return *this;
  }
  
  switch (c)
  {
    case '&' : mStream << "&amp;" ; break;
    case '\'': mStream << "&apos;"; break;
    case '<' : mStream << "&lt;"  ; break;
    case '>' : mStream << "&gt;"  ; break;
    case '"' : mStream << "&quot;"; break;
    default  : mStream << c;        break;
  }

  return *this;
}


/** @cond doxygen-libnuml-internal */

XMLOutputStringStream::XMLOutputStringStream (  std::ostringstream& stream
                   , const std::string&  encoding
                   , bool                writeXMLDecl
                   , const std::string&  programName
                   , const std::string&  programVersion):
  XMLOutputStream(stream, encoding, writeXMLDecl, 
                    programName, programVersion)
    , mString(stream)

{
  setStringStream();
}

XMLOutputFileStream::XMLOutputFileStream (  std::ofstream& stream
                   , const std::string&  encoding
                   , bool                writeXMLDecl
                   , const std::string&  programName
                   , const std::string&  programVersion):
  XMLOutputStream(stream, encoding, writeXMLDecl, 
                    programName, programVersion)
{
}

/** @endcond doxygen-libnuml-internal */

/** @cond doxygen-c-only */
/**
 * Creates a new XMLOutputStream_t that wraps std output stream.
 **/
LIBLAX_EXTERN
XMLOutputStream_t *
XMLOutputStream_createAsStdout (char * encoding, int writeXMLDecl)
{
  return new(nothrow) XMLOutputStream(std::cout, encoding, writeXMLDecl);
}


/**
 * Creates a new XMLOutputStream_t that wraps std output stream
 * and adds program information as a comment.
 **/
LIBLAX_EXTERN
XMLOutputStream_t *
XMLOutputStream_createAsStdoutWithProgramInfo (char * encoding,
        int writeXMLDecl, char * programName, char * programVersion)
{
  return new(nothrow) XMLOutputStream(std::cout, encoding, writeXMLDecl,
                                 programName, programVersion);
}


/**
 * Creates a new XMLOutputStream_t that wraps std string output stream.
 **/
LIBLAX_EXTERN
XMLOutputStream_t *
XMLOutputStream_createAsString (char * encoding, int writeXMLDecl)
{
  std::ostringstream *out = new std::ostringstream();

  return new(nothrow) XMLOutputStringStream(*out, encoding, writeXMLDecl);
}


/**
 * Creates a new XMLOutputStream_t that wraps std string output stream
 * and adds program information as a comment.
**/
LIBLAX_EXTERN
XMLOutputStream_t *
XMLOutputStream_createAsStringWithProgramInfo (char * encoding,
        int writeXMLDecl, char * programName, char * programVersion)
{
  std::ostringstream *out = new std::ostringstream();

  return new(nothrow) XMLOutputStringStream(*out, encoding, writeXMLDecl,
                             programName, programVersion);
}


/**
 * Creates a new XMLOutputStream_t that wraps std file output stream.
 **/
LIBLAX_EXTERN
XMLOutputStream_t *
XMLOutputStream_createFile (char * filename, char * encoding, int writeXMLDecl)
{
  std::ofstream *fout = new std::ofstream(filename, std::ios::out);
  return new(nothrow) XMLOutputFileStream(*fout, encoding, writeXMLDecl);
}


/**
 * Creates a new XMLOutputStream_t that wraps std file output stream
 * and adds program information as a comment.
**/
LIBLAX_EXTERN
XMLOutputStream_t *
XMLOutputStream_createFileWithProgramInfo (char * filename, char * encoding, 
        int writeXMLDecl, char * programName, char * programVersion)
{
  std::ofstream *fout = new std::ofstream(filename, std::ios::out);
  return new(nothrow) XMLOutputFileStream(*fout, encoding, writeXMLDecl,
                          programName, programVersion);
}


/**
 * Deletes this XMLOutputStream_t. 
 **/
LIBLAX_EXTERN
void
XMLOutputStream_free (XMLOutputStream_t *stream)
{
  delete static_cast<XMLOutputStream*>(stream);
}  


/**
 * Writes the XML declaration:
 * <?xml version="1.0" encoding="..."?>
 */
LIBLAX_EXTERN
void 
XMLOutputStream_writeXMLDecl (XMLOutputStream_t *stream)
{
  stream->writeXMLDecl();
}


/**
 * Increases the indentation level for this XMLOutputStream.
 */
LIBLAX_EXTERN
void
XMLOutputStream_upIndent(XMLOutputStream_t *stream)
{
  stream->upIndent();
}


/**
 * Decreases the indentation level for this XMLOutputStream.
 */
LIBLAX_EXTERN
void
XMLOutputStream_downIndent(XMLOutputStream_t *stream)
{
  stream->downIndent();
}


/**
  * Writes the given XML end element name to this XMLOutputStream.
  */
LIBLAX_EXTERN
void 
XMLOutputStream_endElement (XMLOutputStream_t *stream, const char* name)
{
  stream->endElement(name);
}


/**
 * Writes the given XML end element 'prefix:name' to this
 * XMLOutputStream.
 */
LIBLAX_EXTERN
void 
XMLOutputStream_endElementTriple (XMLOutputStream_t *stream, 
                                  const XMLTriple_t *triple)
{
  stream->endElement(*triple);
}


/**
 * Turns automatic indentation on or off for this XMLOutputStream.
 */
LIBLAX_EXTERN
void 
XMLOutputStream_setAutoIndent (XMLOutputStream_t *stream, int indent)
{
  stream->setAutoIndent(static_cast<bool>(indent));
}


/**
 * Writes the given XML start element name to this XMLOutputStream.
 */
LIBLAX_EXTERN
void 
XMLOutputStream_startElement (XMLOutputStream_t *stream, const char* name)
{
  stream->startElement(name);
}


/**
 * Writes the given XML start element 'prefix:name' to this
 * XMLOutputStream.
 */
LIBLAX_EXTERN
void 
XMLOutputStream_startElementTriple (XMLOutputStream_t *stream, 
                                    const XMLTriple_t *triple)
{
  stream->startElement(*triple);
}


/**
 * Writes the given XML start and end element name to this XMLOutputStream.
 */
LIBLAX_EXTERN
void 
XMLOutputStream_startEndElement (XMLOutputStream_t *stream, const char* name)
{
  stream->startEndElement(name);
}


/**
 * Writes the given XML start and end element 'prefix:name' to this
 * XMLOutputStream.
 */
LIBLAX_EXTERN
void 
XMLOutputStream_startEndElementTriple (XMLOutputStream_t *stream, 
                                       const XMLTriple_t *triple)
{
  stream->startEndElement(*triple);
}


/**
 * Writes the given attribute, name="value" to this XMLOutputStream.
 */
LIBLAX_EXTERN
void 
XMLOutputStream_writeAttributeChars (XMLOutputStream_t *stream, 
                                     const char* name, const char* chars)
{
  stream->writeAttribute(name, string(chars));
}


/**
 * Writes the given attribute, prefix:name="value" to this
 * XMLOutputStream.
 */
LIBLAX_EXTERN
void 
XMLOutputStream_writeAttributeCharsTriple (XMLOutputStream_t *stream, 
                                           const XMLTriple_t *triple,
                                           const char* chars)
{
  stream->writeAttribute(*triple, string(chars));
}


/**
 * Writes the given attribute, name="true" or name="false" to this
 * XMLOutputStream.
 */
LIBLAX_EXTERN
void 
XMLOutputStream_writeAttributeBool (XMLOutputStream_t *stream, 
                                    const char* name,
                                    const int flag)
{
  stream->writeAttribute(name, static_cast<bool>(flag));
}


/**
 * Writes the given attribute, prefix:name="true" or prefix:name="false"
 * to this XMLOutputStream.
 */
LIBLAX_EXTERN
void 
XMLOutputStream_writeAttributeBoolTriple (XMLOutputStream_t *stream, 
                                          const XMLTriple_t *triple,
                                          const int flag)
{
  stream->writeAttribute(*triple, static_cast<bool>(flag));
}


/**
 * Writes the given attribute, name="value" to this XMLOutputStream.
 */
LIBLAX_EXTERN
void 
XMLOutputStream_writeAttributeDouble (XMLOutputStream_t *stream, 
                                      const char* name,
                                      const double value)
{
  stream->writeAttribute(name, value);
}


/**
 * Writes the given attribute, prefix:name="value" to this XMLOutputStream.
 */
LIBLAX_EXTERN
void 
XMLOutputStream_writeAttributeDoubleTriple (XMLOutputStream_t *stream, 
                                            const XMLTriple_t *triple,
                                            const double value)
{
  stream->writeAttribute(*triple, value);
}


/**
 * Writes the given attribute, name="value" to this XMLOutputStream.
 */
LIBLAX_EXTERN
void 
XMLOutputStream_writeAttributeLong (XMLOutputStream_t *stream, 
                                    const char* name,
                                    const long value)
{
  stream->writeAttribute(name, value);
}


/**
 * Writes the given attribute, prefix:name="value" to this XMLOutputStream.
 */
LIBLAX_EXTERN
void 
XMLOutputStream_writeAttributeLongTriple (XMLOutputStream_t *stream, 
                                          const XMLTriple_t *triple,
                                          const long value)
{
  stream->writeAttribute(*triple, value);
}


/**
 * Writes the given attribute, name="value" to this XMLOutputStream.
 */
LIBLAX_EXTERN
void 
XMLOutputStream_writeAttributeInt (XMLOutputStream_t *stream, 
                                   const char* name,
                                   const int value)
{
  stream->writeAttribute(name, value);
}


/**
 * Writes the given attribute, prefix:name="value" to this XMLOutputStream.
 */
LIBLAX_EXTERN
void 
XMLOutputStream_writeAttributeIntTriple (XMLOutputStream_t *stream, 
                                         const XMLTriple_t *triple,
                                         const int value)
{
  stream->writeAttribute(*triple, value);
}


/**
 * Writes the given attribute, name="value" to this XMLOutputStream.
 */
LIBLAX_EXTERN
void 
XMLOutputStream_writeAttributeUInt (XMLOutputStream_t *stream, 
                                    const char* name,
                                    const unsigned int value)
{
  stream->writeAttribute(name, value);
}


/**
 * Writes the given attribute, prefix:name="value" to this XMLOutputStream.
 */
LIBLAX_EXTERN
void 
XMLOutputStream_writeAttributeUIntTriple (XMLOutputStream_t *stream, 
                                          const XMLTriple_t *triple,
                                          const unsigned int value)
{
  stream->writeAttribute(*triple, value);
}


/**
 * Outputs the given characters to the underlying stream.
 */
LIBLAX_EXTERN
void
XMLOutputStream_writeChars (XMLOutputStream_t *stream, const char* chars)
{
  stream->operator <<(chars);
}


/**
 * Outputs the given double to the underlying stream.
 */
LIBLAX_EXTERN
void
XMLOutputStream_writeDouble (XMLOutputStream_t *stream, const double value)
{
  stream->operator <<(value);
}


/**
 * Outputs the given long to the underlying stream.
 */
LIBLAX_EXTERN
void
XMLOutputStream_writeLong (XMLOutputStream_t *stream, const long value)
{
  stream->operator <<(value);
}


/**
 * Returns the given string associated to the underlying string stream.
 */
LIBLAX_EXTERN
const char *
XMLOutputStream_getString(XMLOutputStream_t* stream)
{
  if (stream->getStringStream())
  {
    std::string buffer = static_cast <XMLOutputStringStream*>
                                                  (stream)->getString().str();
    return safe_strdup(buffer.c_str());
  }
  else
    return "";
}


/** @endcond doxygen-c-only */

LIBNUML_CPP_NAMESPACE_END

