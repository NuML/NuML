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
 *
 * @class XMLNode
 * @brief Representation of a node in an XML document tree.
 * 
 * Beginning with version 3.0.0, libNUML implements an XML abstraction
 * layer.  This layer presents a uniform XML interface to calling programs
 * regardless of which underlying XML parser libNUML has actually been
 * configured to use.  The basic data object in the XML abstraction is a
 * @em node, represented by XMLNode.
 *
 * An XMLNode can contain any number of children.  Each child is another
 * XMLNode, thereby forming a tree.  The methods XMLNode::getNumChildren()
 * and @if clike XMLNode::getChild() can be used to access the
 * tree structure starting from a given node. @endif@if java XMLNode::getChild(long n)
 * can be used to access the tree structure starting from a given node.
 * @endif
 *
 * Each XMLNode is subclassed from XMLToken, and thus has the same methods
 * available as XMLToken.  These methods include XMLToken::getNamespaces(),
 * XMLToken::getPrefix(), XMLToken::getName(), XMLToken::getURI(), and
 * XMLToken::getAttributes().
 *
 * @section xmlnode-str2xmlnode Conversion between an XML string and an XMLNode
 *
 * LibNUML provides the following utility functions for converting an XML string
 * (e.g., &lt;annotation&gt;...&lt;/annotation&gt;) to/from an XMLNode object.
 * <ul>
 * <li> XMLNode::toXMLString() returns a string representation of the XMLNode object. 
 *
 * <li> XMLNode::convertXMLNodeToString() (static function) returns a string representation 
 * of the given XMLNode object.
 *
 * <li> XMLNode::convertStringToXMLNode() (static function) returns an XMLNode object converted 
 * from the given XML string.
 * </ul>
 *
 * The returned XMLNode object by XMLNode::convertStringToXMLNode() is a dummy root 
 * (container) XMLNode if the given XML string has two or more top-level elements 
 * (e.g., "&lt;p&gt;...&lt;/p&gt;&lt;p&gt;...&lt;/p&gt;"). In the dummy root node, each top-level element in 
 * the given XML string is contained as a child XMLNode. XMLToken::isEOF() can be used 
 * to identify if the returned XMLNode object is a dummy node or not. 
 * Here is an example:
 * @if clike @verbatim
// Checks if the returned XMLNode object by XMLNode::convertStringToXMLNode() is a dummy root node:
                                                                                         
std::string str = "..."; 
XMLNode* xn = XMLNode::convertStringToXMLNode(str);                                      
if (!xn)
{                                                                                      
  // returned value is null (error)                                                    
  ...
}                                                                                      
else if ( xn->isEOF() )                                                                 
{                                                                                      
  // root node is a dummy node                                                         
  for (int i=0; i < xn->getNumChildren(); i++)                                          
  {                                                                                    
    // access to each child node of the dummy node.                                    
    XMLNode& xnChild = xn->getChild(i);                                                  
    ...                                                                                
  }                                                                                    
}                                                                                      
else                                                                                   
{                                                                                      
  // root node is NOT a dummy node                                                     
  ...                                                                                  
}
@endverbatim @endif@if java @verbatim
// Checks if the returned XMLNode object by XMLNode::convertStringToXMLNode() is a dummy root node:

String str = "...";
XMLNode xn = XMLNode.convertStringToXMLNode(str);
if (xn == null)
{
  // returned value is null (error)
  ...
}
else if ( xn.isEOF() )
{
  // root node is a dummy node
  for (int i=0; i < xn.getNumChildren(); i++)
  {
    // access to each child node of the dummy node.
    XMLNode xnChild = xn.getChild(i);
    ...
  }
}
else
{
  // root node is NOT a dummy node
  ...
}
@endverbatim @endif
 *
 */

#ifndef XMLNode_h
#define XMLNode_h

#include <numl/xml/XMLExtern.h>
#include <numl/xml/XMLToken.h>
#include <numl/common/numlfwd.h>


#ifdef __cplusplus

#include <vector>
#include <cstdlib>

LIBNUML_CPP_NAMESPACE_BEGIN

/** @cond doxygen-libnuml-internal */
class XMLInputStream;
class XMLOutputStream;
/** @endcond doxygen-libnuml-internal */


class LIBLAX_EXTERN XMLNode : public XMLToken
{
public:

  /**
   * Creates a new empty XMLNode with no children.
   */
  XMLNode ();


