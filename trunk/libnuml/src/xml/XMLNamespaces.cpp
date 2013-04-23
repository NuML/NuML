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


/** @cond doxygen-libnuml-internal */
#include <numl/xml/XMLOutputStream.h>
#include <numl/util/util.h>
/** @endcond doxygen-libnuml-internal */

#include <numl/xml/XMLTriple.h>
#include <numl/xml/XMLNamespaces.h>


/** @cond doxygen-ignored */

using namespace std;

/** @endcond doxygen-ignored */

LIBNUML_CPP_NAMESPACE_BEGIN

/*
 * Creates a new empty list of XML namespace declarations.
 */
XMLNamespaces::XMLNamespaces ()
{
}


/*
 * Destroys this list of XML namespace declarations.
 */
XMLNamespaces::~XMLNamespaces ()
{
}


/*
 * Copy constructor; creates a copy of this XMLNamespaces set.
 */
XMLNamespaces::XMLNamespaces(const XMLNamespaces& orig)
{
  this->mNamespaces.assign( orig.mNamespaces.begin(), orig.mNamespaces.end() ); 
}


/*
 * Assignment operator for XMLNamespaces.
 */
XMLNamespaces& 
XMLNamespaces::operator=(const XMLNamespaces& orig)
{
  if(&orig!=this)
  {
    this->mNamespaces.assign( orig.mNamespaces.begin(), orig.mNamespaces.end() ); 
  }
  
  return *this;
}

/*
 * Creates and returns a deep copy of this XMLNamespaces set.
 * 
 * @return a (deep) copy of this XMLNamespaces set.
 */
XMLNamespaces* 
XMLNamespaces::clone () const
{
  return new XMLNamespaces(*this);
}


/*
 * Appends an XML namespace prefix/URI pair to this list of namespace
 * declarations.
 * If there is an XML namespace with the given prefix in this list,
 * then the existing XML namespace will be overwritten by the new one.
 */
int
XMLNamespaces::add (const std::string& uri, const std::string& prefix)
{
  //
  // avoids duplicate prefix
  //
  if ( prefix.empty()    ) removeDefault();
  if ( hasPrefix(prefix) ) remove(prefix);

  mNamespaces.push_back( make_pair(prefix, uri) );
  return LIBNUML_OPERATION_SUCCESS;
}


/*
 * @param index an integer, position of the removed namespace.
 */
int XMLNamespaces::remove (int index)
{
  if (index < 0 || index >= getLength()) 
  {
    return LIBNUML_INDEX_EXCEEDS_SIZE;
  }

  vector<PrefixURIPair>::iterator it = mNamespaces.begin() + index;
  mNamespaces.erase(it);

  return LIBNUML_OPERATION_SUCCESS;
}



/*
 * @param prefix a string, prefix of the required namespace.
 */
int XMLNamespaces::remove (const std::string& prefix)
{
  int index = getIndexByPrefix(prefix);
  if(index == -1) 
  {
    return LIBNUML_INDEX_EXCEEDS_SIZE;
  }

  vector<PrefixURIPair>::iterator it = mNamespaces.begin() + index;
  mNamespaces.erase(it);

  return LIBNUML_OPERATION_SUCCESS;
}


/*
 * Clears (deletes) all XML namespace declarations.
 */
int
XMLNamespaces::clear ()
{
  mNamespaces.clear();
  if (mNamespaces.empty())
  {
    return LIBNUML_OPERATION_SUCCESS;
  }
  else
  {
    return LIBNUML_OPERATION_FAILED;
  }
}


/*
 * Lookup the index of an XML namespace declaration by URI.
 *
 * @return the index of the given declaration, or -1 if not present.
 */
int
XMLNamespaces::getIndex (const std::string uri) const
{
  for (int index = 0; index < getLength(); ++index)
  {
    if (getURI(index) == uri) return index;
  }
  
  return -1;
}


/*
 * Lookup the index of an XML namespace declaration by Prefix.
 *
 * @return the index of the given declaration, or -1 if not present.
 */
int
XMLNamespaces::getIndexByPrefix (const std::string prefix) const
{
  for (int index = 0; index < getLength(); ++index)
  {
     if (getPrefix(index) == prefix) return index;
  }
  
  return -1;
}


