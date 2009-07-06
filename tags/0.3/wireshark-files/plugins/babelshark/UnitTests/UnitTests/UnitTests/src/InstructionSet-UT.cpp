#include <unittest++/unittest++.h>
#include <InstructionSet.h>


struct InstructionChildren
{
	public:
		InstructionChildren()
		{
			child1 = new BabelShark::Instruction("5", "child1");
			child2 = new BabelShark::Instruction("4", "child2");
			child3 = new BabelShark::Instruction("3", "child3");
			child4 = new BabelShark::Instruction("52", "child4");
		}
		BabelShark::Instruction* child1;
		BabelShark::Instruction* child2;
		BabelShark::Instruction* child3;
		BabelShark::Instruction* child4;
};


TEST(InstructionSetInitializer)
{
	BabelShark::InstructionSet T1("2", "InstructionSetTest");
	CHECK_EQUAL("InstructionSetTest", T1.GetName());
	CHECK_EQUAL(2, T1.GetSize());
}

TEST_FIXTURE(InstructionChildren, AddingChildren)
{
	BabelShark::InstructionSet T1("2", "test1");
	T1.Add(child1);
	T1.Add(child2);
	T1.Add(child3);
	T1.Add(child4);
	BabelShark::Iterator* iter = T1.CreateIterator();
	 //iter = T1.GetIterator();
	//confirm that the pointer to each child stored into the InstructionSet
	//is the same one we access through the iterator
	CHECK_EQUAL(child1, (*iter).CurrentItem());
	iter->Next();
	CHECK_EQUAL(child2, (*iter).CurrentItem());
	iter->Next();
	CHECK_EQUAL(child3, (*iter).CurrentItem());
	iter->Next();
	CHECK_EQUAL(child4, (*iter).CurrentItem());
}