  /**
   * Creates a new XMLNode by copying token.
   *
   * @param token XMLToken to be copied to XMLNode
   */
  XMLNode (const XMLToken& token);

  /**
   * Creates a new start element XMLNode with the given set of attributes and
   * namespace declarations.
   *
   * @param triple XMLTriple.
   * @param attributes XMLAttributes, the attributes to set.
   * @param namespaces XMLNamespaces, the namespaces to set.
   * @param line an unsigned int, the line number (default = 0).
   * @param column an unsigned int, the column number (default = 0).
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
  XMLNode (  const XMLTriple&     triple
           , const XMLAttributes& attributes
           , const XMLNamespaces& namespaces
           , const unsigned int   line   = 0
           , const unsigned int   column = 0 );


  /**
   * Creates a start element XMLNode with the given set of attributes.
   *
   * @param triple XMLTriple.
   * @param attributes XMLAttributes, the attributes to set.
   * @param line an unsigned int, the line number (default = 0).
   * @param column an unsigned int, the column number (default = 0).
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
  XMLNode (  const XMLTriple&      triple
           , const XMLAttributes&  attributes
           , const unsigned int    line   = 0
           , const unsigned int    column = 0 );


  /**
   * Creates an end element XMLNode.
   *
   * @param triple XMLTriple.
   * @param line an unsigned int, the line number (default = 0).
   * @param column an unsigned int, the column number (default = 0).
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
  XMLNode (  const XMLTriple&    triple
           , const unsigned int  line   = 0
           , const unsigned int  column = 0 );


  /**
   * Creates a text XMLNode.
   *
   * @param chars a string, the text to be added to the XMLToken
   * @param line an unsigned int, the line number (default = 0).
   * @param column an unsigned int, the column number (default = 0).
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
  XMLNode (  const std::string&  chars
           , const unsigned int  line   = 0
           , const unsigned int  column = 0 );


  /** @cond doxygen-libnuml-internal */
  /**
   * Creates a new XMLNode by reading XMLTokens from stream.  
   *
   * The stream must be positioned on a start element
   * (<code>stream.peek().isStart() == true</code>) and will be read until
   * the matching end element is found.
   *
   * @param stream XMLInputStream from which XMLNode is to be created.
   */
  XMLNode (XMLInputStream& stream);
  /** @endcond doxygen-libnuml-internal */


  /**
   * Destroys this XMLNode.
   */
  virtual ~XMLNode ();

  
  /**
   * Copy constructor; creates a copy of this XMLNode.
   * 
   * @param orig the XMLNode instance to copy.
   */
  XMLNode(const XMLNode& orig);


  /**
   * Assignment operator for XMLNode.
   */
  XMLNode& operator=(const XMLNode& orig);


  /**
   * Creates and returns a deep copy of this XMLNode.
   * 
   * @return a (deep) copy of this XMLNode.
   */
  XMLNode* clone () const;


  /**
   * Adds a copy of @p node as a child of this XMLNode.
   *
   * The given @p node is added at the end of the list of children.
   *
   * @param node the XMLNode to be added as child.
   *
   * @return integer value indicating success/failure of the
   * function.  @if clike The value is drawn from the
   * enumeration #OperationReturnValues_t. @endif The possible values
   * returned by this function are:
   * @li LIBNUML_OPERATION_SUCCESS
   * @li LIBNUML_INVALID_XML_OPERATION
   *
   * @note The given node is added at the end of the children list.
   */
  int addChild (const XMLNode& node);


  /**
   * Inserts a copy of the given node as the <code>n</code>th child of this
   * XMLNode.
   *
   * If the given index @p n is out of range for this XMLNode instance,
   * the @p node is added at the end of the list of children.  Even in
   * that situation, this method does not throw an error.
   *
   * @param n an integer, the index at which the given node is inserted
   * @param node an XMLNode to be inserted as <code>n</code>th child.
   *
   * @return a reference to the newly-inserted child @p node
   */
  XMLNode& insertChild (unsigned int n, const XMLNode& node);


  /**
   * Removes the <code>n</code>th child of this XMLNode and returns the
   * removed node.
   *
   * It is important to keep in mind that a given XMLNode may have more
   * than one child.  Calling this method erases all existing references to
   * child nodes @em after the given position @p n.  If the index @p n is
   * greater than the number of child nodes in this XMLNode, this method
   * takes no action (and returns NULL).
   *
   * @param n an integer, the index of the node to be removed
   *
   * @return the removed child, or NULL if @p n is greater than the number
   * of children in this node
   *
   * @note The caller owns the returned node and is responsible for deleting it.
   */
  XMLNode* removeChild(unsigned int n);