/*
 * @return the number of attributes in this list.
 */
int
XMLNamespaces::getLength () const
{
  return mNamespaces.size();
}


/*
 * @return the prefix of an XML namespace declaration in this list (by
 * position).  If index is out of range, an empty string will be
 * returned.
 */
std::string
XMLNamespaces::getPrefix (int index) const
{
  return (index < 0 || index >= getLength()) ? "" : mNamespaces[index].first;
}


/*
 * @return the prefix of an XML namespace declaration given its URI.  If
 * URI does not exist, an empty string will be returned.
 */
std::string
XMLNamespaces::getPrefix (const std::string& uri) const
{
  return getPrefix( getIndex(uri) );
}


/*
 * @return the URI of an XML namespace declaration in this list (by
 * position).  If index is out of range, an empty string will be
 * returned.
 */
std::string
XMLNamespaces::getURI (int index) const
{
  return (index < 0 || index >= getLength()) ? "" : mNamespaces[index].second;
}


/*
 * @return the URI of an XML namespace declaration given its prefix.  If
 * no prefix is given and a default namespace exists it will be returned.
 * If prefix does not exist, an empty string will be returned.
 */
std::string
XMLNamespaces::getURI (const std::string& prefix) const
{
  for (int index = 0; index < getLength(); ++index)
  {
    if (getPrefix(index) == prefix) return getURI(index);
  }
  
  return "";
}


/*
 * @return true if this XMLNamespaces set is empty, false otherwise.
 */
bool
XMLNamespaces::isEmpty () const
{
  return (getLength() == 0);
}


 /*
  * @return @c true if an XML Namespace with the given URI is contained in this 
  * XMLNamespaces list,  @c false otherwise.
  */
bool XMLNamespaces::hasURI(const std::string& uri) const
{
  return ( getIndex(uri) != -1 );
}


/*
 * @return @c true if an XML Namespace with the given URI is contained in this 
 * XMLNamespaces list, @c false otherwise.
 */
bool XMLNamespaces::hasPrefix(const std::string& prefix) const
{
  return ( getIndexByPrefix(prefix) != -1 );
}


/*
 * @return @c true if an XML Namespace with the given uri/prefix pair is 
 * contained in this XMLNamespaces list,  @c false otherwise.
 */
bool XMLNamespaces::hasNS(const std::string& uri, const std::string& prefix) const
{
  for (int i= 0; i < getLength(); ++i)
  {
     if ( (getURI(i) == uri) && (getPrefix(i) == prefix) ) 
       return true;
  }

  return false;
}


/** @cond doxygen-libnuml-internal */
/*
 * Removes the default XML namespace.
 */
void
XMLNamespaces::removeDefault ()
{
  vector<PrefixURIPair>::iterator i;

  for (i = mNamespaces.begin(); i != mNamespaces.end(); ++i)
  {
    if (i->first.empty())
    {
      mNamespaces.erase(i);
      break;
    }
  }
}
/** @endcond doxygen-libnuml-internal */

#ifndef SWIG

/** @cond doxygen-libnuml-internal */
/*
 * Writes the XML namespace declarations to stream.
 */
void
XMLNamespaces::write (XMLOutputStream& stream) const
{
  for (int n = 0; n < getLength(); ++n)
  {
    if ( getPrefix(n).empty() )
    {
      stream.writeAttribute( "xmlns", getURI(n) );
    }
    else
    {
      const XMLTriple triple(getPrefix(n), "", "xmlns");
      stream.writeAttribute( triple, getURI(n) );
    }
  }
}
/** @endcond doxygen-libnuml-internal */


/** @cond doxygen-libnuml-internal */
/*
 * Inserts this XML namespace declarations into stream.
 */
LIBLAX_EXTERN
XMLOutputStream&
operator<< (XMLOutputStream& stream, const XMLNamespaces& namespaces)
{
  namespaces.write(stream);
  return stream;
}
/** @endcond doxygen-libnuml-internal */

#endif  /* !SWIG */


/** @cond doxygen-c-only */

