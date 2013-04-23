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

/**
 * @class XMLError
 * @brief Representation of errors, warnings and other diagnostics
 *
 * @htmlinclude libnuml-not-numl-warning.html
 *
 * LibNUML can be configured to use any of a number of XML parsers; at the
 * time of this writing, libNUML supports Xerces versions 2.4 through 3.0,
 * Expat version 1.95.x and higher, and libxml2 version 2.6.16 and higher.
 * These parsers each report different status codes for the various
 * exceptions that can occur during XML processing.  The XMLError object
 * class abstracts away from the particular diagnostics reported by the
 * different parsers and presents a single uniform interface and set of
 * status codes, along with operations for manipulating the error objects.
 *
 * When the libNUML XML parser layer encounters an error in the XML content
 * being processed, or when there is something else wrong (such as an
 * out-of-memory condition), the problems are reported as XMLError objects.
 * Each XMLError object instance has an identification number that
 * identifies the nature of the problem.
 * @if clike This error identifier will be up to five digits 
 * long and drawn from the enumeration <a class="el"
 * href="#XMLErrorCode_t">XMLErrorCode_t</a>.  Applications can use the
 * error identifiers as a means of recognizing the error encountered and
 * changing their behavior if desired. @endif@if java This
 * error identifier is one of the constants listed in the next section below.
 * Applications can use the error identifiers as a means of recognizing the
 * error encountered and changing their behavior if desired.  @endif
 *
 * Integer error codes are useful for software, but not so much for telling
 * humans what happened.  For this reason, XMLError also provides two text
 * messages describing the nature of the error.  These messages are
 * accessible by means of the methods XMLError::getShortMessage() and
 * XMLError::getMessage().  The method XMLError::getShortMessage() returns
 * a very brief synopsis of the warning or error condition, whereas
 * XMLError::getMessage() returns a longer explanation.  These text strings
 * are suitable for displaying to human users.
 *
 * Each XMLError object also contains a category code; its value may be
 * retrieved using the method XMLError::getCategory().  Category values
 * are @if clike drawn from the enumeration
 * <a class="el" href="#XMLErrorCategory_t">XMLErrorCategory_t</a> 
 * described below.  Categories are used by libNUML to provide more
 * information to calling programs about the nature of a given
 * error. @endif@if java drawn from a set of constants whose
 * names begin with the characters @c LIBNUML_CAT_.  The list of possible
 * codes is described in a separate section below. Categories are used by
 * libNUML to provide more information to calling programs about the nature
 * of a given error.  @endif
 *
 * In addition to category codes, each XMLError object also has a severity
 * code; its value may be retrieved using the method
 * XMLError::getSeverity().  Severity code values are 
 * @if clike drawn from the enumeration 
 * <a class="el" href="#XMLErrorSeverity_t">XMLErrorSeverity_t</a> described
 * in a separate section below.  Severity levels range from informational
 * (@c LIBNUML_SEV_INFO) to fatal errors (@c LIBNUML_SEV_FATAL).
 * @endif@if java drawn from a
 * set of constants whose names begin with the characters @c LIBNUML_SEV_.
 * The list of possible severity codes is described in a separate section
 * below.  Severity levels range from informational (@c LIBNUML_SEV_INFO)
 * to fatal errors (@c LIBNUML_SEV_FATAL). @endif
 *
 * Finally, XMLError objects record the line and column near where the
 * problem occurred in the XML content.  The values can be retrieved using
 * the methods XMLError::getLine() and XMLError::getColumn().  We say "near
 * where the problem occurred", because many factors affect how accurate
 * the line/column information ultimately is.  For example, different XML
 * parsers have different conventions for which line and column number they
 * report for a particular problem (which in turn makes a difference when a
 * problem involves an opening XML tag on one line and a closing tag on
 * another line).  In some situations, some parsers report invalid line
 * and/or column numbers altogether.  If this occurs, libNUML sets the line
 * and/or column number in the XMLError object to the the value of the
 * maximum unsigned long integer representable on the platform where
 * libNUML is running.  (This is equal to the constant named
 * <code>ULONG_MAX</code> in C and C++.)  The probability that a true line
 * or column number in an NUML model would equal this value is vanishingly
 * small; thus, if an application encounters these values in an XMLError
 * object, it can assume no valid line/column number could be provided by
 * libNUML in that situation.
 *
 * 
 * @if clike
 * <h3><a class="anchor" name="XMLErrorCode_t">XMLErrorCode_t</a></h3>
 *
 * This is an enumeration of all the error and warning codes returned by
 * the XML layer in libNUML.  Each code is an integer with a 4-digit value
 * less than 10000.  The following table lists each possible value and a
 * brief description of its meaning.
 * @endif@if java <h3><a class="anchor" 
 * name="XMLErrorCode_t">Error codes associated with XMLError objects</a></h3>
 * 
 * The error and warning codes returned by the XML layer in libNUML are
 * listed in the table below.  In the libNUML Java language interface,
 * these error identifiers are currently (in libNUML 3.3.x) implemented as
 * static integer constants defined in the interface class <code><a
 * href="libnumlConstants.html">libnumlConstants</a></code>.  This is admittedly
 * not an ideal approach from the standpoint of modern Java programming,
 * but it was necessary to work around the lack of enumerations in Java
 * prior to JDK 1.5.  Future versions of libNUML may use a proper Java
 * enumeration type to define the error identifiers. @endif
 *
 * <center>
 * <table cellspacing="1" cellpadding="1" border="0" class="text-table width80 normal-font alt-row-colors">
 * <caption>Possible XMLError error codes.  Depending on the programming
 * language in use, the <em>Enumerator</em> values will be defined either
 * as a value from the enumeration XMLErrorCode_t or as integer constants.
 * To make this table more compact, we have shortened the identifiers for
 * the category and severity codes to their essential parts.  To get the
 * actual names of the constants, prepend <code>LIBNUML_CAT_</code> to the
 * category names and <code>LIBNUML_SEV_</code> to the severity names
 * shown in the two right-hand columns.
 * </caption>
 *  <tr style="background: lightgray" class="normal-font">
 *      <th>Enumerator</th>
 *      <th>Meaning</th>
 *      <th width="90">Category</th>
 *      <th width="90">Severity</th>
 *  </tr>
 * <tr><td><code>XMLUnknownError</code></td><td>Unrecognized error encountered internally</td><td>INTERNAL</td><td>FATAL</td></tr>
 * <tr><td><code>XMLOutOfMemory</code></td> <td>Out of memory</td><td>SYSTEM</td><td>FATAL</td></tr>
 * <tr><td><code>XMLFileUnreadable</code></td> <td>File unreadable</td><td>SYSTEM</td><td>ERROR</td></tr>
 * <tr><td><code>XMLFileUnwritable</code></td> <td>File unwritable</td><td>SYSTEM</td><td>ERROR</td></tr>
 * <tr><td><code>XMLFileOperationError</code></td><td>Error encountered while attempting file operation</td><td>SYSTEM</td><td>ERROR</td></tr>
 * <tr><td><code>XMLNetworkAccessError</code></td><td>Network access error</td><td>SYSTEM</td><td>ERROR</td></tr>
 * <tr><td><code>InternalXMLParserError</code></td><td>Internal XML parser state error</td><td>INTERNAL</td><td>FATAL</td></tr>
 * <tr><td><code>UnrecognizedXMLParserCode</code></td><td>XML parser returned an unrecognized error code</td><td>INTERNAL</td><td>FATAL</td></tr>
 * <tr><td><code>XMLTranscoderError</code></td><td>Character transcoder error</td><td>INTERNAL</td><td>FATAL</td></tr>
 * <tr><td><code>MissingXMLDecl</code></td><td>Missing XML declaration at beginning of XML input</td><td>XML</td><td>ERROR</td></tr>
 * <tr><td><code>MissingXMLEncoding</code></td><td>Missing encoding attribute in XML declaration</td><td>XML</td><td>ERROR</td></tr>
 * <tr><td><code>BadXMLDecl</code></td><td>Invalid or unrecognized XML declaration or XML encoding</td><td>XML</td><td>ERROR</td></tr>
 * <tr><td><code>BadXMLDOCTYPE</code></td><td>Invalid, malformed or unrecognized XML DOCTYPE declaration</td><td>XML</td><td>ERROR</td></tr>
 * <tr><td><code>InvalidCharInXML</code></td><td>Invalid character in XML content</td><td>XML</td><td>ERROR</td></tr>
 * <tr><td><code>BadlyFormedXML</code></td><td>XML content is not well-formed</td><td>XML</td><td>ERROR</td></tr>
 * <tr><td><code>UnclosedXMLToken</code></td><td>Unclosed XML token</td><td>XML</td><td>ERROR</td></tr>
 * <tr><td><code>InvalidXMLConstruct</code></td><td>XML construct is invalid or not permitted</td><td>XML</td><td>ERROR</td></tr>
 * <tr><td><code>XMLTagMismatch</code></td><td>Element tag mismatch or missing tag</td><td>XML</td><td>ERROR</td></tr>
 * <tr><td><code>DuplicateXMLAttribute</code></td><td>Duplicate XML attribute</td><td>XML</td><td>ERROR</td></tr>
 * <tr><td><code>UndefinedXMLEntity</code></td><td>Undefined XML entity</td><td>XML</td><td>ERROR</td></tr>
 * <tr><td><code>BadProcessingInstruction</code></td><td>Invalid, malformed or unrecognized XML processing instruction</td><td>XML</td><td>ERROR</td></tr>
 * <tr><td><code>BadXMLPrefix</code></td><td>Invalid or undefined XML namespace prefix</td><td>XML</td><td>ERROR</td></tr>
 * <tr><td><code>BadXMLPrefixValue</code></td><td>Invalid XML namespace prefix value</td><td>XML</td><td>ERROR</td></tr>
 * <tr><td><code>MissingXMLRequiredAttribute</code></td><td>Missing a required XML attribute</td><td>XML</td><td>ERROR</td></tr>
 * <tr><td><code>XMLAttributeTypeMismatch</code></td><td>Data type mismatch for the value of an attribute</td><td>XML</td><td>ERROR</td></tr>
 * <tr><td><code>XMLBadUTF8Content</code></td><td>Invalid UTF8 content</td><td>XML</td><td>ERROR</td></tr>
 * <tr><td><code>MissingXMLAttributeValue</code></td><td>Missing or improperly formed attribute value</td><td>XML</td><td>ERROR</td></tr>
 * <tr><td><code>BadXMLAttributeValue</code></td><td>Invalid or unrecognizable attribute value</td><td>XML</td><td>ERROR</td></tr>
 * <tr><td><code>BadXMLAttribute</code></td><td>Invalid, unrecognized or malformed attribute</td><td>XML</td><td>ERROR</td></tr>
 * <tr><td><code>UnrecognizedXMLElement</code></td><td>Element either not recognized or not permitted</td><td>XML</td><td>ERROR</td></tr>
 * <tr><td><code>BadXMLComment</code></td><td>Badly formed XML comment</td><td>XML</td><td>ERROR</td></tr>
 * <tr><td><code>BadXMLDeclLocation</code></td><td>XML declaration not permitted in this location</td><td>XML</td><td>ERROR</td></tr>
 * <tr><td><code>XMLUnexpectedEOF</code></td><td>Reached end of input unexpectedly</td><td>XML</td><td>ERROR</td></tr>
 * <tr><td><code>BadXMLIDValue</code></td><td>Value is invalid for XML ID, or has already been used</td><td>XML</td><td>ERROR</td></tr>
 * <tr><td><code>BadXMLIDRef</code></td><td>XML ID value was never declared</td><td>XML</td><td>ERROR</td></tr>
 * <tr><td><code>UninterpretableXMLContent</code></td><td>Unable to interpret content</td><td>XML</td><td>ERROR</td></tr>
 * <tr><td><code>BadXMLDocumentStructure</code></td><td>Bad XML document structure</td><td>XML</td><td>ERROR</td></tr>
 * <tr><td><code>InvalidAfterXMLContent</code></td><td>Encountered invalid content after expected content</td><td>XML</td><td>ERROR</td></tr>
 * <tr><td><code>XMLExpectedQuotedString</code></td><td>Expected to find a quoted string</td><td>XML</td><td>ERROR</td></tr>
 * <tr><td><code>XMLEmptyValueNotPermitted</code></td><td>An empty value is not permitted in this context</td><td>XML</td><td>ERROR</td></tr>
 * <tr><td><code>XMLBadNumber</code></td><td>Invalid or unrecognized number</td><td>XML</td><td>ERROR</td></tr>
 * <tr><td><code>XMLBadColon</code></td><td>Colon characters are invalid in this context</td><td>XML</td><td>ERROR</td></tr>
 * <tr><td><code>MissingXMLElements</code></td><td>One or more expected elements are missing</td><td>XML</td><td>ERROR</td></tr>
 * <tr><td><code>XMLContentEmpty</code></td><td>Main XML content is empty</td><td>XML</td><td>ERROR</td></tr>
 * </table>
 * </center>
 *
 *
 * @if clike
 * <h3><a class="anchor" name="XMLErrorCategory_t">XMLErrorCategory_t</a></h3>
 *
 * As discussed above, each XMLError object contains a value for a category
 * identifier, describing the type of issue that the XMLError object
 * represents.  The category can be retrieved from an XMLError object using
 * the method XMLError::getCategory().  The value is chosen from the
 * enumeration of category codes <a class="el" href="#XMLErrorCategory_t">
 * XMLErrorCategory_t</a>.  The following table
 * lists each possible value and a brief description of its meaning.
 * @endif@if java <h3><a class="anchor"
 * name="XMLErrorCategory_t">Category codes associated with XMLError objects</a></h3>
 *
 * As discussed above, each XMLError object contains a value for a category
 * identifier, describing the type of issue that the XMLError object represents.
 * The category can be retrieved from an XMLError object using the method
 * XMLError::getCategory(). The following table lists each possible value
 * and a brief description of its meaning.
 * 
 * As is the case with the error codes, in the libNUML Java language
 * interface, the category identifiers are currently implemented as static
 * integer constants defined in the interface class
 * <code>libnumlConstants</code> in the file "<a
 * href="libnumlConstants.html">libnumlConstants.java</a>".
 * @endif
 *
 * <center>
 * <table width="90%" cellspacing="1" cellpadding="1" border="0" class="text-table width80 normal-font alt-row-colors">
 *  <tr style="background: lightgray" class="normal-font">
 *      <th>Enumerator</th>
 *      <th>Meaning</th>
 *  </tr>
 * <tr><td><em>LIBNUML_CAT_INTERNAL</em></td><td>A problem involving the libNUML
 * software itself or the underlying XML parser.  This almost certainly
 * indicates a software defect (i.e., bug) in libNUML.  Please report
 * instances of this to the libNUML developers.</td></tr>
 * <tr><td><em>LIBNUML_CAT_SYSTEM</em></td><td>A problem reported by the operating
 * system, such as an inability to read or write a file.  This indicates
 * something that is not a program error but is outside of the control of
 * libNUML.</td></tr>
 * <tr><td><em>LIBNUML_CAT_XML</em></td><td>A problem in the XML content itself.  This
 * usually arises from malformed XML or the use of
 * constructs not permitted in NUML.</td></tr>
 * </table>
 * </center>
 *
 *
 * @if clike
 * <h3><a class="anchor" name="XMLErrorSeverity_t">XMLErrorSeverity_t</a></h3>
 *
 * As described above, each XMLError object contains a value for a severity
 * code, describing how critical is the issue that the XMLError object
 * represents.  The severity can be retrieved from an XMLError object using
 * the method XMLError::getSeverity().  The value is chosen from the
 * enumeration of category codes <a class="el" href="#XMLErrorSeverity_t">
 * XMLErrorSeverity_t</a>.  The following table
 * lists each possible value and a brief description of its meaning.
 * @endif@if java <h3><a class="anchor"
 * name="XMLErrorSeverity_t">Severity codes associated with XMLError objects</a></h3>
 * 
 * As described above, each XMLError object contains a value for a severity
 * code, describing how severe is the issue that the XMLError object
 * represents.  The severity be retrieved from an XMLError object using the
 * method XMLError::getSeverity(). The following table lists each possible
 * value and a brief description of its meaning.
 * 
 * As is the case with the category codes, in the libNUML Java language
 * interface, these severity codes are currently (in libNUML 3.3.x)
 * implemented as static integer constants defined in the interface class
 * <code>libnumlConstants</code> in the file "libnumlConstants.java".  This
 * is admittedly not an ideal approach from the standpoint of modern Java
 * programming, but it was necessary to work around the lack of
 * enumerations in Java prior to JDK 1.5.  Future versions of libNUML may
 * use a proper Java enumeration type to define the severity codes. @endif
 *
 * <center>
 * <table width="90%" cellspacing="1" cellpadding="1" border="0" class="text-table width80 normal-font alt-row-colors">
 *  <tr style="background: lightgray" class="normal-font">
 *      <th>Enumerator</th>
 *      <th>Meaning</th>
 *  </tr>
 * <tr><td><em>LIBNUML_SEV_INFO</em></td><td>The error is actually informational and
 * not necessarily a serious problem.</td></tr>
 * <tr><td><em>LIBNUML_SEV_WARNING</em></td><td>The error object represents a problem
 * that is not serious enough to necessarily stop the problem, but
 * applications should take note of the problem and evaluate what its
 * implications may be.</td></tr>
 * <tr><td><em>LIBNUML_SEV_ERROR</em></td><td>The error object represents a serious
 * error.  The application may continue running but it is unlikely to be
 * able to continue processing the same XML file or data stream.</td></tr>
 * <tr><td><em>LIBNUML_SEV_FATAL</em></td><td>A serious error occurred, such as an
 * out-of-memory condition, and the software should terminate
 * immediately.</td></tr>
 * </table>
 * </center>
 */


