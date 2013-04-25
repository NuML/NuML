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


#ifndef XMLAttributes_h
#define XMLAttributes_h

#include <numl/xml/XMLExtern.h>
#include <numl/common/numlfwd.h>
#include <numl/common/operationReturnValues.h>


#ifdef __cplusplus


#include <string>
#include <vector>

#include <numl/xml/XMLTriple.h>

LIBNUML_CPP_NAMESPACE_BEGIN

class XMLErrorLog;
/** @cond doxygen-libnuml-internal */
class XMLOutputStream;
/** @endcond doxygen-libnuml-internal */


class LIBLAX_EXTERN XMLAttributes
{
public:

  /**
   * Creates a new empty XMLAttributes set.
   */
  XMLAttributes ();


  /**
   * Destroys this XMLAttributes set.
   */
  virtual ~XMLAttributes ();


  /**
   * Copy constructor; creates a copy of this XMLAttributes set.
   */
  XMLAttributes(const XMLAttributes& orig);


  /**
   * Assignment operator for XMLAttributes.
   */
  XMLAttributes& operator=(const XMLAttributes& orig);


  /**
   * Creates and returns a deep copy of this XMLAttributes set.
   * 
   * @return a (deep) copy of this XMLAttributes set.
   */
  XMLAttributes* clone () const;


  /**
   * Adds an attribute (a name/value pair) to this XMLAttributes set optionally 
   * with a prefix and URI defining a namespace.
   *
   * @param name a string, the local name of the attribute.
   * @param value a string, the value of the attribute.
   * @param namespaceURI a string, the namespace URI of the attribute.
   * @param prefix a string, the prefix of the namespace
   *
   * @return integer value indicating success/failure of the
   * function.  @if clike The value is drawn from the
   * enumeration #OperationReturnValues_t. @endif The possible values
   * returned by this function are:
   * @li LIBNUML_OPERATION_SUCCESS
   *
   * @note if local name with the same namespace URI already exists in this 
   * attribute set, its value and prefix will be replaced.
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
  int add (  const std::string& name
	    , const std::string& value
	    , const std::string& namespaceURI = ""
	    , const std::string& prefix = "");


  /**
   * Adds an attribute with the given XMLTriple/value pair to this XMLAttributes set.
   *
   * @note if local name with the same namespace URI already exists in this attribute set, 
   * its value and prefix will be replaced.
   *
   * @param triple an XMLTriple, the XML triple of the attribute.
   * @param value a string, the value of the attribute.
   *
   * @return integer value indicating success/failure of the
   * function.  @if clike The value is drawn from the
   * enumeration #OperationReturnValues_t. @endif The possible values
   * returned by this function are:
   * @li LIBNUML_OPERATION_SUCCESS
   */
   int add ( const XMLTriple& triple, const std::string& value);


  /** @cond doxygen-libnuml-internal */

  /**
   * Adds an name/value pair to this XMLAttributes set.  
   *
   * This method is similar to the add method but an attribute with same name wont 
   * be overwritten. This facilitates the addition of multiple resource attributes 
   * in CVTerm class.
   *
   * @param name a string, the name of the attribute.
   * @param value a string, the value of the attribute.
   *
   * @note This function is only internally used to store multiple rdf:resource 
   * attributes in CVTerm class, and thus should not be used for other purposes.
   *
   * @return integer value indicating success/failure of the
   * function.  @if clike The value is drawn from the
   * enumeration #OperationReturnValues_t. @endif The possible values
   * returned by this function are:
   * @li LIBNUML_OPERATION_SUCCESS
   */
  int addResource (const std::string& name, const std::string& value);

  /** @endcond doxygen-libnuml-internal */


  /**
   * Removes an attribute with the given index from this XMLAttributes set.  
   *
   * @param n an integer the index of the resource to be deleted
   * @return integer value indicating success/failure of the
   * function.  @if clike The value is drawn from the
   * enumeration #OperationReturnValues_t. @endif The possible values
   * returned by this function are:
   * @li LIBNUML_OPERATION_SUCCESS
   * @li LIBNUML_INDEX_EXCEEDS_SIZE
   */
  int removeResource (int n);


  /**
   * Removes an attribute with the given index from this XMLAttributes set.  
   * (This function is an alias of XMLAttributes::removeResource() ).
   *
   * @param n an integer the index of the resource to be deleted
   *
   * @return integer value indicating success/failure of the
   * function.  @if clike The value is drawn from the
   * enumeration #OperationReturnValues_t. @endif The possible values
   * returned by this function are:
   * @li LIBNUML_OPERATION_SUCCESS
   * @li LIBNUML_INDEX_EXCEEDS_SIZE
   */
  int remove (int n);


  /**
   * Removes an attribute with the given local name and namespace URI from 
   * this XMLAttributes set.  
   *
   * @param name   a string, the local name of the attribute.
   * @param uri    a string, the namespace URI of the attribute.
   *
   * @return integer value indicating success/failure of the
   * function.  @if clike The value is drawn from the
   * enumeration #OperationReturnValues_t. @endif The possible values
   * returned by this function are:
   * @li LIBNUML_OPERATION_SUCCESS
   * @li LIBNUML_INDEX_EXCEEDS_SIZE
   */
  int remove (const std::string& name, const std::string& uri = "");


