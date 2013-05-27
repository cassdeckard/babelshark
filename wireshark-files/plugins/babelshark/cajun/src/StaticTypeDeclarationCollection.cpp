#include "StaticTypeDeclarationCollection.h"
#include "DataDictionary.h"
#include "InstructionSet.h"
#include "UintElement.h"
#include "PadElement.h"
#include "StaticTreeVisitor.h"

namespace PDI
{

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
         std::string sNameOfStaticType = itElement->GetLabel();
         StaticTreeVisitor StaticTreeVisitor(sNameOfStaticType);
//         StaticTreeVisitor StaticTreeVisitor((*itElement)->GetLabel());
			(*itElement).Accept(StaticTreeVisitor);
      }
	}
}