#ifndef XMLError_h
#define XMLError_h

#include <stdio.h>


#include <numl/xml/XMLExtern.h>
#include <numl/common/numlfwd.h>
#include <numl/util/util.h>

LIBNUML_CPP_NAMESPACE_BEGIN

BEGIN_C_DECLS

/**
 * Canonical error codes returned for low-level XML parser errors.
 *
 * These codes are 4 digits long, less than 10000, to distinguish them
 * from 5-digit NUML error codes > 10000.  The codes are an abstraction
 * of errors from the multiple parsers (Xerces, Expat, libxml2) supported
 * by libNUML.
 */
typedef enum {
    XMLUnknownError           =    0 /*!< Unknown error encountered. */

  /* System diagnostics: numbers below 100 -------------------------------- */

  , XMLOutOfMemory            =    1 /*!< LibNUML unexpected encountered an out
                                      *   of memory condition from the operating
                                      *   system. */

  , XMLFileUnreadable         =    2 /*!< Could not open or read the file. */

  , XMLFileUnwritable         =    3 /*!< Could not write to the file. */

  , XMLFileOperationError     =    4 /*!< Error encountered while attempting
                                      *   a file operation. */

  , XMLNetworkAccessError     =    5 /*!< Error encountered while attempting
                                      *   a network access. */

  /* Internal diagnostics: numbers about 100 and below 1000 --------------- */

  , InternalXMLParserError    =  101 /*!< Internal error in XML parser. */

  , UnrecognizedXMLParserCode =  102 /*!< The XML parser returned an error
                                      *   code that is not recognized by
                                      *   libNUML. */

  , XMLTranscoderError        =  103 /*!< The character transcoder reported
                                      *   an error. */

  /* Content errors: numbers about 1000 and below 9999 -------------------- */

  , MissingXMLDecl            = 1001 /*!< Missing XML declaration at beginning
                                      *   of XML input. */

  , MissingXMLEncoding        = 1002 /*!< Missing encoding attribute in
                                      *   XML declaration. */

  , BadXMLDecl                = 1003 /*!< Invalid or unrecognized XML
                                      *   declaration or XML encoding. */

  , BadXMLDOCTYPE             = 1004 /*!< Invalid, malformed or unrecognized
                                      *   XML DOCTYPE declaration. */

  , InvalidCharInXML          = 1005 /*!< Invalid character in XML content. */

  , BadlyFormedXML            = 1006 /*!< XML is not well-formed. */

  , UnclosedXMLToken          = 1007 /*!< Unclosed token. */

  , InvalidXMLConstruct       = 1008 /*!< XML construct is invalid or
                                      *   not permitted. */

  , XMLTagMismatch            = 1009 /*!< Element tag mismatch or missing tag.*/

  , DuplicateXMLAttribute     = 1010 /*!< Duplicate attribute. */

  , UndefinedXMLEntity        = 1011 /*!< Undefined XML entity. */

  , BadProcessingInstruction  = 1012 /*!< Invalid, malformed or unrecognized
                                      *   XML processing instruction. */

  , BadXMLPrefix              = 1013 /*!< Invalid or undefined XML
                                      *   Namespace prefix. */

  , BadXMLPrefixValue         = 1014 /*!< Invalid XML Namespace prefix value. */

  , MissingXMLRequiredAttribute = 1015 /*!< Required attribute is missing. */

  , XMLAttributeTypeMismatch  = 1016 /*!< Data type mismatch for attribute
                                      *   value. */

  , XMLBadUTF8Content         = 1017 /*!< Invalid UTF8 content. */

  , MissingXMLAttributeValue  = 1018 /*!< Missing or improperly formed
                                      *   attribute value. */

  , BadXMLAttributeValue      = 1019 /*!< Invalid or unrecognizable attribute
                                      *   value. */

  , BadXMLAttribute           = 1020 /*!< Invalid, unrecognized or malformed
                                      *   attribute. */

  , UnrecognizedXMLElement    = 1021 /*!< Element either not recognized or
                                      *   not permitted. */

  , BadXMLComment             = 1022 /*!< Badly formed XML comment. */

  , BadXMLDeclLocation        = 1023 /*!< XML declaration not permitted in
                                      *   this location. */

  , XMLUnexpectedEOF          = 1024 /*!< Reached end of input unexpectedly. */

  , BadXMLIDValue             = 1025 /*!< Value is invalid for XML ID, or has
                                      *   already been used. */

  , BadXMLIDRef               = 1026 /*!< XML ID value was never declared. */

  , UninterpretableXMLContent = 1027 /*!< Unable to interpret content. */

  , BadXMLDocumentStructure   = 1028 /*!< Bad XML document structure. */

  , InvalidAfterXMLContent    = 1029 /*!< Encountered invalid content after
                                      *   expected content. */

  , XMLExpectedQuotedString   = 1030 /*!< Expected to find a quoted string. */

  , XMLEmptyValueNotPermitted = 1031 /*!< An empty value is not permitted in
                                      *   this context. */

  , XMLBadNumber              = 1032 /*!< Invalid or unrecognized number. */

  , XMLBadColon               = 1033 /*!< Colon characters are invalid in
                                      *   this context. */

  , MissingXMLElements        = 1034 /*!< One or more expected elements
                                      *   are missing. */

  , XMLContentEmpty           = 1035 /*!< Main XML content is empty. */

  /* Bounds */

  , XMLErrorCodesUpperBound   = 9999

} XMLErrorCode_t;