  /**
   * Removes an attribute with the given XMLTriple from this XMLAttributes set.  
   *
   * @param triple an XMLTriple, the XML triple of the attribute.
   *
   * @return integer value indicating success/failure of the
   * function.  @if clike The value is drawn from the
   * enumeration #OperationReturnValues_t. @endif The possible values
   * returned by this function are:
   * @li LIBNUML_OPERATION_SUCCESS
   * @li LIBNUML_INDEX_EXCEEDS_SIZE
   */
  int remove (const XMLTriple& triple); 


  /**
   * Clears (deletes) all attributes in this XMLAttributes object.
   *
   * @return integer value indicating success/failure of the
   * function.  @if clike The value is drawn from the
   * enumeration #OperationReturnValues_t. @endif The possible values
   * returned by this function are:
   * @li LIBNUML_OPERATION_SUCCESS
   */
  int clear();


  /**
   * Return the index of an attribute with the given name.
   *
   * @note A namespace bound to the name is not checked by this function.
   * Thus, if there are multiple attributes with the given local name and
   * different namespaces, the smallest index among those attributes will
   * be returned.  XMLAttributes::getIndex(const std::string& name, const std::string& uri) or
   * XMLAttributes::getIndex(const XMLTriple& triple) should be used to get an index of an
   * attribute with the given local name and namespace.
   *
   * @param name a string, the local name of the attribute for which the 
   * index is required.
   *
   * @return the index of an attribute with the given local name, or -1 if not present.
   */
  int getIndex (const std::string& name) const;


  /**
   * Return the index of an attribute with the given local name and namespace URI.
   *
   * @param name a string, the local name of the attribute.
   * @param uri  a string, the namespace URI of the attribute.
   *
   * @return the index of an attribute with the given local name and namespace URI, 
   * or -1 if not present.
   */
  int getIndex (const std::string& name, const std::string& uri) const;


  /**
   * Return the index of an attribute with the given XMLTriple.
   *
   * @param triple an XMLTriple, the XML triple of the attribute for which 
   *        the index is required.
   *
   * @return the index of an attribute with the given XMLTriple, or -1 if not present.
   */
  int getIndex (const XMLTriple& triple) const;


  /**
   * Return the number of attributes in the set.
   *
   * @return the number of attributes in this XMLAttributes set.
   */
  int getLength () const;


  /**
   * Return the local name of an attribute in this XMLAttributes set (by position).
   *
   * @param index an integer, the position of the attribute whose local name is 
   * required.
   *
   * @return the local name of an attribute in this list (by position).  
   *
   * @note If index is out of range, an empty string will be returned.  Use
   * XMLAttributes::hasAttribute(int index) to test for the attribute
   * existence.
   */
  std::string getName (int index) const;


  /**
   * Return the prefix of an attribute in this XMLAttributes set (by position).
   *
   * @param index an integer, the position of the attribute whose prefix is 
   * required.
   *
   * @return the namespace prefix of an attribute in this list (by
   * position).  
   *
   * @note If index is out of range, an empty string will be returned. Use
   * XMLAttributes::hasAttribute(int index) to test for the attribute
   * existence.
   */
  std::string getPrefix (int index) const;


  /**
   * Return the prefixed name of an attribute in this XMLAttributes set (by position).
   *
   * @param index an integer, the position of the attribute whose prefixed 
   * name is required.
   *
   * @return the prefixed name of an attribute in this list (by
   * position).  
   *
   * @note If index is out of range, an empty string will be returned.  Use
   * XMLAttributes::hasAttribute(int index) to test for attribute existence.
   */
  std::string getPrefixedName (int index) const;


  /**
   * Return the namespace URI of an attribute in this XMLAttributes set (by position).
   *
   * @param index an integer, the position of the attribute whose namespace URI is 
   * required.
   *
   * @return the namespace URI of an attribute in this list (by position).
   *
   * @note If index is out of range, an empty string will be returned.  Use
   * XMLAttributes::hasAttribute(int index) to test for attribute existence.
   */
  std::string getURI (int index) const;


  /**
   * Return the value of an attribute in this XMLAttributes set (by position).
   *
   * @param index an integer, the position of the attribute whose value is 
   * required.
   *
   * @return the value of an attribute in the list (by position).  
   *
   * @note If index is out of range, an empty string will be returned.  Use
   * XMLAttributes::hasAttribute(int index) to test for attribute existence.
   */
  std::string getValue (int index) const;


  /**
   * Return an attribute's value by name.
   *
   * @param name a string, the local name of the attribute whose value is required.
   *
   * @return The attribute value as a string.  
   *
   * @note If an attribute with the given local name does not exist, an
   * empty string will be returned.  Use XMLAttributes::hasAttribute(const std::string name, const std::string uri)
   * to test for attribute existence.  A namespace bound to the local name
   * is not checked by this function.  Thus, if there are multiple
   * attributes with the given local name and different namespaces, the
   * value of an attribute with the smallest index among those attributes
   * will be returned.  XMLAttributes::getValue(const std::string name) or
   * XMLAttributes::getValue(const XMLTriple& triple) should be used to get a value of an
   * attribute with the given local name and namespace.
   */
  std::string getValue (const std::string name) const;