/**
 * Creates a new empty XMLNamespaces_t structure.
 */
LIBLAX_EXTERN
XMLNamespaces_t *
XMLNamespaces_create (void)
{
  return new(nothrow) XMLNamespaces;
}


/**
 * Frees the given XMLNamespaces_t structure.
 *
 * @param ns XMLNamespaces structure to be freed.
 **/
LIBLAX_EXTERN
void
XMLNamespaces_free (XMLNamespaces_t *ns)
{
  delete ns;
}


/**
 * Creates a deep copy of the given XMLNamespaces_t structure
 * 
 * @param ns the XMLNamespaces_t structure to be copied
 * 
 * @return a (deep) copy of the given XMLNamespaces_t structure.
 */
LIBLAX_EXTERN
XMLNamespaces_t *
XMLNamespaces_clone (const XMLNamespaces_t* ns)
{
  return static_cast<XMLNamespaces*>( ns->clone() );
}


/**
 * Appends an XML namespace prefix/URI pair to this XMLNamespaces_t 
 * structure.
 *
 * @param ns XMLNamespaces structure.
 * @param uri a string, the uri for the namespace.
 * @param prefix a string, the prefix for the namespace.
 *
 * @return integer value indicating success/failure of the
 * function.  @if clike The value is drawn from the
 * enumeration #OperationReturnValues_t. @endif The possible values
 * returned by this function are:
 * @li LIBNUML_OPERATION_SUCCESS
 */
LIBLAX_EXTERN
int
XMLNamespaces_add (XMLNamespaces_t *ns, 
		   const char *uri, const char *prefix)
{
  return ns->add(uri, prefix);
}


/**
 * Removes an XML Namespace stored in the given position of this list.
 *
 * @param index an integer, position of the removed namespace.
 *
 * @return integer value indicating success/failure of the
 * function.  @if clike The value is drawn from the
 * enumeration #OperationReturnValues_t. @endif The possible values
 * returned by this function are:
 * @li LIBNUML_OPERATION_SUCCESS
 * @li LIBNUML_INDEX_EXCEEDS_SIZE
 */
LIBLAX_EXTERN
int XMLNamespaces_remove (XMLNamespaces_t *ns, int index)
{
  return ns->remove(index);
}


/**
 * Removes an XML Namespace with the given Prefix.
 *
 * @param prefix a string, prefix of the required namespace.
 *
 * @return integer value indicating success/failure of the
 * function.  @if clike The value is drawn from the
 * enumeration #OperationReturnValues_t. @endif The possible values
 * returned by this function are:
 * @li LIBNUML_OPERATION_SUCCESS
 * @li LIBNUML_INDEX_EXCEEDS_SIZE
 */
LIBLAX_EXTERN
int XMLNamespaces_removeByPrefix (XMLNamespaces_t *ns, const char* prefix)
{
  return ns->remove(prefix);
}



/**
 * Clears this XMLNamespaces_t structure.
 *
 * @param ns XMLNamespaces structure.
 *
 * @return integer value indicating success/failure of the
 * function.  @if clike The value is drawn from the
 * enumeration #OperationReturnValues_t. @endif The possible values
 * returned by this function are:
 * @li LIBNUML_OPERATION_SUCCESS
 * @li LIBNUML_OPERATION_FAILED
 **/
LIBLAX_EXTERN
int
XMLNamespaces_clear (XMLNamespaces_t *ns)
{
  return ns->clear();
}


/**
 * Lookup the index of an XML namespace declaration by URI.
 *
 * @param uri a string, uri of the required namespace.
 *
 * @return the index of the given declaration, or -1 if not present.
 */
LIBLAX_EXTERN
int
XMLNamespaces_getIndex (const XMLNamespaces_t *ns, const char *uri)
{
  return ns->getIndex(uri);
}


/**
 * Look up the index of an XML namespace declaration by Prefix.
 *
 * @param prefix a string, prefix of the required namespace.
 *
 * @return the index of the given declaration, or -1 if not present.
 */
LIBLAX_EXTERN
int XMLNamespaces_getIndexByPrefix (const XMLNamespaces_t *ns, const char* prefix)
{
  return ns->getIndexByPrefix(prefix);
}


