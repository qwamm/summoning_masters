#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include <cstdlib>
#include "/home/fdfdas/oop2023/2/src/include/dynamic_class.h"

TEST_CASE ("Constructors of complex class")
{
	using namespace dynamic_class;
	SECTION("Default constructor")
	{
		Dices d;
		REQUIRE(d.get_size() == 0);
	}
}