  /**
   * Return a value of an attribute with the given local name and namespace URI.
   *
   * @param name a string, the local name of the attribute whose value is required.
   * @param uri  a string, the namespace URI of the attribute.
   *
   * @return The attribute value as a string.  
   *
   * @note If an attribute with the given local name and namespace URI does
   * not exist, an empty string will be returned.  Use
   * XMLAttributes::hasAttribute(const std::string name, const std::string uri)
   * to test for attribute existence.
   */
  std::string getValue (const std::string name, const std::string uri) const;

  /**
   * Return a value of an attribute with the given XMLTriple.
   *
   * @param triple an XMLTriple, the XML triple of the attribute whose 
   *        value is required.
   *
   * @return The attribute value as a string.  
   *
   * @note If an attribute with the given XMLTriple does not exist, an
   * empty string will be returned.  Use
   * XMLAttributes::hasAttribute(const XMLTriple& triple) to test for attribute existence.
   */
  std::string getValue (const XMLTriple& triple) const;


  /**
   * Predicate returning @c true or @c false depending on whether
   * an attribute with the given index exists in this XMLAttributes.
   *
   * @param index an integer, the position of the attribute.
   *
   * @return @c true if an attribute with the given index exists in this
   * XMLAttributes, @c false otherwise.
   */
  bool hasAttribute (int index) const;


  /**
   * Predicate returning @c true or @c false depending on whether
   * an attribute with the given local name and namespace URI exists in this 
   * XMLAttributes.
   *
   * @param name a string, the local name of the attribute.
   * @param uri  a string, the namespace URI of the attribute.
   *
   * @return @c true if an attribute with the given local name and namespace 
   * URI exists in this XMLAttributes, @c false otherwise.
   */
  bool hasAttribute (const std::string name, const std::string uri="") const;


  /**
   * Predicate returning @c true or @c false depending on whether
   * an attribute with the given XML triple exists in this XMLAttributes.
   *
   * @param triple an XMLTriple, the XML triple of the attribute 
   *
   * @return @c true if an attribute with the given XML triple exists in this
   * XMLAttributes, @c false otherwise.
   *
   */
  bool hasAttribute (const XMLTriple& triple) const;


  /**
   * Predicate returning @c true or @c false depending on whether 
   * this XMLAttributes set is empty.
   * 
   * @return @c true if this XMLAttributes set is empty, @c false otherwise.
   */
  bool isEmpty () const;


