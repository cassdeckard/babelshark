#include <unittest++/unittest++.h>
#include <FloatElement.h>
#include <sstream>

TEST(FloatConstruction)
{
	BabelShark::FloatElement UT1("15", "test1!!!");
	CHECK_EQUAL("test1!!!", UT1.GetName());
}

TEST(FloatDeterminingByteSize)
{
	size_t size = 5;
	std::stringstream ss;
	ss << size;
	BabelShark::FloatElement UT1(ss.str(), "UtilityTest");
	CHECK_EQUAL(4, UT1.GetSizeInBytes());
}

TEST(FloatInterpretingData)
{
	BabelShark::FloatElement UT1("16", "InterpretTest1");
	BabelShark::FloatElement UT2("32", "InterpretTest2");
	BabelShark::FloatElement UT3("64", "InterpretTest3");

	// UT1
	UT1.Interpret("\xC3\xF5\x48\x40");
	CHECK_EQUAL("InterpretTest1 : 3.14", UT1.Display());
	UT1.Interpret("\x49\x2D\xA7\x44");
	CHECK_EQUAL("InterpretTest1 : 1337.42", UT1.Display());

	// UT2
	UT2.Interpret("\xC3\xF5\x48\x40");
	CHECK_EQUAL("InterpretTest2 : 3.14", UT2.Display());
	UT2.Interpret("\x49\x2D\xA7\x44");
	CHECK_EQUAL("InterpretTest2 : 1337.42", UT2.Display());

	// UT3
	UT3.Interpret("\x18\x2D\x44\x54\xFB\x21\x09\x40");
	CHECK_EQUAL("InterpretTest3 : 3.14159", UT3.Display());
	UT3.Interpret("\xAF\x25\x51\x20\xA9\xE5\x94\x40");
	CHECK_EQUAL("InterpretTest3 : 1337.42", UT3.Display());

}