/**
 * 
 **/
LIBLAX_EXTERN
int
XMLNamespaces_getLength (const XMLNamespaces_t *ns)
{
  return ns->getLength();
}


/**
 * 
 **/
LIBLAX_EXTERN
const char *
XMLNamespaces_getPrefix (const XMLNamespaces_t *ns, int index)
{
  /**
   * I did this because MSVC and gcc handle .c_str() in different ways
   * meaning that with MSVC the actual string goes out of scope before 
   * the char * is returned and thus the char * is garbage once returned
   */
  if (ns->getPrefix(index).empty())
    return NULL;
  else
    return safe_strdup(ns->getPrefix(index).c_str());
}


/**
 * 
 **/
LIBLAX_EXTERN
const char *
XMLNamespaces_getPrefixByURI (const XMLNamespaces_t *ns, const char *uri)
{
  /**
   * I did this because MSVC and gcc handle .c_str() in different ways
   * meaning that with MSVC the actual string goes out of scope before 
   * the char * is returned and thus the char * is garbage once returned
   */
  if (ns->getPrefix(uri).empty())
    return NULL;
  else
    return safe_strdup(ns->getPrefix(uri).c_str());
}

/**
 * 
 **/
LIBLAX_EXTERN
const char *
XMLNamespaces_getURI (const XMLNamespaces_t *ns, int index)
{
  /**
   * I did this because MSVC and gcc handle .c_str() in different ways
   * meaning that with MSVC the actual string goes out of scope before 
   * the char * is returned and thus the char * is garbage once returned
   */
  if (ns->getURI(index).empty())
    return NULL;
  else
    return safe_strdup(ns->getURI(index).c_str());
}

/**
 * 
 **/
LIBLAX_EXTERN
const char *
XMLNamespaces_getURIByPrefix (const XMLNamespaces_t *ns, const char *prefix)
{
  /**
   * I did this because MSVC and gcc handle .c_str() in different ways
   * meaning that with MSVC the actual string goes out of scope before 
   * the char * is returned and thus the char * is garbage once returned
   */
  if (ns->getURI(prefix).empty())
    return NULL;
  else
    return safe_strdup(ns->getURI(prefix).c_str());
}


/**
 * Predicate returning @c true or @c false depending on whether 
 * this XMLNamespaces list is empty.
 * 
 * @return @c true if this XMLNamespaces list is empty, @c false otherwise.
 */
LIBLAX_EXTERN
int
XMLNamespaces_isEmpty (const XMLNamespaces_t *ns)
{
  return ns->isEmpty();
}


/**
 * Predicate returning @c true or @c false depending on whether 
 * an XML Namespace with the given URI is contained in this XMLNamespaces list.
 * 
 * @return @c true if an XML Namespace with the given URI is contained in this 
 * XMLNamespaces list,  @c false otherwise.
 */
LIBLAX_EXTERN
int 
XMLNamespaces_hasURI(const XMLNamespaces_t *ns, const char* uri)
{
  return ns->hasURI(uri);
}


/**
 * Predicate returning @c true or @c false depending on whether 
 * an XML Namespace the given Prefix is contained in this XMLNamespaces list.
 * 
 * @return @c true if an XML Namespace with the given URI is contained in this 
 * XMLNamespaces list, @c false otherwise.
 */
LIBLAX_EXTERN
int 
XMLNamespaces_hasPrefix(const XMLNamespaces_t *ns, const char* prefix)
{
  return ns->hasPrefix(prefix);
}


/**
 * Predicate returning @c true or @c false depending on whether
 * an XML Namespace with the given URI is contained in this XMLNamespaces list.
 *
 * @return @c true if an XML Namespace with the given uri/prefix pair is contained
 * in this XMLNamespaces list,  @c false otherwise.
 */
LIBLAX_EXTERN
int 
XMLNamespaces_hasNS(const XMLNamespaces_t *ns, const char* uri, const char* prefix)
{
  return ns->hasNS(uri, prefix);
}


/** @endcond doxygen-c-only */

LIBNUML_CPP_NAMESPACE_END
