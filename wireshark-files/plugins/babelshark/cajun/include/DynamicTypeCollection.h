/**********************************************
File : DynamicTypeCollection.h
***********************************************/

#pragma once

#include <list>
#include <string>

namespace PDI
{

class DynamicTypeElement;

/** The DynamicTypeCollection class is a singleton that holds a list 
  * of DynamicTypeElements. This is a singleton because we will only
  * have one collection of these, and also because we want to make
  * it easier to access the data.  We don't want to have to pass
  * a pointer out to the calling program (the Main.cpp file in the
  * cajun test folder, or the dissector.cpp file in babelshark include
  * folder).
  */
class DynamicTypeCollection
{
public:
   DynamicTypeCollection();
   ~DynamicTypeCollection();

   typedef std::list<DynamicTypeElement> m_DynamicTypeCollection;
   typedef m_DynamicTypeCollection::iterator iterator;
   typedef m_DynamicTypeCollection::const_iterator const_iterator;
   iterator Begin();
   iterator End();
   const_iterator Begin() const;
   const_iterator End() const;

   iterator Insert(const DynamicTypeElement& dynamicTypeElementToAdd);
   /** The ClearCollection function calls the Clear function on
     * each DynamicTypeElement in the collection.
     */
   void ClearCollection();

protected:

private:

};

} // End namespace
