#ifndef STATIC_TYPE_DEFINITION_COLLECTION_H
#define STATIC_TYPE_DEFINITION_COLLECTION_H

#include "singleton.h"
#include "StaticTypeDeclarationElement.h"
#include <list>

namespace PDI
{
	class StaticTypeDeclarationCollection : public Singleton<StaticTypeDeclarationCollection>
	{
		public:
			typedef std::list<StaticTypeDeclaration> StaticTypeDefinitionCollection;
			typedef StaticTypeDefinitionCollection::iterator Iterator;
			typedef StaticTypeDefinitionCollection::const_iterator ConstIter;

			/** Iterator accessors.  Both Const iterators and regular
			*/
			Iterator Begin();
			Iterator End();

			ConstIter Begin() const;
			ConstIter End() const;

			/** Inserts a StaticTypeElement into the Collection
			***/
			void Insert(StaticTypeDeclaration& element);

			/** The FillDataDictionary function iterates over each StaticTypeDefinition
			 * in the collection.  Each StaticTypeElement contains a name and an Array of Elements.  For each DynamicTypeEntry, a function
			 * call will be made to add it to the DataDictionary.  The function
			 * call will be DataDictionary::AddDynamic(std::string alias,
			 *    std::string parameter, std::string typeName)
			 * where alias is the name field from DynamicTypeDeclarationElement,
			 * parameter is the first field inside DynamicTypeEntry, and
			 * typeName is the seconed field inside DynamicTypeEntry.
			 ***/
			void FillDataDictionary();
		private:
			StaticTypeDefinitionCollection _Collection;
	};
}

#endif //STATIC_TYPE_DEFINITION_COLLECTION_H