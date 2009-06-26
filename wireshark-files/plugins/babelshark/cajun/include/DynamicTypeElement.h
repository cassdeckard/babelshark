/**********************************************
File : DynamicTypeElement.h
***********************************************/

#pragma once

#include <list>
#include <string>


namespace PDI
{

struct DynamicTypeEntry {
   std::string first;
   std::string second;
};

/** The DynamicTypeElement class holds one "dynamictype" read in from a PDI file.
  * An example dynamictype in PDI file format follows:
  * dynamictype BODY {
  *    1 &ACK,
  *    2 &INIT
  * }
  * where BODY is stored in the Name field in the DynamicTypeElement class
  * and 1 &ACK is one entry in the DynamicTypeList.  Each entry is 
  * stored in a DynamicTypeEntry object, which is just a struct with
  * two std::string fields.  The first field is a string instead of
  * an unsigned int, in order to make the definition more flexible.
  *
  * m_DynamicTypeList is defined as std::list<DynamicTypeEntry>
  * Originally we planned to use std::map<std::string, std::string>,
  * but then realized that when we were going to access the data, 
  * we just want to iterate over every item in the list, rather than 
  * look-up an item by passing in the first value.
  */
class DynamicTypeElement
{
public:
   DynamicTypeElement();
   DynamicTypeElement(const DynamicTypeElement& dyn_element);
   ~DynamicTypeElement();

   DynamicTypeElement& operator= (const DynamicTypeElement& dyn_element);

   void SetName(const std::string& nameIn);
   const std::string& Name() const;

   typedef std::list<DynamicTypeEntry> m_DynamicTypeList;
   typedef m_DynamicTypeList::iterator iterator;
   typedef m_DynamicTypeList::const_iterator const_iterator;
   iterator Begin();
   iterator End();
   const_iterator Begin() const;
   const_iterator End() const;

   iterator Insert(const DynamicTypeEntry& entry);
   void Clear();

protected:


private:
   std::string m_sName;

};

} // End namespace
