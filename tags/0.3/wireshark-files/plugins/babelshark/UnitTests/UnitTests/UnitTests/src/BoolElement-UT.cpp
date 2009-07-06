#include <unittest++/unittest++.h>
#include <BoolElement.h>


TEST(BoolInterpreter)
{
	BabelShark::BoolElement UT1("5", "unitTest1");
	char* buffer = new char[10];
	buffer = "zomgtest1!";
	UT1.Interpret(buffer);
	CHECK_EQUAL("unitTest1 : TRUE", UT1.Display());
	char* buffer2 = new char[10];
	for(int counter = 0; counter < 10; counter++){
		buffer2[counter] = 0;
	}
	UT1.Interpret(buffer2);
	CHECK_EQUAL("unitTest1 : FALSE", UT1.Display());

}