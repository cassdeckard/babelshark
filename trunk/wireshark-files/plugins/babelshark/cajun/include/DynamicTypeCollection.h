/**********************************************
File : DynamicTypeCollection.h
***********************************************/

#pragma once

#include <list>
#include <string>
#include "Singleton.h"

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
class DynamicTypeCollection : public Singleton<DynamicTypeCollection>
{
public:
   /** The DynamicTypeCollection function is just a simple constructor.
     */
   DynamicTypeCollection();

   /** The ~DynamicTypeCollection function is just a simple destructor.
     * It will call the ClearCollection function.
     */
   ~DynamicTypeCollection();

   typedef std::list<DynamicTypeElement> DynamicTypeCollectionTypeDef;
   typedef DynamicTypeCollectionTypeDef::iterator iterator;
   typedef DynamicTypeCollectionTypeDef::const_iterator const_iterator;
   iterator Begin();
   iterator End();
   const_iterator Begin() const;
   const_iterator End() const;

   /** The Insert function is used to insert a DynamicTypeElement in
     * the DynamicTypeCollection.  There will be one call to the insert
     * function for each dynamictype found in the PDI File.
     */
   iterator Insert(const DynamicTypeElement& dynamicTypeElementToAdd);

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
   void FillDataDictionary();

protected:

private:
   DynamicTypeCollectionTypeDef m_DynamicTypeCollection;
};

} // End namespace
