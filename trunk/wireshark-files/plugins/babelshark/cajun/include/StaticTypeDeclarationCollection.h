#ifndef STATIC_TYPE_DEFINITION_COLLECTION_H
#define STATIC_TYPE_DEFINITION_COLLECTION_H


namespace PDI
{
	class StaticTypeDeclarationCollection : public Singleton<StaticTypeCollection>
	{
		public:
			typedef std::list<StaticTypeElement> StaticTypeDefinitionCollection;
			typedef StaticTypeDefinitionCollection::iterator StaticTypeIterator;
			typedef StaticTypeDefinitionCollection::const_iterator StaticTypeConstIter;

			/** Iterator accessors.  Both Const iterators and regular
			*/
			StaticTypeIterator Begin();
			StaticTypeIterator End();

			StaticTypeConstIter Begin() const;
			StaticTypeConstIter End() const;

			/** Inserts a StaticTypeElement into the Collection
			***/
			void Insert(StaticTypeElement* element);

			/** The FillDataDictionary function iterates over each StaticTypeDefinition
			 * in the collection.  Each DynamicTypeElement contains a name and a
			 * list of DynamicTypeEntry objects.  For each DynamicTypeEntry, a function
			 * call will be made to add it to the DataDictionary.  The function
			 * call will be DataDictionary::AddDynamic(std::string alias,
			 *    std::string parameter, std::string typeName)
			 * where alias is the name field from DynamicTypeElement,
			 * parameter is the first field inside DynamicTypeEntry, and
			 * typeName is the seconed field inside DynamicTypeEntry.
			 ***/
			void FillDataDictionary();
		private:
	}
}

#endif //STATIC_TYPE_DEFINITION_COLLECTION_H