#ifndef STATIC_TYPE_DEFINITION_COLLECTION_H
#define STATIC_TYPE_DEFINITION_COLLECTION_H


namespace PDI
{
	class StaticTypeCollection : public Singleton<StaticTypeCollection>
	{
		public:
			typedef std::list<StaticTypeElement> StaticTypeDefinitionCollection;
			typedef StaticTypeDefinitionCollection::iterator StaticTypeIterator;
			typedef StaticTypeDefinitionCollection::const_iterator StaticTypeConstIter;

			StaticTypeIterator Begin();
			StaticTypeIterator End();

			StaticTypeConstIter Begin() const;
			StaticTypeConstIter End() const;

			void Insert(StaticTypeElement* element);
		private:
	}
}

#endif //STATIC_TYPE_DEFINITION_COLLECTION_H