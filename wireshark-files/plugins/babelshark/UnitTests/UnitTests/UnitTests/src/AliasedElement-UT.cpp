#include <unittest++/unittest++.h>
#include <InstructionSet.h>
#include <AsciiElement.h>
#include <BoolElement.h>
#include <UintElement.h>
#include <PadElement.h>
#include <DataDictionary.h>
#include <AliasedInstruction.h>


struct AliasedInstruction
{
	public:
		AliasedInstruction()
		{
			child1 = new BabelShark::AsciiElement("5", "child1");
			child2 = new BabelShark::BoolElement("4", "child2");
			child3 = new BabelShark::UintElement("8", "child3", "$MyInt");
			child4 = new BabelShark::PadElement("52", "child4");
		}
		BabelShark::Instruction* child1;
		BabelShark::Instruction* child2;
		BabelShark::Instruction* child3;
		BabelShark::Instruction* child4;
};


TEST(AliasedInstructionInitializer)
{
	BabelShark::InstructionSet T1("2", "InstructionSetTest");
	CHECK_EQUAL("InstructionSetTest", T1.GetName());
	CHECK_EQUAL(2, T1.GetSize());
}

TEST_FIXTURE(AliasedInstruction, StaticDefinition)
{
	BabelShark::InstructionSet T1("2", "test1");
	T1.Add(child1);
	T1.Add(child2);
	T1.Add(child3);
	T1.Add(child4);
	
	DATA_DICT.AddStatic("&MyStatic", &T1);

	BabelShark::AliasedInstruction TestAlias("1", "Body", "&MyStatic");
	BabelShark::Iterator* iter = T1.CreateIterator();
	CHECK_EQUAL(child1, (*iter).CurrentItem());
	iter->Next();
	CHECK_EQUAL(child2, (*iter).CurrentItem());
	iter->Next();
	CHECK_EQUAL(child3, (*iter).CurrentItem());
	iter->Next();
	CHECK_EQUAL(child4, (*iter).CurrentItem());
}

TEST_FIXTURE(AliasedInstruction, DynamicDefinition)
{
	//Create two static definitions
	BabelShark::InstructionSet T1("2", "test1");
	T1.Add(child1);
	T1.Add(child2);
	BabelShark::InstructionSet T2("2", "test2");
	T2.Add(child3);
	T2.Add(child4);
	
	//Add them
	DATA_DICT.AddStatic("&MyStatic1", &T1);
	DATA_DICT.AddStatic("&MyStatic2", &T2);

	//Add them as children of dynamic
	DATA_DICT.AddDynamic("&DynamicTest", "1", "&MyStatic1");
	DATA_DICT.AddDynamic("&DynamicTest", "2", "&MyStatic2");

	//Create aliased instruction
	BabelShark::AliasedInstruction TestAlias("1", "Body", "&DynamicTest", "$MyInt");

	DATA_DICT.Initialize();

	//Update value of variable, then verify children
	child3->Interpret("\x1");
	CHECK_EQUAL("Body : test1", TestAlias.Display());
	CHECK_EQUAL("child3 : 1", child3->Display());
	BabelShark::Iterator* iter = TestAlias.CreateIterator();
	CHECK_EQUAL(child1, (*iter).CurrentItem());
	iter->Next();
	CHECK_EQUAL(child2, (*iter).CurrentItem());

	//Update value of variable to a differrent value, then verify children have changed
	//The below statement has valid syntax,  but doesn't appear to be triggering the change
	//in children
	child3->Interpret("\x2");
	CHECK_EQUAL("child3 : 2", child3->Display());
	CHECK_EQUAL("Body : test2", TestAlias.Display());
	iter = TestAlias.CreateIterator();
	CHECK_EQUAL(child3, (*iter).CurrentItem());
	iter->Next();
	CHECK_EQUAL(child4, (*iter).CurrentItem());
}