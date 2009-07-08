/***********************************************
File : DynamicTypeDeclarationCollection.cpp
*************************************************/

#pragma once

#include "DynamicTypeDeclarationCollection.h"
#include "DataDictionary.h"

namespace PDI
{

   DynamicTypeDeclarationCollection::iterator DynamicTypeDeclarationCollection::Begin() { return m_DynamicTypeDeclarationCollection.begin(); }
   DynamicTypeDeclarationCollection::iterator DynamicTypeDeclarationCollection::End() { return m_DynamicTypeDeclarationCollection.end(); }
   DynamicTypeDeclarationCollection::const_iterator DynamicTypeDeclarationCollection::Begin() const { return m_DynamicTypeDeclarationCollection.begin(); }
   DynamicTypeDeclarationCollection::const_iterator DynamicTypeDeclarationCollection::End() const { return m_DynamicTypeDeclarationCollection.end(); }

   /*** The Insert function is used to insert a DynamicTypeDeclarationElement in
     * the DynamicTypeDeclarationCollection.  There will be one call to the insert
     * function for each dynamictype found in the PDI File.
     ***/
   DynamicTypeDeclarationCollection::iterator DynamicTypeDeclarationCollection::Insert(const DynamicTypeDeclarationElement& dynamicTypeElementToAdd) 
   { 
      return m_DynamicTypeDeclarationCollection.insert(m_DynamicTypeDeclarationCollection.end(), dynamicTypeElementToAdd);   
   }

   /*** The FillDataDictionary function iterates over each DynamicTypeDeclarationElement
     * in the collection.  Each DynamicTypeDeclarationElement contains a name and a
     * list of DynamicTypeEntry objects.  For each DynamicTypeEntry, a function
     * call will be made to add it to the DataDictionary.  The function
     * call will be DataDictionary::AddDynamic(std::string alias, 
     *    std::string parameter, std::string typeName)
     * where alias is the name field from DynamicTypeDeclarationElement,
     * parameter is the first field inside DynamicTypeEntry, and
     * typeName is the seconed field inside DynamicTypeEntry.
     ***/
   void DynamicTypeDeclarationCollection::FillDataDictionary() 
   {
      // Loop over all items in the dynamic type collection.
      DynamicTypeDeclarationCollection::const_iterator itElement(Begin()),
                                            itElementEnd(End());
      for (; itElement != itElementEnd; ++itElement)
      {
         DynamicTypeDeclarationElement::const_iterator itEntry(itElement->Begin()),
                                            itEntryEnd(itElement->End());

         for (; itEntry != itEntryEnd; ++itEntry)
         {
            DATA_DICT.AddDynamic(itElement->Name(), itEntry->first, itEntry->second);
            //DATA_DICT.AddDynamic("&BODY", "1", "&ACK");
            //DATA_DICT.AddDynamic("&BODY", "2", "&INIT");
         }
      }
   }


} // End namespace
