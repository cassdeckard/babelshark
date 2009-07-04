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
			child1 = new BabelShark::AsciiElement(5, "child1");
			child2 = new BabelShark::BoolElement(4, "child2");
			child3 = new BabelShark::UintElement(8, "child3", "$MyInt");
			child4 = new BabelShark::PadElement(52, "child4");
		}
		BabelShark::Instruction* child1;
		BabelShark::Instruction* child2;
		BabelShark::Instruction* child3;
		BabelShark::Instruction* child4;
};


TEST(AliasedInstructionInitializer)
{
	BabelShark::InstructionSet T1(2, "InstructionSetTest");
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
	
	BabelShark::DataDictionary::Instance()->AddStatic("&MyStatic", &T1);

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
	BabelShark::InstructionSet T1(2, "test1");
	T1.Add(child1);
	T1.Add(child2);
	BabelShark::InstructionSet T2(2, "test2");
	T2.Add(child3);
	T2.Add(child4);
	
	//Add them
	BabelShark::DataDictionary::Instance()->AddStatic("&MyStatic1", &T1);
	BabelShark::DataDictionary::Instance()->AddStatic("&MyStatic2", &T2);

	//Add them as children of dynamic
	BabelShark::DataDictionary::Instance()->AddDynamic("&DynamicTest", "1", "&MyStatic1");
	BabelShark::DataDictionary::Instance()->AddDynamic("&DynamicTest", "2", "&MyStatic2");

	//Create aliased instruction
	BabelShark::AliasedInstruction TestAlias("1", "Body", "&DynamicTest", "$MyInt");

	//Update value of variable, then verify children
	child3->Interpret("1");
	BabelShark::Iterator* iter = T1.CreateIterator();
	CHECK_EQUAL(child1, (*iter).CurrentItem());
	iter->Next();
	CHECK_EQUAL(child2, (*iter).CurrentItem());

	//Update value of variable to a differrent value, then verify children have changed
	//The below statement has valid syntax,  but doesn't appear to be triggering the change
	//in children
	//TODO  fix this
	child3->Interpret("2");
	iter = T1.CreateIterator();
	CHECK_EQUAL(child3, (*iter).CurrentItem());
	iter->Next();
	CHECK_EQUAL(child4, (*iter).CurrentItem());
}