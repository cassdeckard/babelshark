#include <unittest++/unittest++.h>
#include <AsciiElement.h>


TEST(AsciiInterpreter)
{
	BabelShark::AsciiElement UT1(5, "unitTest1");
	char* buffer = new char[10];
	buffer = "zomgtest1!";
	UT1.Interpret(buffer);
	CHECK_EQUAL("unitTest1 : 'zomgt'", UT1.Display());

}