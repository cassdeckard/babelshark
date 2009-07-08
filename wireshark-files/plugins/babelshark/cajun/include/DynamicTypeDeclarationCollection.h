/***********************************************
File : DynamicTypeDeclarationCollection.h
*************************************************/

#pragma once

#include <list>
#include <string>
#include "Singleton.h"
#include "DynamicTypeDeclarationElement.h"

namespace PDI
{

class DynamicTypeDeclarationElement;
/** The DynamicTypeDeclarationCollection class is a singleton that holds a list
  * of DynamicTypeDeclarationElements. This is a singleton because we will only
  * have one collection of these, and also because we want to make
  * it easier to access the data.  We don't want to have to pass
  * a pointer out to the calling program (the Main.cpp file in the
  * cajun test folder, or the dissector.cpp file in babelshark include
  * folder).
  *
  * <pre>
  * Design Pattern: Singleton
  * Design Pattern Role: Singleton
  * Other Participants: 
  *    The Singleton class is actually what implements the features of the Singleton
  *    design pattern.  This class inherits from the Singleton class.
  * </pre>
*************************************************/
class DynamicTypeDeclarationCollection : public Singleton<DynamicTypeDeclarationCollection>
{
public:
   typedef std::list<DynamicTypeDeclarationElement> DynamicTypeDeclarationCollectionTypeDef;
   typedef DynamicTypeDeclarationCollectionTypeDef::iterator iterator;
   typedef DynamicTypeDeclarationCollectionTypeDef::const_iterator const_iterator;
   iterator Begin();
   iterator End();
   const_iterator Begin() const;
   const_iterator End() const;

   /** The Insert function is used to insert a DynamicTypeDeclarationElement in
     * the DynamicTypeDeclarationCollection.  There will be one call to the insert
     * function for each dynamictype found in the PDI File.
     ***/
   iterator Insert(const DynamicTypeDeclarationElement& dynamicTypeElementToAdd);

   /** The FillDataDictionary function iterates over each DynamicTypeDeclarationElement
     * in the collection.  Each DynamicTypeDeclarationElement contains a name and a
     * list of DynamicTypeEntry objects.  For each DynamicTypeEntry, a function
     * call will be made to add it to the DataDictionary.  The function
     * call will be DataDictionary::AddDynamic(std::string alias,
     *    std::string parameter, std::string typeName)
     * where alias is the name field from DynamicTypeDeclarationElement,
     * parameter is the first field inside DynamicTypeEntry, and
     * typeName is the seconed field inside DynamicTypeEntry.
     ***/
   void FillDataDictionary();

protected:

private:
   DynamicTypeDeclarationCollectionTypeDef m_DynamicTypeDeclarationCollection;
};

} // End namespace