  /**
   * Removes all children from this node.
   * @return integer value indicating success/failure of the
   * function.  @if clike The value is drawn from the
   * enumeration #OperationReturnValues_t. @endif The possible values
   * returned by this function are:
   * @li LIBNUML_OPERATION_SUCCESS
   */
  int removeChildren();


  /**
   * Returns the <code>n</code>th child of this XMLNode.
   *
   * If the index @p n is greater than the number of child nodes, or it is
   * 0 or less, this method returns an empty node.
   *
   * @param n the index of the node to return
   * 
   * @return the  <code>n</code>th child of this XMLNode.
   */
  XMLNode& getChild (unsigned int n);


  /**
   * Returns the  <code>n</code>th child of this XMLNode.
   *
   * If the index @p n is greater than the number of child nodes, or it is
   * 0 or less, this method returns an empty node.
   *
   * @param n an integer, the index of the node to return
   * 
   * @return the  <code>n</code>th child of this XMLNode.
   */
  const XMLNode& getChild (unsigned int n) const;


  /**
   * Returns the number of children for this XMLNode.
   *
   * @return the number of children for this XMLNode.
   */
  unsigned int getNumChildren () const;


  /** @cond doxygen-libnuml-internal */
  /**
   * Writes this XMLNode and its children to stream.
   *
   * @param stream XMLOutputStream, stream to which this XMLNode
   * is to be written.
   */
  void write (XMLOutputStream& stream) const;
  /** @endcond doxygen-libnuml-internal */


  /**
   * Returns a string representation of this XMLNode. 
   *
   * @return a string derived from this XMLNode.
   */
  std::string toXMLString() const;


  /**
   * Returns a string representation of a given XMLNode. 
   *
   * @param node the XMLNode to be represented as a string
   *
   * @return a string-form representation of @p node
   */
  static std::string convertXMLNodeToString(const XMLNode* node);


  /**
   * Returns an XMLNode which is derived from a string containing XML
   * content.
   *
   * The XML namespace must be defined using argument @p xmlns if the
   * corresponding XML namespace attribute is not part of the string of the
   * first argument.
   *
   * @param xmlstr string to be converted to a XML node.
   * @param xmlns XMLNamespaces the namespaces to set (default value is NULL).
   *
   * @note The caller owns the returned XMLNode and is reponsible for deleting it.
   * The returned XMLNode object is a dummy root (container) XMLNode if the top-level 
   * element in the given XML string is NOT @p html, @p body, @p annotation, @p notes.
   * In the dummy root node, each top-level element in the given XML string is contained
   * as a child XMLNode. XMLToken::isEOF() can be used to identify if the returned XMLNode 
   * object is a dummy node.
   *
   * @return a XMLNode which is converted from string @p xmlstr. NULL is returned
   * if the conversion failed. 
   * 
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
  static XMLNode* convertStringToXMLNode(const std::string& xmlstr,
                                         const XMLNamespaces* xmlns = NULL);


#ifndef SWIG

  /** @cond doxygen-libnuml-internal */
  /**
   * Inserts this XMLNode and its children into stream.
   *
   * @param stream XMLOutputStream, stream to which the XMLNode
   * is to be written.
   * @param node XMLNode, node to be written to stream.
   *
   * @return the stream with the node inserted.
   */
  LIBLAX_EXTERN
  friend
  XMLOutputStream& operator<< (XMLOutputStream& stream, const XMLNode& node);
  /** @endcond doxygen-libnuml-internal */

#endif  /* !SWIG */


protected:
  /** @cond doxygen-libnuml-internal */

