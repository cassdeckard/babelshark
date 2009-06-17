#include <unittest++/unittest++.h>
#include <UintElement.h>

TEST(UintConstruction)
{
	BabelShark::UintElement UT1(15, "test1!!!");
	CHECK_EQUAL("test1!!!", UT1.GetName());
}

TEST(bitMaskSetting)
{
	size_t size = 8;
	BabelShark::UintElement UT1(size, "UtilityTest");
	std::bitset<64> bitMask;
	//setup the bitMask for our test case.
	for(size_t i = 0; i < size; ++i)
	{
		bitMask.set(i, 1);
	}
	//confirm that the 2 bitmasks match each other
	//(the first 5 'bits' are 1, rest are zero.
	for(size_t i = 0; i < bitMask.size(); ++i)
	{
		CHECK_EQUAL(bitMask.at(i), UT1.GetBitMask().at(i));
	}
}

TEST(DeterminingByteSize)
{
	size_t size = 5;
	BabelShark::UintElement UT1(size, "UtilityTest");
	CHECK_EQUAL(1, UT1.GetSizeInBytes());
}