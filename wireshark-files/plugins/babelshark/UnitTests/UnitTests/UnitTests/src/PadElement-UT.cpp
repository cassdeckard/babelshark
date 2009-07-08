#include <unittest++/unittest++.h>
#include <PadElement.h>
#include <sstream>

TEST(PadConstruction)
{
	BabelShark::PadElement UT1("15", "test1!!!");
	CHECK_EQUAL("test1!!!", UT1.GetName());
}

TEST(PadInterpretingData)
{
	BabelShark::PadElement UT1("8", "InterpretTest1");
	BabelShark::PadElement UT2("52", "InterpretTest2");
	char* buffer = new char[200];
	buffer = "12345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890";
	UT1.Interpret(buffer);
	CHECK_EQUAL("InterpretTest1 : (8 bits of padding)", UT1.Display());

	// UT2
	UT2.Interpret(buffer);
	CHECK_EQUAL("InterpretTest2 : (52 bits of padding)", UT2.Display());
}
