#include "StaticTypeDeclarationCollection.h"
#include "DataDictionary.h"
#include "InstructionSet.h"
#include "UintElement.h"
#include "PadElement.h"
#include "TreeVisitor.h"

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

         /////TreeVisitor treeVisitor((*itEntry).Name());
         for (; itEntry != itEntryEnd; ++itEntry)
         {
            //TODO (DAN)
            // Change the code below to call the visit function on itEntry.
			//itEntry.visit(
			/////(*itEntry).Accept(treeVisitor);
            BabelShark::InstructionSet* tempTree;
			//tempTree = new BabelShark::InstructionSet((*itEntry).GetSize(), (*itEntry).GetLabel());
			//tempTree = 
            tempTree = new BabelShark::InstructionSet(1, "TestInit");
            tempTree->Add(new BabelShark::UintElement(7, "Age"));
            tempTree->Add(new BabelShark::PadElement(56, "Pad"));
			//BabelShark::DataDictionary::Instance()->AddStatic(
            //BabelShark::DataDictionary::Instance()->AddStatic("o rly?"/*(itElement)->GetLabel()*/, tempTree);
         }
      }
	}
}
