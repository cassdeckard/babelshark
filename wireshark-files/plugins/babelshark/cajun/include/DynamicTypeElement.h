/***********************************************
File : DynamicTypeElement.h
*************************************************/

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
  * <pre>
  * dynamictype BODY {
  *    1 &ACK,
  *    2 &INIT
  *  }
  * </pre>
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
   /** The SetName function is used to set the m_sName member variable
   with the name of the dynamictype from the PDI File.  This
   corresponds to the "BODY" string in our example.
     ***/
   void SetName(const std::string& nameIn);
   /** The Name function returns a std::string containing the value
   of the m_sName member variable.
     ***/
   const std::string& Name() const;

   typedef std::list<DynamicTypeEntry> DynamicTypeList;
   typedef DynamicTypeList::iterator iterator;
   typedef DynamicTypeList::const_iterator const_iterator;
   iterator Begin();
   iterator End();
   const_iterator Begin() const;
   const_iterator End() const;

   /** The Insert function is used to insert a DynamicTypeEntry into
   a DynamicTypeElement.  There will be one call to the insert
   function for each row inside a dynamictype found in the PDI File.
     ***/
   iterator Insert(const DynamicTypeEntry& entry);

   //iterator FindNext(const std::string& name);
   //const_iterator FindNext(const std::string& name) const;

   /** The Clear function is used to empty the DynamicTypeElement list.
     ***/
   void Clear();

protected:


private:
   std::string m_sName;
   DynamicTypeList m_DynamicTypeList;
};

} // End namespace