  std::vector<XMLNode> mChildren;

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
XMLNode_t *
XMLNode_create (void);


LIBLAX_EXTERN
XMLNode_t *
XMLNode_createFromToken (const XMLToken_t *token);


LIBLAX_EXTERN
XMLNode_t *
XMLNode_createStartElement  (const XMLTriple_t *triple,
			     const XMLAttributes_t *attr);


LIBLAX_EXTERN
XMLNode_t *
XMLNode_createStartElementNS (const XMLTriple_t *triple,
			      const XMLAttributes_t *attr,
			      const XMLNamespaces_t *ns);


LIBLAX_EXTERN
XMLNode_t *
XMLNode_createEndElement (const XMLTriple_t *triple);


LIBLAX_EXTERN
XMLNode_t *
XMLNode_createTextNode (const char *text);


LIBLAX_EXTERN
void
XMLNode_free (XMLNode_t *node);


LIBLAX_EXTERN
XMLNode_t *
XMLNode_clone (const XMLNode_t* c);


LIBLAX_EXTERN
int
XMLNode_addChild (XMLNode_t *node, const XMLNode_t *child);


LIBLAX_EXTERN
XMLNode_t*
XMLNode_insertChild (XMLNode_t *node, unsigned int n, const XMLNode_t *child);


LIBLAX_EXTERN
XMLNode_t* 
XMLNode_removeChild(XMLNode_t *node, unsigned int n);


LIBLAX_EXTERN
int
XMLNode_removeChildren (XMLNode_t *node);


LIBLAX_EXTERN
const char *
XMLNode_getCharacters (const XMLNode_t *node);


LIBLAX_EXTERN
const char *
XMLNode_getName (const XMLNode_t *node);


LIBLAX_EXTERN
int 
XMLNode_setTriple(XMLNode_t *node, const XMLTriple_t *triple);


LIBLAX_EXTERN
const char *
XMLNode_getPrefix (const XMLNode_t *node);


LIBLAX_EXTERN
const char *
XMLNode_getURI (const XMLNode_t *node);



LIBLAX_EXTERN
const XMLAttributes_t *
XMLNode_getAttributes (const XMLNode_t *node);


LIBLAX_EXTERN
int 
XMLNode_setAttributes (XMLNode_t *node, const XMLAttributes_t* attributes);


LIBLAX_EXTERN
int 
XMLNode_addAttr ( XMLNode_t *node,  const char* name, const char* value );
		   

LIBLAX_EXTERN
int 
XMLNode_addAttrWithNS ( XMLNode_t *node,  const char* name
	                , const char* value
    	                , const char* namespaceURI
	                , const char* prefix      );


LIBLAX_EXTERN
int 
XMLNode_addAttrWithTriple (XMLNode_t *node, const XMLTriple_t *triple, const char* value);


LIBLAX_EXTERN
int 
XMLNode_removeAttr (XMLNode_t *node, int n);


LIBLAX_EXTERN
int 
XMLNode_removeAttrByName (XMLNode_t *node, const char* name);


LIBLAX_EXTERN
int 
XMLNode_removeAttrByNS (XMLNode_t *node, const char* name, const char* uri);


LIBLAX_EXTERN
int 
XMLNode_removeAttrByTriple (XMLNode_t *node, const XMLTriple_t *triple);


LIBLAX_EXTERN
int 
XMLNode_clearAttributes(XMLNode_t *node);


LIBLAX_EXTERN
int 
XMLNode_getAttrIndex (const XMLNode_t *node, const char* name, const char* uri);


LIBLAX_EXTERN
int 
XMLNode_getAttrIndexByTriple (const XMLNode_t *node, const XMLTriple_t *triple);


LIBLAX_EXTERN
int 
XMLNode_getAttributesLength (const XMLNode_t *node);


LIBLAX_EXTERN
char* 
XMLNode_getAttrName (const XMLNode_t *node, int index);


LIBLAX_EXTERN
char* 
XMLNode_getAttrPrefix (const XMLNode_t *node, int index);


LIBLAX_EXTERN
char* 
XMLNode_getAttrPrefixedName (const XMLNode_t *node, int index);


LIBLAX_EXTERN
char* 
XMLNode_getAttrURI (const XMLNode_t *node, int index);


LIBLAX_EXTERN
char* 
XMLNode_getAttrValue (const XMLNode_t *node, int index);


LIBLAX_EXTERN
char* 
XMLNode_getAttrValueByName (const XMLNode_t *node, const char* name);


LIBLAX_EXTERN
char* 
XMLNode_getAttrValueByNS (const XMLNode_t *node, const char* name, const char* uri);


LIBLAX_EXTERN
char* 
XMLNode_getAttrValueByTriple (const XMLNode_t *node, const XMLTriple_t *triple);


LIBLAX_EXTERN
int
XMLNode_hasAttr (const XMLNode_t *node, int index);


LIBLAX_EXTERN
int
XMLNode_hasAttrWithName (const XMLNode_t *node, const char* name);

LIBLAX_EXTERN
int
XMLNode_hasAttrWithNS (const XMLNode_t *node, const char* name, const char* uri);


LIBLAX_EXTERN
int
XMLNode_hasAttrWithTriple (const XMLNode_t *node, const XMLTriple_t *triple);


LIBLAX_EXTERN
int
XMLNode_isAttributesEmpty (const XMLNode_t *node);



LIBLAX_EXTERN
const XMLNamespaces_t *
XMLNode_getNamespaces (const XMLNode_t *node);


LIBLAX_EXTERN
int 
XMLNode_setNamespaces(XMLNode_t *node, const XMLNamespaces_t* namespaces);


LIBLAX_EXTERN
int 
XMLNode_addNamespace (XMLNode_t *node, const char* uri, const char* prefix);


LIBLAX_EXTERN
int 
XMLNode_removeNamespace (XMLNode_t *node, int index);


LIBLAX_EXTERN
int 
XMLNode_removeNamespaceByPrefix (XMLNode_t *node, const char* prefix);


LIBLAX_EXTERN
int 
XMLNode_clearNamespaces (XMLNode_t *node);


LIBLAX_EXTERN
int 
XMLNode_getNamespaceIndex (const XMLNode_t *node, const char* uri);


LIBLAX_EXTERN
int 
XMLNode_getNamespaceIndexByPrefix (const XMLNode_t *node, const char* prefix);


LIBLAX_EXTERN
int 
XMLNode_getNamespacesLength (const XMLNode_t *node);


LIBLAX_EXTERN
char* 
XMLNode_getNamespacePrefix (const XMLNode_t *node, int index);


LIBLAX_EXTERN
char* 
XMLNode_getNamespacePrefixByURI (const XMLNode_t *node, const char* uri);


LIBLAX_EXTERN
char* 
XMLNode_getNamespaceURI (const XMLNode_t *node, int index);


LIBLAX_EXTERN
char* 
XMLNode_getNamespaceURIByPrefix (const XMLNode_t *node, const char* prefix);


LIBLAX_EXTERN
int
XMLNode_isNamespacesEmpty (const XMLNode_t *node);


LIBLAX_EXTERN
int
XMLNode_hasNamespaceURI(const XMLNode_t *node, const char* uri);


LIBLAX_EXTERN
int
XMLNode_hasNamespacePrefix(const XMLNode_t *node, const char* prefix);


LIBLAX_EXTERN
int
XMLNode_hasNamespaceNS(const XMLNode_t *node, const char* uri, const char* prefix);
                        


LIBLAX_EXTERN
int
XMLNode_isElement (const XMLNode_t *node);


LIBLAX_EXTERN
int
XMLNode_isEnd (const XMLNode_t *node); 


LIBLAX_EXTERN
int
XMLNode_isEndFor (const XMLNode_t *node, const XMLNode_t *element);


LIBLAX_EXTERN
int
XMLNode_isEOF (const XMLNode_t *node);


LIBLAX_EXTERN
int
XMLNode_isStart (const XMLNode_t *node);


LIBLAX_EXTERN
int
XMLNode_isText (const XMLNode_t *node);


LIBLAX_EXTERN
int
XMLNode_setEnd (XMLNode_t *node);


LIBLAX_EXTERN
int
XMLNode_setEOF (XMLNode_t *node);


LIBLAX_EXTERN
int
XMLNode_unsetEnd (XMLNode_t *node);


LIBLAX_EXTERN
const XMLNode_t *
XMLNode_getChild (const XMLNode_t *node, const int n);


LIBLAX_EXTERN
XMLNode_t *
XMLNode_getChildNC (XMLNode_t *node, const unsigned int n);


LIBLAX_EXTERN
unsigned int
XMLNode_getNumChildren (const XMLNode_t *node);


LIBLAX_EXTERN
char *
XMLNode_toXMLString(const XMLNode_t *node);


LIBLAX_EXTERN
const char *
XMLNode_convertXMLNodeToString(const XMLNode_t *node);


LIBLAX_EXTERN
XMLNode_t *
XMLNode_convertStringToXMLNode(const char * xml, const XMLNamespaces_t* xmlns);

END_C_DECLS
LIBNUML_CPP_NAMESPACE_END

#endif  /* !SWIG */
#endif  /* XMLNode_h */