/**
 * Category codes for errors in the XML layer.
 */
typedef enum
{
    LIBNUML_CAT_INTERNAL = 0 /*!< A problem involving the libNUML software itself
                           * or the underlying XML parser.  This almost 
                           * certainly indicates a software defect (i.e., bug)
                           * in libNUML.  Please report instances of this to
                           * the libNUML developers. */

  , LIBNUML_CAT_SYSTEM       /*!< A problem reported by the operating system, such
                           * as an inability to read or write a file.  This
                           * indicates something that is not a program error
                           * but is outside of the control of libNUML. */

  , LIBNUML_CAT_XML          /*!< A problem in the XML content itself.  This
                           * usually arises from malformed XML or the use of
                           * constructs not permitted in NUML. */
} XMLErrorCategory_t;


/**
 * Severity codes for errors in the XML layer
 *
 * These severity levels are based on those defined in the XML
 * specification, with the addition of Info for informational messages.
 *
 */
typedef enum 
{
    LIBNUML_SEV_INFO    = 0 /*!< The error is actually informational and
                          * not necessarily a serious problem. */

  , LIBNUML_SEV_WARNING     /*!< The error object represents a problem that is not
                          * serious enough to necessarily stop the problem, but
                          * applications should take note of the problem and
                          * evaluate what its implications may be. */

  , LIBNUML_SEV_ERROR       /*!< The error object represents a serious error.  The
                          * application may continue running but it is unlikely
                          * to be able to continue processing the same XML file
                          * or data stream. */

  , LIBNUML_SEV_FATAL       /*!< A serious error occurred, such as an
                          * out-of-memory condition, and the software should
                          * terminate immediately. */
} XMLErrorSeverity_t;


