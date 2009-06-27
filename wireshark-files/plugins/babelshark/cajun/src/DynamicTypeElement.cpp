/***********************************************
File : DynamicTypeElement.cpp
*************************************************/

#pragma once

#include "DynamicTypeElement.h"

namespace PDI
{

   /*** The DynamicTypeElement function is just a simple constructor.
     ***/
   DynamicTypeElement::DynamicTypeElement() {}

   /*** The DynamicTypeElement function with one DynamicTypeElement 
     * parameter is just a simple copy constructor.
     ***/
   DynamicTypeElement::DynamicTypeElement(const DynamicTypeElement& dyn_element) {}

   /*** The ~DynamicTypeElement function is just a simple destructor.
     ***/
   DynamicTypeElement::~DynamicTypeElement() {}

   /*** The SetName function is used to set the m_sName member variable
     * with the name of the dynamictype from the PDI File.  This 
     * corresponds to the "BODY" string in our example.
     ***/
   void DynamicTypeElement::SetName(const std::string& nameIn) { m_sName = nameIn; }
   /*** The Name function returns a std::string containing the value
     * of the m_sName member variable.
     ***/
   const std::string& DynamicTypeElement::Name() const { return m_sName; }

   DynamicTypeElement::iterator DynamicTypeElement::Begin() { return m_DynamicTypeList.begin(); }
   DynamicTypeElement::iterator DynamicTypeElement::End() { return m_DynamicTypeList.end(); }
   DynamicTypeElement::const_iterator DynamicTypeElement::Begin() const { return m_DynamicTypeList.begin(); }
   DynamicTypeElement::const_iterator DynamicTypeElement::End() const { return m_DynamicTypeList.end(); }

   /*** The Insert function is used to insert a DynamicTypeEntry into
     * a DynamicTypeElement.  There will be one call to the insert
     * function for each row inside a dynamictype found in the PDI File.
     ***/

   // Insert at the end of the list.
   DynamicTypeElement::iterator DynamicTypeElement::Insert(const DynamicTypeEntry& entry) {
      return m_DynamicTypeList.insert(m_DynamicTypeList.end(), entry);
   }

   /*** The Clear function is used to empty the DynamicTypeElement list.
     ***/
   void DynamicTypeElement::Clear() { m_DynamicTypeList.clear(); }

} // End namespace
