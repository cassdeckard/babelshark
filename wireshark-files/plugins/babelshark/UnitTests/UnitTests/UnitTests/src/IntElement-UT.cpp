#include <unittest++/unittest++.h>
#include <IntElement.h>
#include <sstream>

TEST(IntConstruction)
{
	BabelShark::IntElement UT1("15", "test1!!!");
	CHECK_EQUAL("test1!!!", UT1.GetName());
}

TEST(IntBitMaskSetting)
{
	size_t size = 8;
	std::stringstream ss;
	ss << size;
	BabelShark::IntElement UT1(ss.str(), "UtilityTest");
	std::bitset<64> bitMask;
	//setup the bitMask for our test case.
	for(size_t i = 0; i < size; ++i)
	{
		bitMask.set(i, 1);
	}
	//confirm that the 2 bitmasks match each other
	//(the first 5 'bits' are 1, rest are zero.
//	for(size_t i = 0; i < bitMask.size(); ++i)
//	{
//		CHECK_EQUAL(bitMask.at(i), UT1.GetBitMask().at(i));
//	}
}

TEST(IntDeterminingByteSize)
{
	size_t size = 5;
	std::stringstream ss;
	ss << size;
	BabelShark::IntElement UT1(ss.str(), "UtilityTest");
	CHECK_EQUAL(1, UT1.GetSizeInBytes());
}

TEST(IntInterpretingData)
{
	BabelShark::IntElement UT1("8", "InterpretTest1");
	BabelShark::IntElement UT2("9", "InterpretTest2");
	BabelShark::IntElement UT3("16", "InterpretTest3");
	BabelShark::IntElement UT4("32", "InterpretTest4");

	// UT1
	UT1.Interpret("\x7F");
	CHECK_EQUAL("InterpretTest1 : 127", UT1.Display());
	UT1.Interpret("\xFF");
	CHECK_EQUAL("InterpretTest1 : -1", UT1.Display());

	// UT2
	UT2.Interpret("\x7F");
	CHECK_EQUAL("InterpretTest2 : 127", UT2.Display());
	UT2.Interpret("\xFF");
	CHECK_EQUAL("InterpretTest2 : 255", UT2.Display());
	UT2.Interpret("\xFF\x1");
	CHECK_EQUAL("InterpretTest2 : -1", UT2.Display());
	
	// UT3
	UT3.Interpret("\xFF\x7F");
	CHECK_EQUAL("InterpretTest3 : 32767", UT3.Display());
	UT3.Interpret("\xFF\xFF");
	CHECK_EQUAL("InterpretTest3 : -1", UT3.Display());
	UT3.Interpret("\x00\x80");
	CHECK_EQUAL("InterpretTest3 : -32768", UT3.Display());

	// UT4
	UT4.Interpret("\xFF\xFF\xFF\x7F");
	CHECK_EQUAL("InterpretTest4 : 2147483647", UT4.Display());
	UT4.Interpret("\xFF\xFF\xFF\xFF");
	CHECK_EQUAL("InterpretTest4 : -1", UT4.Display());
	UT4.Interpret("\x00\x00\x00\x80");
	CHECK_EQUAL("InterpretTest4 : -2147483648", UT4.Display());
}