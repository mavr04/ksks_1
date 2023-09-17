#include "pch.h"
#include "CppUnitTest.h"
#include "../ConsoleApplication1/ConsoleApplication1.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:

		TEST_METHOD(TestMethod1)
		{
			std::string expected = "draw pixel : 20 20 2";

			std::stringstream buffer;
			std::streambuf* sbuf = std::cout.rdbuf();
			std::cout.rdbuf(buffer.rdbuf());

			int result = main();

			std::cout.rdbuf(sbuf);
			std::cout << "std original buffer: \n";
			std::cout << buffer.get();

			// Test
			Assert::AreEqual(expected, buffer.str());
		}
		TEST_METHOD(TestMethod2)
		{
			std::string expected = "draw circle : 100 100 100 2";

			std::stringstream buffer;
			std::streambuf* sbuf = std::cout.rdbuf();
			std::cout.rdbuf(buffer.rdbuf());

			int result = main();

			std::cout.rdbuf(sbuf);
			std::cout << "std original buffer: \n";
			std::cout << buffer.get();

			// Test
			Assert::AreEqual(expected, buffer.str());
		}
	};
}
