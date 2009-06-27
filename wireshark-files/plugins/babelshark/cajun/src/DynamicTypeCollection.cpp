/**********************************************
File : DynamicTypeCollection.cpp
***********************************************/

#pragma once

#include "DynamicTypeCollection.h"
#include "DynamicTypeElement.h"

namespace PDI
{

   /** The DynamicTypeCollection function is just a simple constructor.
     */
   DynamicTypeCollection::DynamicTypeCollection() {}

   /** The ~DynamicTypeCollection function is just a simple destructor.
     * It will call the ClearCollection function.
     */
   DynamicTypeCollection::~DynamicTypeCollection() {}

   DynamicTypeCollection::iterator DynamicTypeCollection::Begin() { return m_DynamicTypeCollection.begin(); }
   DynamicTypeCollection::iterator DynamicTypeCollection::End() { return m_DynamicTypeCollection.end(); }
   DynamicTypeCollection::const_iterator DynamicTypeCollection::Begin() const { return m_DynamicTypeCollection.begin(); }
   DynamicTypeCollection::const_iterator DynamicTypeCollection::End() const { return m_DynamicTypeCollection.end(); }

   /** The Insert function is used to insert a DynamicTypeElement in
     * the DynamicTypeCollection.  There will be one call to the insert
     * function for each dynamictype found in the PDI File.
     */
   DynamicTypeCollection::iterator DynamicTypeCollection::Insert(const DynamicTypeElement& dynamicTypeElementToAdd) 
   { 
      return m_DynamicTypeCollection.insert(m_DynamicTypeCollection.end(), dynamicTypeElementToAdd);   
   }

   /** The FillDataDictionary function iterates over each DynamicTypeElement
     * in the collection.  Each DynamicTypeElement contains a name and a
     * list of DynamicTypeEntry objects.  For each DynamicTypeEntry, a function
     * call will be made to add it to the DataDictionary.  The function
     * call will be DataDictionary::AddDynamic(std::string alias, 
     *    std::string parameter, std::string typeName)
     * where alias is the name field from DynamicTypeElement,
     * parameter is the first field inside DynamicTypeEntry, and
     * typeName is the seconed field inside DynamicTypeEntry.
     */
   void DynamicTypeCollection::FillDataDictionary() {}


} // End namespace