  /**
   * Reads the value for the attribute name into value.  If the given local
   * name was not found or value could be interpreted as a boolean, value 
   * is not modified.
   *
   * According to the W3C XML Schema, valid boolean values are: "true",
   * "false", "1", and "0" (case-insensitive).  For more information, see:
   * http://www.w3.org/TR/xmlschema-2/#boolean
   *
   * If an XMLErrorLog is passed in datatype format errors are logged.  If
   * required is true, missing attributes are also logged.
   *
   *
   * @param name a string, the local name of the attribute.
   * @param value a boolean, the value of the attribute.
   * @param log an XMLErrorLog, the error log.
   * @param required a boolean, indicating whether the attribute is required.
   *
   * @returns @c true if the attribute was read into value, @c false otherwise.
   *
   * @note A namespace bound to the given local name is not checked by this
   * function. XMLAttributes::readInto(const XMLTriple, bool&, ...) should
   * be used to read a value for an attribute name with a prefix and
   * namespace.
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
  bool readInto (  const std::string&  name
                 , bool&               value
                 , XMLErrorLog*        log      = 0
                 , bool                required = false ) const;


  /**
   * Reads the value for the attribute with the given XMLTriple into value.  
   * If the XMLTriple was not found or value could be interpreted as a boolean, 
   * value is not modified.
   *
   * According to the W3C XML Schema, valid boolean values are: "true",
   * "false", "1", and "0" (case-insensitive).  For more information, see:
   * http://www.w3.org/TR/xmlschema-2/#boolean
   *
   * If an XMLErrorLog is passed in datatype format errors are logged.  If
   * required is true, missing attributes are also logged.
   *
   *
   * @param triple an XMLTriple, the XML triple of the attribute.
   * @param value a boolean, the value of the attribute.
   * @param log an XMLErrorLog, the error log.
   * @param required a boolean, indicating whether the attribute is required.
   *
   * @returns @c true if the attribute was read into value, @c false otherwise.
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
  bool readInto (  const XMLTriple& triple
                 , bool&        value
                 , XMLErrorLog* log      = 0
                 , bool         required = false ) const;



  /**
   * Reads the value for the attribute name into value.  If the given local
   * name was not found or value could be interpreted as a double, value is 
   * not modified.
   *
   * According to the W3C XML Schema, valid doubles are the same as valid
   * doubles for C and the special values "INF", "-INF", and "NaN"
   * (case-sensitive).  For more information, see:
   * http://www.w3.org/TR/xmlschema-2/#double
   *
   * If an XMLErrorLog is passed in datatype format errors are logged.  If
   * required is true, missing attributes are also logged.
   *
   * @param name a string, the local name of the attribute.
   * @param value a double, the value of the attribute.
   * @param log an XMLErrorLog, the error log.
   * @param required a boolean, indicating whether the attribute is required.
   *
   * @returns @c true if the attribute was read into value, @c false otherwise.
   *
   * @note A namespace bound to the given local name is not checked by this
   * function.  XMLAttributes::readInto(const XMLTriple, double&, ...)
   * should be used to read a value for an attribute name with a prefix and
   * namespace.
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
  bool readInto (  const std::string&  name
                 , double&             value
                 , XMLErrorLog*        log      = 0
                 , bool                required = false ) const;


  /**
   * Reads the value for the attribute with the given XMLTriple into value.  
   * If the triple was not found or value could be interpreted as a double, 
   *value is not modified.
   *
   * According to the W3C XML Schema, valid doubles are the same as valid
   * doubles for C and the special values "INF", "-INF", and "NaN"
   * (case-sensitive).  For more information, see:
   * http://www.w3.org/TR/xmlschema-2/#double
   *
   * If an XMLErrorLog is passed in datatype format errors are logged.  If
   * required is true, missing attributes are also logged.
   *
   * @param triple an XMLTriple, the XML triple of the attribute.
   * @param value a double, the value of the attribute.
   * @param log an XMLErrorLog, the error log.
   * @param required a boolean, indicating whether the attribute is required.
   *
   * @returns @c true if the attribute was read into value, @c false otherwise.
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
  bool readInto (  const XMLTriple&  triple
                 , double&           value
                 , XMLErrorLog*      log      = 0
                 , bool              required = false ) const;


  /**
   * Reads the value for the attribute name into value.  If the given local
   * name was not found or value could be interpreted as an long, value is 
   * not modified.
   *
   * According to the W3C XML Schema valid integers include zero, *all*
   * positive and *all* negative whole numbers.  For practical purposes, we
   * limit values to what can be stored in a long.  For more information,
   * see: http://www.w3.org/TR/xmlschema-2/#integer
   *
   * If an XMLErrorLog is passed in datatype format errors are logged.  If
   * required is true, missing attributes are also logged.
   *
   * @param name a string, the local name of the attribute.
   * @param value a long, the value of the attribute.
   * @param log an XMLErrorLog, the error log.
   * @param required a boolean, indicating whether the attribute is required.
   *
   * @returns @c true if the attribute was read into value, @c false otherwise.
   *
   * @note A namespace bound to the given local name is not checked by this
   * function.  XMLAttributes::readInto(const XMLTriple, long&, ...) should
   * be used to read a value for an attribute name with a prefix and
   * namespace.
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
  bool readInto (  const std::string&  name
                 , long&               value
                 , XMLErrorLog*        log      = 0
                 , bool                required = false ) const;


  /**
   * Reads the value for the attribute XMLTriple into value.  
   * If the XMLTriple was not found or value could be interpreted as a long, 
   * value is not modified.
   *
   * According to the W3C XML Schema valid integers include zero, *all*
   * positive and *all* negative whole numbers.  For practical purposes, we
   * limit values to what can be stored in a long.  For more information,
   * see: http://www.w3.org/TR/xmlschema-2/#integer
   *
   * If an XMLErrorLog is passed in datatype format errors are logged.  If
   * required is true, missing attributes are also logged.
   *
   * @param triple an XMLTriple, the XML triple of the attribute.
   * @param value a long, the value of the attribute.
   * @param log an XMLErrorLog, the error log.
   * @param required a boolean, indicating whether the attribute is required.
   *
   * @returns @c true if the attribute was read into value, @c false otherwise.
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
  bool readInto (  const XMLTriple& triple
                 , long&            value
                 , XMLErrorLog*     log      = 0
                 , bool             required = false ) const;


  /**
   * Reads the value for the attribute name into value.  If the given local
   * name was not found or value could be interpreted as an int, value is 
   * not modified.
   *
   * According to the W3C XML Schema valid integers include zero, *all*
   * positive and *all* negative whole numbers.  For practical purposes, we
   * limit values to what can be stored in a int.  For more information,
   * see: http://www.w3.org/TR/xmlschema-2/#integer
   *
   * If an XMLErrorLog is passed in datatype format errors are logged.  If
   * required is true, missing attributes are also logged.
   *
   * @param name a string, the local name of the attribute.
   * @param value an integer, the value of the attribute.
   * @param log an XMLErrorLog, the error log.
   * @param required a boolean, indicating whether the attribute is required.
   *
   * @returns @c true if the attribute was read into value, @c false otherwise.
   *
   * @note A namespace bound to the given local name is not checked by this
   * function.  XMLAttributes::readInto(const XMLTriple, int&, ...) should
   * be used to read a value for an attribute name with a prefix and
   * namespace.
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
  bool readInto (  const std::string&  name
                 , int&                value
                 , XMLErrorLog*        log      = 0
                 , bool                required = false ) const;


  /**
   * Reads the value for the attribute with the given XMLTriple into value.  
   * If the XMLTriple was not found or value could be interpreted as an int, 
   * value is not modified.
   *
   * According to the W3C XML Schema valid integers include zero, *all*
   * positive and *all* negative whole numbers.  For practical purposes, we
   * limit values to what can be stored in a int.  For more information,
   * see: http://www.w3.org/TR/xmlschema-2/#integer
   *
   * If an XMLErrorLog is passed in datatype format errors are logged.  If
   * required is true, missing attributes are also logged.
   *
   * @param triple an XMLTriple, the XML triple of the attribute.
   * @param value an integer, the value of the attribute.
   * @param log an XMLErrorLog, the error log.
   * @param required a boolean, indicating whether the attribute is required.
   *
   * @returns @c true if the attribute was read into value, @c false otherwise.
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
  bool readInto (  const XMLTriple& triple
                 , int&             value
                 , XMLErrorLog*     log      = 0
                 , bool             required = false ) const;


  /**
   * Reads the value for the attribute name into value.  If the given local
   * name was not found or value could be interpreted as an unsigned int, 
   * value is not modified.
   *
   * According to the W3C XML Schema valid integers include zero, *all*
   * positive and *all* negative whole numbers.  For practical purposes, we
   * limit values to what can be stored in a unsigned int.  For more
   * information, see: http://www.w3.org/TR/xmlschema-2/#integer
   *
   * If an XMLErrorLog is passed in datatype format errors are logged.  If
   * required is true, missing attributes are also logged.
   *
   * @param name a string, the local name of the attribute.
   * @param value an unsigned integer, the value of the attribute.
   * @param log an XMLErrorLog, the error log.
   * @param required a boolean, indicating whether the attribute is required.
   *
   * @returns @c true if the attribute was read into value, @c false otherwise.
   *
   * @note A namespace bound to the given local name is not checked by this
   * function.  XMLAttributes::readInto(const XMLTriple, unsigned int&,
   * ...) should be used to read a value for an attribute name with a
   * prefix and namespace.
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
  bool readInto (  const std::string&  name
                 , unsigned int&       value
                 , XMLErrorLog*        log      = 0
                 , bool                required = false ) const;


  /**
   * Reads the value for the attribute with the given XMLTriple into value.  
   * If the XMLTriple was not found or value could be interpreted as an unsigned int, 
   * value is not modified.
   *
   * According to the W3C XML Schema valid integers include zero, *all*
   * positive and *all* negative whole numbers.  For practical purposes, we
   * limit values to what can be stored in a unsigned int.  For more
   * information, see: http://www.w3.org/TR/xmlschema-2/#integer
   *
   * If an XMLErrorLog is passed in datatype format errors are logged.  If
   * required is true, missing attributes are also logged.
   *
   * @param triple an XMLTriple, the XML triple of the attribute.
   * @param value an unsigned integer, the value of the attribute.
   * @param log an XMLErrorLog, the error log.
   * @param required a boolean, indicating whether the attribute is required.
   *
   * @returns @c true if the attribute was read into value, @c false otherwise.
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
  bool readInto (  const XMLTriple& triple
                 , unsigned int&    value
                 , XMLErrorLog*     log      = 0
                 , bool             required = false ) const;


  /**
   * Reads the value for the attribute name into value.  If the given local
   * name was not found, value is not modified.
   *
   * If an XMLErrorLog is passed in and required is true, missing
   * attributes are logged.
   *
   * @param name a string, the local name of the attribute.
   * @param value a string, the value of the attribute.
   * @param log an XMLErrorLog, the error log.
   * @param required a boolean, indicating whether the attribute is required.
   *
   * @returns @c true if the attribute was read into value, @c false otherwise.
   *
   * @note A namespace bound to the given local name is not checked by this
   * function. XMLAttributes::readInto(const XMLTriple, std::string&, ...)
   * should be used to read a value for an attribute name with a prefix and
   * namespace.
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
  bool readInto (  const std::string&  name
                 , std::string&        value
                 , XMLErrorLog*        log      = 0
                 , bool                required = false ) const;


  /**
   * Reads the value for the attribute with the given XMLTriple into value.  
   * If the XMLTriple was not found, value is not modified.
   *
   * If an XMLErrorLog is passed in and required is true, missing
   * attributes are logged.
   *
   * @param triple an XMLTriple, the XML triple of the attribute.
   * @param value a string, the value of the attribute.
   * @param log an XMLErrorLog, the error log.
   * @param required a boolean, indicating whether the attribute is required.
   *
   * @returns @c true if the attribute was read into value, @c false otherwise.
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
  bool readInto (  const XMLTriple& triple
                 , std::string&     value
                 , XMLErrorLog*     log      = 0
                 , bool              required = false ) const;


  /** @cond doxygen-libnuml-internal */

