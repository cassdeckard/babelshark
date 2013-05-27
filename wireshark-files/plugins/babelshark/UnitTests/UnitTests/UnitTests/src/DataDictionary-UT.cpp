#include <unittest++/unittest++.h>
#include <InstructionSet.h>
#include <AsciiElement.h>
#include <BoolElement.h>
#include <UintElement.h>
#include <PadElement.h>
#include <DataDictionary.h>
#include <AliasedInstruction.h>
#include <InstructionElement.h>

struct TestDataDictionary
{
	public:
		TestDataDictionary()
		{
			child1 = new BabelShark::AsciiElement("5", "child1");
			child2 = new BabelShark::BoolElement("4", "child2");
			child3 = new BabelShark::UintElement("8", "child3");
			child4 = new BabelShark::PadElement("52", "child4");
		}
		BabelShark::Instruction* child1;
		BabelShark::Instruction* child2;
		BabelShark::Instruction* child3;
		BabelShark::Instruction* child4;
};


TEST_FIXTURE(TestDataDictionary, StaticType)
{
	BabelShark::InstructionSet T1("2", "test1");
	T1.Add(child1);
	T1.Add(child2);
	BabelShark::InstructionSet T2("2", "test2");
	T2.Add(child3);
	T2.Add(child4);
	
	DATA_DICT.AddStatic("&MyStatic1", &T1);
	DATA_DICT.AddStatic("&MyStatic2", &T2);

	BabelShark::InstructionNode* returnValue;
	DATA_DICT.LookupType(&returnValue, "&MyStatic1");
	CHECK_EQUAL(T1.Display(), returnValue->Display());
	BabelShark::Iterator* iter = returnValue->CreateIterator();
	CHECK_EQUAL(child1, (*iter).CurrentItem());
	iter->Next();
	CHECK_EQUAL(child2, (*iter).CurrentItem());

	DATA_DICT.LookupType(&returnValue, "&MyStatic2");
	CHECK_EQUAL(T2.Display(), returnValue->Display());
	iter = returnValue->CreateIterator();
	CHECK_EQUAL(child3, (*iter).CurrentItem());
	iter->Next();
	CHECK_EQUAL(child4, (*iter).CurrentItem());

}

TEST_FIXTURE(TestDataDictionary, DynamicType)
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

	//Create and add a variable
	BabelShark::InstructionElement* myVariable = new BabelShark::UintElement("8", "myVariable", "$MyInt");
	DATA_DICT.AddVariable("$MyInt", myVariable);
	
	//Initialize it to call the attach function
	BabelShark::InstructionNode* returnValue;
	BabelShark::InstructionElement* param = DATA_DICT.LookupVariable("$MyInt");
	DATA_DICT.LookupType(&returnValue, "&DynamicTest", param);

	//update the value so that its pointing to the correct instruction
	myVariable->Interpret("\x1");
	CHECK_EQUAL("myVariable : 1", myVariable->Display());

	CHECK_EQUAL(T1.Display(), returnValue->Display());
	BabelShark::Iterator* iter = returnValue->CreateIterator();
	CHECK_EQUAL(child1, (*iter).CurrentItem());
	iter->Next();
	CHECK_EQUAL(child2, (*iter).CurrentItem());

	//Update value of variable to a differrent value, then verify children have changed
	//The below statement has valid syntax,  but doesn't appear to be triggering the change
	//in children
	myVariable->Interpret("\x2");
	CHECK_EQUAL(T2.Display(), returnValue->Display());
	iter = returnValue->CreateIterator();
	CHECK_EQUAL(child3, (*iter).CurrentItem());
	iter->Next();
	CHECK_EQUAL(child4, (*iter).CurrentItem());
}