/**
 * Sometimes the line/column numbers reported by the underlying parsers are
 * simply invalid.  This especially occurs in error situations when the
 * error is severe.  Typically you're not supposed to call the parsers'
 * getline()/getcolumn() functions in those situations, but it's hard to
 * avoid because of the flow of control in our code.  The problem is, in
 * some cases, calling the parser's getline()/getcolumn() functions results
 * in a segmentation fault.  (Case in point: this was happening using
 * Xerces 2.8 on 32-bit systems.)  We need to communicate that a
 * line/column number value is actually invalid or meaningless.
 *
 * Doing that presents a new problem: our line/column number values are
 * unsigned integers, which thus only allows 2 states to be
 * communicated. (Explanation: you could use 0 to communicate an invalid
 * state and let all other values indicate a valid state.  If we had signed
 * integers, we could communicate 3 state values, using negative, 0, and
 * positive values for the different states.)  Unfortunately we can't use 0
 * because that value is already being used to communicate a different
 * meaning between users of XMLError objects.
 *
 * The following is a bit of a hack, but not completely unrealistic: we use
 * the largest possible value of the data type used to represent
 * line/column numbers.  The probability that an error in an file will
 * involve these specific numbers is vanishingly small.  Thus, we can say
 * that if user code encounters these values as line/column numbers, they
 * should assume they are actually meaningless and no valid line/column
 * number could be provided by the parser.
 */