  /**
   * Writes this XMLAttributes set to stream.
   *
   * @param stream XMLOutputStream, stream to which this XMLAttributes
   * set is to be written.
   */
  void write (XMLOutputStream& stream) const;
  /** @endcond doxygen-libnuml-internal */


  /** @cond doxygen-libnuml-internal */
  /**
   * (Optional) Sets the log used when logging attributeTypeError() and
   * attributeRequired() errors.
   *
   * @param log the log to use
   *
   * @return integer value indicating success/failure of the
   * function.  @if clike The value is drawn from the
   * enumeration #OperationReturnValues_t. @endif The possible values
   * returned by this function are:
   * @li LIBNUML_OPERATION_SUCCESS
   */
  int setErrorLog (XMLErrorLog* log);
  /** @endcond doxygen-libnuml-internal */


#ifndef SWIG

  /** @cond doxygen-libnuml-internal */
  /**
   * Inserts this XMLAttributes set into stream.
   *
   * @param stream XMLOutputStream, stream to which the XMLAttributes
   * set is to be written.
   * @param attributes XMLAttributes, attributes to be written to stream.
   *
   * @return the stream with the attributes inserted.
   */
  LIBLAX_EXTERN
  friend XMLOutputStream&
  operator<< (XMLOutputStream& stream, const XMLAttributes& attributes);
  /** @endcond doxygen-libnuml-internal */

#endif  /* !SWIG */


protected:
  /** @cond doxygen-libnuml-internal */

