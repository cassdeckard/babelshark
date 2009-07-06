/***********************************************
File : DynamicTypeDeclarationElement.cpp
*************************************************/

#pragma once

#include "DynamicTypeDeclarationElement.h"

namespace PDI
{

   /*** The SetName function is used to set the m_sName member variable
     * with the name of the dynamictype from the PDI File.  This 
     * corresponds to the "BODY" string in our example.
     ***/
   void DynamicTypeDeclarationElement::SetName(const std::string& nameIn) { m_sName = nameIn; }
   /*** The Name function returns a std::string containing the value
     * of the m_sName member variable.
     ***/
   const std::string& DynamicTypeDeclarationElement::Name() const { return m_sName; }

   DynamicTypeDeclarationElement::iterator DynamicTypeDeclarationElement::Begin() { return m_DynamicTypeList.begin(); }
   DynamicTypeDeclarationElement::iterator DynamicTypeDeclarationElement::End() { return m_DynamicTypeList.end(); }
   DynamicTypeDeclarationElement::const_iterator DynamicTypeDeclarationElement::Begin() const { return m_DynamicTypeList.begin(); }
   DynamicTypeDeclarationElement::const_iterator DynamicTypeDeclarationElement::End() const { return m_DynamicTypeList.end(); }

   /*** The Insert function is used to insert a DynamicTypeEntry into
     * a DynamicTypeDeclarationElement.  There will be one call to the insert
     * function for each row inside a dynamictype found in the PDI File.
     ***/

   // Insert at the end of the list.
   DynamicTypeDeclarationElement::iterator DynamicTypeDeclarationElement::Insert(const DynamicTypeEntry& entry) {
      return m_DynamicTypeList.insert(m_DynamicTypeList.end(), entry);
   }

   /*** The Clear function is used to empty the DynamicTypeDeclarationElement list.
     ***/
   void DynamicTypeDeclarationElement::Clear() { m_DynamicTypeList.clear(); }

} // End namespace