#define LIBNUML_UNKNOWN_LINE	ULONG_MAX
#define LIBNUML_UNKNOWN_COLUMN	ULONG_MAX



END_C_DECLS


LIBNUML_CPP_NAMESPACE_END


#ifdef __cplusplus


#include <iosfwd>
#include <string>
#include <numl/common/operationReturnValues.h>

LIBNUML_CPP_NAMESPACE_BEGIN

class LIBLAX_EXTERN XMLError
{
public:

  /**
   * Creates a new XMLError to report that something occurred during XML
   * processing.
   *
   * XMLError objects have identification numbers to indicate the nature of
   * the exception.  @if clike These numbers are drawn from
   * the enumeration <a class="el"
   * href="#XMLErrorCode_t">XMLErrorCode_t</a>.
   * @endif@if java These numbers are defined as unsigned 
   * integer constants in the file
   * "libnumlConstants.java".  See the <a class="el"
   * href="#XMLErrorCode_t">top of this documentation</a> for a table
   * listing the possible values and their meanings. @endif The argument @p
   * errorId to this constructor @em can be (but does not have to be) a
   * value from this @if clike enumeration. If it is a value
   * from <a class="el" href="#XMLErrorCode_t">XMLErrorCode_t</a>, the
   * XMLError class assumes the error is a low-level system or XML layer
   * error and <em>prepends</em> a built-in, predefined error message to
   * any string passed in the argument @p details to this constructor.  In
   * addition, all <a class="el" href="#XMLErrorCode_t">XMLErrorCode_t</a>
   * errors have associated values for the @p severity and @p category
   * codes, and these fields are filled-in as well from the enumerations <a
   * class="el" href="#XMLErrorSeverity_t">XMLErrorSeverity_t</a> and <a
   * class="el" href="#XMLErrorCategory_t">XMLErrorCategory_t</a>,
   * respectively. @endif@if java set of constants.  If it is
   * one of the predefined error identifiers, the XMLError class assumes
   * the error is a low-level system or XML layer error and
   * <em>prepends</em> a built-in, predefined error message to any string
   * passed in the argument @p details to this constructor.  In addition,
   * all the predefined error identifiers have associated values for the @p
   * severity and @p category codes, and these fields are filled-in as
   * well. @endif
   *
   * If the error identifier @p errorId is a number greater than 9999, this
   * constructor assumes that the error was generated from another part of
   * the software, and does not do additional filling in of values beyond
   * the defaults in the constructor itself.  This allows XMLError to serve
   * as a base class for other errors (and is used in this way elsewhere in
   * libNUML).  Callers should fill in all the parameters with suitable
   * values if generating errors with codes greater than 9999 to make
   * maximum use of the XMLError facilities.
   *
   * @if clike As mentioned above, there are two other
   * enumerations, <a class="el"
   * href="#XMLErrorSeverity_t">XMLErrorSeverity_t</a> and <a class="el"
   * href="#XMLErrorCategory_t">XMLErrorCategory_t</a>, used for indicating
   * the severity and category of error for the predefined XMLError codes.
   * The values passed in @p severity and @p category override the defaults
   * assigned based on the error code.  If the value of @p errorId is a
   * value from <a class="el" href="#XMLErrorCode_t">XMLErrorCode_t</a>,
   * callers do not need to fill in @p severity and @p category.
   * Conversely, if @p errorId is not a value from <a class="el"
   * href="#XMLErrorCode_t">XMLErrorCode_t</a>, callers can use other
   * values (not just those from <a class="el"
   * href="#XMLErrorSeverity_t">XMLErrorSeverity_t</a> and <a class="el"
   * href="#XMLErrorCategory_t">XMLErrorCategory_t</a>, but their own
   * special values) for @p severity and @p
   * category. @endif@if java As mentioned above, 
   * there are additional constants defined for <a class="el"
   * href="#XMLErrorSeverity_t">standard severity</a> and <a class="el"
   * href="#XMLErrorCategory_t">standard category</a> codes, and every predefined 
   * error in libNUML has an associated value for severity and category taken
   * from these predefined sets.  These constants have symbol names
   * prefixed with <code>LIBNUML_SEV_</code> and <code>LIBNUML_CAT_</code>,
   * respectively.  If the value of @p errorId is one of the standard error
   * codes, callers do not need to fill in @p severity and @p category in a
   * call to this constructor.  Conversely, if @p errorId is not an existing
   * XML-level error code, callers can use other values for @p severity and
   * @p category. @endif
   *
   * @param errorId an unsigned int, the identification number of the error.
   * 
   * @param details a string containing additional details about the error.
   * If the error code in @p errorId is one that is recognized by XMLError,
   * the given message is @em appended to a predefined message associated
   * with the given code.  If the error code is not recognized, the message
   * is stored as-is as the text of the error.
   * 
   * @param line an unsigned int, the line number at which the error occured.
   * 
   * @param column an unsigned int, the column number at which the error occured.
   * 
   * @param severity an integer indicating severity of the error.
   * 
   * @param category an integer indicating the category to which the error
   * belongs.
   *
   * @docnote The native C++ implementation of this method defines a
   * default argument value.  In the documentation generated for different
   * libNUML language bindings, you may or may not see corresponding
   * arguments in the method declarations.  For example, in Java, a default
   * argument is handled by declaring two separate methods, with one of
   * them having the argument and the other one lacking the argument.
   * However, the libNUML documentation will be @em identical for both
   * methods.  Consequently, if you are reading this and do not see an
   * argument even though one is described, please look for descriptions of
   * other variants of this method near where this one appears in the
   * documentation.
   */
  XMLError
  (
      const int errorId           = 0
    , const std::string& details  = ""
    , const unsigned int line     = 0
    , const unsigned int column   = 0
    , const unsigned int severity = LIBNUML_SEV_FATAL
    , const unsigned int category = LIBNUML_CAT_INTERNAL
  );