  /**
   * Used by attributeTypeError().
   */ 
  enum DataType { Boolean = 0, Double = 1, Integer = 2 };


  /**
   * Logs an attribute datatype error.
   *
   * @param name  name of the attribute
   * @param type  the datatype of the attribute value.
   * @param log   the XMLErrorLog where the error should be logged
   */
  void attributeTypeError (  const std::string& name
			   , DataType           type
			   , XMLErrorLog*       log ) const;


  /**
   * Logs an error indicating a required attribute was missing.
   * Used internally.
   * 
   * @param name  name of the attribute
   * @param log   the XMLErrorLog where the error should be logged
   */
  void attributeRequiredError ( const std::string& name, XMLErrorLog* log ) const;


  /**
   * Reads the value for the attribute with the given index into value.  
   * If the attribute was not found or value could be interpreted as a boolean, 
   * value is not modified.
   *
   * According to the W3C XML Schema, valid boolean values are: "true",
   * "false", "1", and "0" (case-insensitive).  For more information, see:
   * http://www.w3.org/TR/xmlschema-2/#boolean
   *
   * If an XMLErrorLog is passed in datatype format errors are logged.  If
   * required is true, missing attributes are also logged.
   *
   *
   * @param index a int, the index of the attribute.
   * @param name a string, the name of the attribute 
   * (only used for an error message (if error detected))
   * @param value a boolean, the value of the attribute.
   * @param log an XMLErrorLog, the error log.
   * @param required a boolean, indicating whether the attribute is required.
   *
   * @returns @c true if the attribute was read into value, @c false otherwise.
   */
  bool readInto (  int          index
	         , const std::string&  name
                 , bool&        value
                 , XMLErrorLog* log      = 0
                 , bool         required = false ) const;


  /**
   * Reads the value for the attribute with the given index into value.  
   * If name was not found or value could be interpreted as a double, value 
   * is not modified.
   *
   * According to the W3C XML Schema, valid doubles are the same as valid
   * doubles for C and the special values "INF", "-INF", and "NaN"
   * (case-sensitive).  For more information, see:
   * http://www.w3.org/TR/xmlschema-2/#double
   *
   * If an XMLErrorLog is passed in datatype format errors are logged.  If
   * required is true, missing attributes are also logged.
   *
   * @param index a int, the index of the attribute.
   * @param name a string, the name of the attribute
   * (only used for an error message (if error detected))
   * @param value a double, the value of the attribute.
   * @param log an XMLErrorLog, the error log.
   * @param required a boolean, indicating whether the attribute is required.
   *
   * @returns @c true if the attribute was read into value, @c false otherwise.
   */
  bool readInto (  int          index
	         , const std::string&  name
                 , double&      value
                 , XMLErrorLog* log      = 0
                 , bool          required = false ) const;


  /**
   * Reads the value for the attribute with the given index into value.  
   * If the attribute was not found or value could be interpreted as a long, 
   * value is not modified.
   *
   * According to the W3C XML Schema valid integers include zero, *all*
   * positive and *all* negative whole numbers.  For practical purposes, we
   * limit values to what can be stored in a long.  For more information,
   * see: http://www.w3.org/TR/xmlschema-2/#integer
   *
   * If an XMLErrorLog is passed in datatype format errors are logged.  If
   * required is true, missing attributes are also logged.
   *
   * @param index a int, the index of the attribute.
   * @param name a string, the name of the attribute
   * (only used for an error message (if error detected))
   * @param value a long, the value of the attribute.
   * @param log an XMLErrorLog, the error log.
   * @param required a boolean, indicating whether the attribute is required.
   *
   * @returns @c true if the attribute was read into value, @c false otherwise.
   */
  bool readInto (  int          index
	         , const std::string&  name
                 , long&         value
                 , XMLErrorLog*  log      = 0
                 , bool          required = false ) const;


