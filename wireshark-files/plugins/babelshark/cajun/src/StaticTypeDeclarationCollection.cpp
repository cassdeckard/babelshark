#include "StaticTypeDeclarationCollection.h"
#include "DataDictionary.h"

namespace PDI
{
	StaticTypeDeclarationCollection::StaticTypeDeclarationCollection()
	{

	}

	StaticTypeDeclarationCollection::Iterator StaticTypeDeclarationCollection::Begin()
	{
		return _Collection.begin();
	}

	StaticTypeDeclarationCollection::Iterator StaticTypeDeclarationCollection::End()
	{
		return _Collection.end();
	}

	StaticTypeDeclarationCollection::ConstIter StaticTypeDeclarationCollection::Begin() const
	{
		return _Collection.begin();
	}

	StaticTypeDeclarationCollection::ConstIter StaticTypeDeclarationCollection::End() const
	{
		return _Collection.end();
	}

	void StaticTypeDeclarationCollection::Insert(StaticTypeDeclaration& element)
	{
		_Collection.insert(_Collection.end(), element);
	}

	void StaticTypeDeclarationCollection::FillDataDictionary()
	{
      StaticTypeDeclarationCollection::ConstIter itElement(Begin()),
                                            itElementEnd(End());
      for (; itElement != itElementEnd; ++itElement)
      {
         StaticTypeDeclaration::const_iterator itEntry(itElement->Begin()),
                                            itEntryEnd(itElement->End());

         for (; itEntry != itEntryEnd; ++itEntry)
         {
            BabelShark::DataDictionary::Instance()->AddStatic("o rly?"/*(itElement)->GetLabel()*/, *itEntry);
         }
      }
	}
}