  /**
   * Copy constructor; creates a copy of this XMLError.
   */
  XMLError(const XMLError& orig);


  /**
   * Destroys this XMLError.
   */
  virtual ~XMLError ();


  /**
   * Returns the identifier of this error.
   *
   * @return the id of this XMLError.
   * 
   * @see getMessage()
   * @see getShortMessage()
   * @see getCategory()
   * @see getSeverity()
   */
  const unsigned int getErrorId () const;


  /**
   * Returns the message text of this error.
   *
   * The message associated with an error object describes the nature of
   * the problem.  The message returned by this method is generally longer
   * and clearer than the message returned by XMLError::getShortMessage(),
   * but not in all cases.
   *
   * Callers may use XMLError::getCategory() and XMLError::getSeverity() to
   * obtain additional information about the nature and severity of the
   * problem.
   *
   * @return the message text
   *
   * @see getErrorId()
   * @see getShortMessage()
   * @see getCategory()
   * @see getSeverity()
   */
  const std::string& getMessage () const;


  /**
   * Returns a brief message for this error.
   *
   * This is an alternative error message that, in general, is as short as
   * the authors could make it.  However, brevity is often inversely
   * proportional to clarity, so this short message may not be sufficiently
   * informative to understand the nature of the error.  Calling
   * applications may wish to check XMLError::getMessage() in addition or
   * instead.
   *
   * @return the short error message text
   * 
   * @see getErrorId()
   * @see getMessage()
   * @see getCategory()
   * @see getSeverity()
   */
  const std::string& getShortMessage () const;


  /**
   * Returns the line number in the XML input near where the error, warning
   * or other diagnostic occurred.
   *
   * We say "near where the problem occurred", because many factors affect
   * how accurate the line/column information ultimately is.  For example,
   * different XML parsers have different conventions for which line and
   * column number they report for a particular problem (which in turn
   * makes a difference when a problem involves an opening XML tag on one
   * line and a closing tag on another line).  In some situations, some
   * parsers report invalid line and/or column numbers altogether.  If this
   * occurs, the line and/or column number in the XMLError object will be
   * set to the the value of the maximum unsigned long integer
   * representable on the platform where libNUML is running.  (This is
   * equal to the constant named <code>ULONG_MAX</code> in C and C++.)  The
   * probability that a true line or column number in an NUML model would
   * equal this value is vanishingly small; thus, if an application
   * encounters these values in an XMLError object, it can assume no valid
   * line/column number could be provided by libNUML in that situation.
   *
   * @return the line number
   *
   * @see getColumn()
   */
  unsigned int getLine () const;


  /**
   * Returns the column number in the XML input near where the error,
   * warning or other diagnostic occurred.
   *
   * We say "near where the problem occurred", because many factors affect
   * how accurate the line/column information ultimately is.  For example,
   * different XML parsers have different conventions for which line and
   * column number they report for a particular problem (which in turn
   * makes a difference when a problem involves an opening XML tag on one
   * line and a closing tag on another line).  In some situations, some
   * parsers report invalid line and/or column numbers altogether.  If this
   * occurs, the line and/or column number in the XMLError object will be
   * set to the the value of the maximum unsigned long integer
   * representable on the platform where libNUML is running.  (This is
   * equal to the constant named <code>ULONG_MAX</code> in C and C++.)  The
   * probability that a true line or column number in an NUML model would
   * equal this value is vanishingly small; thus, if an application
   * encounters these values in an XMLError object, it can assume no valid
   * line/column number could be provided by libNUML in that situation.
   *
   * @return the column number
   *
   * @see getLine()
   */
  unsigned int getColumn () const;