  /**
   * Reads the value for the attribute with the given index into value.  
   * If the attribute was not found or value could be interpreted as an integer, 
   * value is not modified.
   *
   * According to the W3C XML Schema valid integers include zero, *all*
   * positive and *all* negative whole numbers.  For practical purposes, we
   * limit values to what can be stored in a int.  For more information,
   * see: http://www.w3.org/TR/xmlschema-2/#integer
   *
   * If an XMLErrorLog is passed in datatype format errors are logged.  If
   * required is true, missing attributes are also logged.
   *
   * @param index a int, the index of the attribute.
   * @param name a string, the name of the attribute
   * (only used for an error message (if error detected))
   * @param value an integer, the value of the attribute.
   * @param log an XMLErrorLog, the error log.
   * @param required a boolean, indicating whether the attribute is required.
   *
   * @returns @c true if the attribute was read into value, @c false otherwise.
   */
  bool readInto (  int          index
	         , const std::string&  name
                 , int&         value
                 , XMLErrorLog* log      = 0
                 , bool          required = false ) const;


  /**
   * Reads the value for the attribute with the given index into value.  
   * If the attribute was not found or value could be interpreted as an 
   * unsigned int, value is not modified.
   *
   * According to the W3C XML Schema valid integers include zero, *all*
   * positive and *all* negative whole numbers.  For practical purposes, we
   * limit values to what can be stored in a unsigned int.  For more
   * information, see: http://www.w3.org/TR/xmlschema-2/#integer
   *
   * If an XMLErrorLog is passed in datatype format errors are logged.  If
   * required is true, missing attributes are also logged.
   *
   * @param index a int, the index of the attribute.
   * @param name a string, the name of the attribute
   * (only used for an error message (if error detected))
   * @param value an unsigned integer, the value of the attribute.
   * @param log an XMLErrorLog, the error log.
   * @param required a boolean, indicating whether the attribute is required.
   *
   * @returns @c true if the attribute was read into value, @c false otherwise.
   */
  bool readInto (  int           index
	         , const std::string&  name
                 , unsigned int& value
                 , XMLErrorLog*  log      = 0
                 , bool          required = false ) const;


  /**
   * Reads the value for the attribute with the given index into value.  
   * If the attribute was not found, value is not modified.
   *
   * If an XMLErrorLog is passed in and required is true, missing
   * attributes are logged.
   *
   * @param index a int, the index of the attribute.
   * @param name a string, the name of the attribute
   * (only used for an error message (if error detected))
   * @param value a string, the value of the attribute.
   * @param log an XMLErrorLog, the error log.
   * @param required a boolean, indicating whether the attribute is required.
   *
   * @returns @c true if the attribute was read into value, @c false otherwise.
   */
  bool readInto (  int          index
	         , const std::string&  name
                 , std::string& value
                 , XMLErrorLog* log      = 0
                 , bool         required = false ) const;



  std::vector<XMLTriple>    mNames;
  std::vector<std::string>  mValues;

  std::string               mElementName;
  XMLErrorLog*              mLog;

  /** @endcond doxygen-libnuml-internal */
};

LIBNUML_CPP_NAMESPACE_END

#endif  /* __cplusplus */



#ifndef SWIG

LIBNUML_CPP_NAMESPACE_BEGIN
BEGIN_C_DECLS

/*-----------------------------------------------------------------------------
 * See the .cpp file for the documentation of the following functions.
 *---------------------------------------------------------------------------*/

LIBLAX_EXTERN
XMLAttributes_t *
XMLAttributes_create (void);


LIBLAX_EXTERN
void
XMLAttributes_free (XMLAttributes_t *xa);


LIBLAX_EXTERN
XMLAttributes_t *
XMLAttributes_clone (const XMLAttributes_t* c);


LIBLAX_EXTERN
int
XMLAttributes_add (XMLAttributes_t *xa, const char *name, const char *value);


LIBLAX_EXTERN
int
XMLAttributes_addWithNamespace (XMLAttributes_t *xa,
				const char *name,
				const char *value,
				const char* uri,
				const char* prefix);

/*
LIBLAX_EXTERN
void
XMLAttributes_addResource (XMLAttributes_t *xa, 
			   const char *name, 
			   const char *value);
*/


LIBLAX_EXTERN
int
XMLAttributes_addWithTriple (XMLAttributes_t *xa, const XMLTriple_t* triple, const char* value);


LIBLAX_EXTERN
int
XMLAttributes_removeResource (XMLAttributes_t *xa, int n);


LIBLAX_EXTERN
int
XMLAttributes_remove (XMLAttributes_t *xa, int n);


LIBLAX_EXTERN
int
XMLAttributes_removeByName (XMLAttributes_t *xa, const char* name);


LIBLAX_EXTERN
int 
XMLAttributes_removeByNS (XMLAttributes_t *xa, const char* name, const char* uri);


LIBLAX_EXTERN
int 
XMLAttributes_removeByTriple (XMLAttributes_t *xa, const XMLTriple_t* triple);