  /**
   * Returns the severity of this error.
   *
   * XMLError defines an enumeration of severity codes for the XML layer.
   * Applications that build on XMLError by subclassing it may add their
   * own severity codes with numbers higher than those in the predefined
   * set of severity codes.
   *
   * @return the severity of this XMLError.
   *
   * @see getSeverityAsString()
   * @see getCategory()
   */
  unsigned int getSeverity () const;


  /**
   * Returns a string describing the severity level of this error.
   *
   * XMLError defines an enumeration of severity codes for the XML layer.
   * Applications that build on XMLError by subclassing it may add their
   * own severity codes with numbers higher than those in the predefined
   * set of severity codes.
   *
   * @return string representing the severity of this XMLError.
   *
   * @see getSeverity()
   * @see getCategoryAsString()
   */
  const std::string& getSeverityAsString() const;
  
  
  /**
   * Returns the category of this error.
   *
   * XMLError defines an enumeration of category codes for the XML layer.
   * Applications that build on XMLError by subclassing it may add their
   * own categories with numbers higher than those in the predefined
   * set of category codes.
   *
   * Categories can be used to partition errors into distinct groups.
   * Among other things, this can be used to prevent id conflicts by
   * uniquely identifying an XMLError by both id and category.
   *
   * @return the category of this XMLError.
   *
   * @see getSeverity()
   * @see getCategoryAsString()
   */
  unsigned int getCategory () const;


  /**
   * Returns a string describing the category of this error.
   *
   * XMLError defines an enumeration of category codes for the XML layer.
   * Applications that build on XMLError by subclassing it may add their
   * own categories with numbers higher than those in the predefined
   * set of category codes.
   *
   * Categories can be used to partition errors into distinct groups.
   * Among other things, this can be used to prevent id conflicts by
   * uniquely identifying an XMLError by both id and category.
   *
   * @return string representing the category of this XMLError.
   *
   * @see getCategory()
   * @see getSeverityAsString()
   */
  const std::string& getCategoryAsString () const;


  /**
   * Predicate returning @c true or @c false depending on whether this
   * error object is for information purposes only.
   *
   * This is equivalent to obtaining the severity code from an XMLError
   * object (via XMLError::getSeverity()) and then comparing it to the
   * value <code>LIBNUML_SEV_INFO</code> from the
   * @if clike enumeration
   * #XMLErrorSeverity_t. @endif@if java set of predefined
   * severity codes.@endif
   *
   * @return @c true if this XMLError is for informational purposes only,
   * @c false otherwise.
   *
   * @see isWarning()
   * @see isError()
   * @see isFatal()
   */
  bool isInfo () const;


  /**
   * Predicate returning @c true or @c false depending on whether 
   * this error object is a warning.
   *
   * This is equivalent to obtaining the severity code from an XMLError
   * object (via XMLError::getSeverity()) and then comparing it to the
   * value <code>LIBNUML_SEV_WARNING</code> from the
   * @if clike enumeration
   * #XMLErrorSeverity_t. @endif@if java set of predefined
   * severity codes.@endif
   *
   * @return @c true if this error is a warning, @c false otherwise.
   *
   * @see isInfo()
   * @see isError()
   * @see isFatal()
   */
  bool isWarning () const;


  /**
   * Predicate returning @c true or @c false depending on whether this
   * error is a significant error.
   *
   * This is equivalent to obtaining the severity code from an XMLError
   * object (via XMLError::getSeverity()) and then comparing it to the
   * value <code>LIBNUML_SEV_ERROR</code> from the
   * @if clike enumeration
   * #XMLErrorSeverity_t. @endif@if java set of predefined
   * severity codes.@endif
   *
   * @return @c true if this error is an error, @c false otherwise.
   *
   * @see isInfo()
   * @see isWarning()
   * @see isFatal()
   */
  bool isError () const;


  /**
   * Predicate returning @c true or @c false depending on whether this
   * error is a fatal run-time error.
   *
   * This is equivalent to obtaining the severity code from an XMLError
   * object (via XMLError::getSeverity()) and then comparing it to the
   * value <code>LIBNUML_SEV_FATAL</code> from the
   * @if clike enumeration
   * #XMLErrorSeverity_t. @endif@if java set of predefined
   * severity codes.@endif
   *
   * @return @c true if this error is a fatal error, @c false otherwise.
   *
   * @see isInfo()
   * @see isWarning()
   * @see isError()
   */
  bool isFatal () const;


  /**
   * Predicate returning @c true or @c false depending on whether this
   * error resulted from an internal program error.
   *
   * This is equivalent to obtaining the category identifier from an
   * XMLError object (via XMLError::getCategory()) and then comparing it to
   * the value <code>LIBNUML_CAT_INTERNAL</code> from the
   * @if clike
   * enumeration #XMLErrorCategory_t. @endif@if java set of
   * predefined category codes.@endif
   *
   * @return @c true or @c false
   *
   * @see isSystem()
   * @see isXML()
   */
  bool isInternal () const;


  /**
   * Predicate returning @c true or @c false depending on whether this
   * error was generated by the operating system.
   *
   * This is equivalent to obtaining the category identifier from an
   * XMLError object (via XMLError::getCategory()) and then comparing it to
   * the value <code>LIBNUML_CAT_SYSTEM</code> from the
   * @if clike
   * enumeration #XMLErrorCategory_t. @endif@if java set of
   * predefined category codes.@endif
   *
   * @return @c true or @c false
   *
   * @see isInternal()
   * @see isXML()
   */
  bool isSystem () const;


  /**
   * Predicate returning @c true or @c false depending on whether this
   * error resulted from a problem in the XML input (e.g., an XML syntax
   * error).
   *
   * This is equivalent to obtaining the category identifier from an
   * XMLError object (via XMLError::getCategory()) and then comparing it to
   * the value <code>LIBNUML_CAT_XML</code> from the
   * @if clike
   * enumeration #XMLErrorCategory_t. @endif@if java set of
   * predefined category codes.@endif
   *
   * @return @c true or @c false
   *
   * @see isInternal()
   * @see isSystem()
   */
  bool isXML () const;


  /**
   * Sets the line number where this error occurred.
   * 
   * @param line an unsigned int, the line number to set.
   *
   * @return integer value indicating success/failure of the
   * function.  @if clike The value is drawn from the
   * enumeration #OperationReturnValues_t. @endif The possible values
   * returned by this function are:
   * @li LIBNUML_OPERATION_SUCCESS
   *
   * @see setColumn(unsigned int column)
   */
  int setLine (unsigned int line);


  /**
   * Sets the column number where this error occurred.
   * 
   * @param column an unsigned int, the column number to set.
   *
   * @return integer value indicating success/failure of the
   * function.  @if clike The value is drawn from the
   * enumeration #OperationReturnValues_t. @endif The possible values
   * returned by this function are:
   * @li LIBNUML_OPERATION_SUCCESS
   *
   * @see setLine(unsigned int line)
   */
  int setColumn (unsigned int column);

  
  /**
   * Returns a copy of the message string associated with the given
   * predefined XMLError code.
   *
   * @param code the error code whose message is sought; it must be a
   * predefined value from @if clike <a class="el"
   * href="#XMLErrorCode_t">
   * XMLErrorCode_t</a>. @endif@if java <a class="el"
   * href="#XMLErrorCode_t">the set of predefined error identifiers.@endif
   */
  static const std::string getStandardMessage (const int code);

#ifndef SWIG

  /** @cond doxygen-libnuml-internal */

  /**
   * clone function
   */
  virtual XMLError* clone() const;


  /**
   * Outputs this XMLError to stream in the following format (and followed
   * by a newline):
   *
   *   line: (error id) message
   *
   * @param stream the output stream to write to.
   */
  virtual void print(std::ostream& stream) const;

  /** @endcond doxygen-libnuml-internal */

#endif

protected:
  /** @cond doxygen-libnuml-internal */

  unsigned int mErrorId;

  std::string  mMessage;
  std::string  mShortMessage;

  unsigned int mSeverity;
  unsigned int mCategory;

  unsigned int mLine;
  unsigned int mColumn;

  std::string mSeverityString;
  std::string mCategoryString;

  virtual std::string stringForSeverity(unsigned int code) const;
  virtual std::string stringForCategory(unsigned int code) const;

  /** @endcond doxygen-libnuml-internal */
};


#ifndef SWIG

/** @cond doxygen-libnuml-internal */

/**
 * Outputs the given XMLError (or the derived class (e.g. NUMLError) ) to stream
 * by invoking the print function which is implemented as a virtual function in
 * the class.
 *
 * @param stream the output stream to write to.
 * @param error the XMLError to write.
 */
LIBLAX_EXTERN
std::ostream& operator<< (std::ostream& stream, const XMLError& error);


/**
 * The structured used in constructing tables of predefined error codes and
 * their associated messages, severities and categories. 
 */
typedef struct {
  int          code;
  unsigned int category;
  unsigned int severity;
  const char*  shortMessage;
  const char*  message;
} xmlErrorTableEntry;

/** @endcond doxygen-libnuml-internal */

#endif  /* !SWIG */

LIBNUML_CPP_NAMESPACE_END

#endif  /* __cplusplus */



#ifndef SWIG

LIBNUML_CPP_NAMESPACE_BEGIN
BEGIN_C_DECLS

/*-----------------------------------------------------------------------------
 * See the .cpp file for the documentation of the following functions.
 *---------------------------------------------------------------------------*/


/* #ifndef __cplusplus */
/* typedef struct XMLError_t; */
/* #endif */

LIBLAX_EXTERN
XMLError_t*
XMLError_create (void);

LIBLAX_EXTERN
XMLError_t*
XMLError_createWithIdAndMessage (unsigned int errorId, const char * message);

/* LIBLAX_EXTERN */
/* XMLError_t* */
/* XMLError_createWithAll (unsigned int id, const char * message, XMLError_Severity severity, */
/*                         const char * category, unsigned int line, unsigned int column); */

LIBLAX_EXTERN
void
XMLError_free(XMLError_t* error);


LIBLAX_EXTERN
unsigned int
XMLError_getErrorId (const XMLError_t *error);


LIBLAX_EXTERN
const char *
XMLError_getMessage (const XMLError_t *error);


LIBLAX_EXTERN
const char *
XMLError_getShortMessage (const XMLError_t *error);


LIBLAX_EXTERN
unsigned int
XMLError_getLine (const XMLError_t *error);


LIBLAX_EXTERN
unsigned int
XMLError_getColumn (const XMLError_t *error);


LIBLAX_EXTERN
unsigned int
XMLError_getSeverity (const XMLError_t *error);


LIBLAX_EXTERN
const char *
XMLError_getSeverityAsString (const XMLError_t *error);


LIBLAX_EXTERN
unsigned int
XMLError_getCategory (const XMLError_t *error);


LIBLAX_EXTERN
const char *
XMLError_getCategoryAsString (const XMLError_t *error);


LIBLAX_EXTERN
int
XMLError_isInfo (const XMLError_t *error);


LIBLAX_EXTERN
int
XMLError_isWarning (const XMLError_t *error);


LIBLAX_EXTERN
int
XMLError_isError (const XMLError_t *error);


LIBLAX_EXTERN
int
XMLError_isFatal (const XMLError_t *error);


LIBLAX_EXTERN
void
XMLError_print (const XMLError_t *error, FILE *stream);


END_C_DECLS
LIBNUML_CPP_NAMESPACE_END

#endif  /* !SWIG */
#endif  /* XMLError_h */