LIBLAX_EXTERN
int 
XMLAttributes_clear(XMLAttributes_t *xa);


LIBLAX_EXTERN
int
XMLAttributes_getIndex (const XMLAttributes_t *xa, const char *name);


LIBLAX_EXTERN
int
XMLAttributes_getIndexByNS (const XMLAttributes_t *xa, const char *name, const char *uri);


LIBLAX_EXTERN
int
XMLAttributes_getIndexByTriple (const XMLAttributes_t *xa, const XMLTriple_t *triple);


LIBLAX_EXTERN
int
XMLAttributes_getLength (const XMLAttributes_t *xa);


LIBLAX_EXTERN
const char *
XMLAttributes_getName (const XMLAttributes_t *xa, int index);


LIBLAX_EXTERN
const char *
XMLAttributes_getPrefix (const XMLAttributes_t *xa, int index);


LIBLAX_EXTERN
const char *
XMLAttributes_getURI (const XMLAttributes_t *xa, int index);


LIBLAX_EXTERN
const char *
XMLAttributes_getValue (const XMLAttributes_t *xa, int index);


LIBLAX_EXTERN
const char *
XMLAttributes_getValueByName (const XMLAttributes_t *xa, const char *name);


LIBLAX_EXTERN
const char *
XMLAttributes_getValueByNS (const XMLAttributes_t *xa, const char* name, const char* uri);
LIBLAX_EXTERN

const char *
XMLAttributes_getValueByTriple (const XMLAttributes_t *xa, const XMLTriple_t* triple);


LIBLAX_EXTERN
int 
XMLAttributes_hasAttribute (const XMLAttributes_t *xa, int index);


LIBLAX_EXTERN
int 
XMLAttributes_hasAttributeWithName (const XMLAttributes_t *xa, const char* name);


LIBLAX_EXTERN
int 
XMLAttributes_hasAttributeWithNS (const XMLAttributes_t *xa, const char* name, const char* uri);


LIBLAX_EXTERN
int 
XMLAttributes_hasAttributeWithTriple (const XMLAttributes_t *xa, const XMLTriple_t* triple);


LIBLAX_EXTERN
int
XMLAttributes_isEmpty (const XMLAttributes_t *xa);


LIBLAX_EXTERN
int
XMLAttributes_readIntoBoolean (XMLAttributes_t *xa,
			       const char *name,
			       int *value,
			       XMLErrorLog_t *log,
			       int required);


LIBLAX_EXTERN
int
XMLAttributes_readIntoBooleanByTriple (XMLAttributes_t *xa,
                               const XMLTriple_t* triple,
                               int *value,
                               XMLErrorLog_t *log,
                               int required);


LIBLAX_EXTERN
int
XMLAttributes_readIntoDouble (XMLAttributes_t *xa,
			      const char *name,
			      double *value,
			      XMLErrorLog_t *log,
			      int required);


LIBLAX_EXTERN
int
XMLAttributes_readIntoDoubleByTriple (XMLAttributes_t *xa,
                               const XMLTriple_t* triple,
                               double *value,
                               XMLErrorLog_t *log,
                               int required);


LIBLAX_EXTERN
int
XMLAttributes_readIntoLong (XMLAttributes_t *xa,
			    const char *name,
			    long *value,
			    XMLErrorLog_t *log,
			    int required);


LIBLAX_EXTERN
int
XMLAttributes_readIntoLongByTriple (XMLAttributes_t *xa,
                               const XMLTriple_t* triple,
                               long *value,
                               XMLErrorLog_t *log,
                               int required);


LIBLAX_EXTERN
int
XMLAttributes_readIntoInt (XMLAttributes_t *xa,
			   const char *name,
			   int *value,
			   XMLErrorLog_t *log,
			   int required);


LIBLAX_EXTERN
int
XMLAttributes_readIntoIntByTriple (XMLAttributes_t *xa,
                               const XMLTriple_t* triple,
                               int *value,
                               XMLErrorLog_t *log,
                               int required);


LIBLAX_EXTERN
int
XMLAttributes_readIntoUnsignedInt (XMLAttributes_t *xa,
				   const char *name,
				   unsigned int *value,
				   XMLErrorLog_t *log,
				   int required);


LIBLAX_EXTERN
int
XMLAttributes_readIntoUnsignedIntByTriple (XMLAttributes_t *xa,
                               const XMLTriple_t* triple,
                               unsigned int *value,
                               XMLErrorLog_t *log,
                               int required);


LIBLAX_EXTERN
int
XMLAttributes_readIntoString (XMLAttributes_t *xa,
			      const char *name,
			      char **value,
			      XMLErrorLog_t *log,
			      int required);


LIBLAX_EXTERN
int
XMLAttributes_readIntoStringByTriple (XMLAttributes_t *xa,
                               const XMLTriple_t* triple,
                               char **value,
                               XMLErrorLog_t *log,
                               int required);

END_C_DECLS
LIBNUML_CPP_NAMESPACE_END

#endif  /* !SWIG */

#endif  /* XMLAttributes_h */
