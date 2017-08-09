#define CATCH_CONFIG_MAIN
#define DO_NOT_USE_WMAIN
#include <Catch.hpp>

#include "CommandLineParser.h"

TEST_CASE("Correct Input", "[core::CommandLineParser]")
{
	char* argv[] = { "path/to/executable.exe", "arg1", "arg2", 
							"--key1=value1", "-opt1", "--key2=value2", 
							"-opt2"};
	char argc = 7;

	freed::core::CommandLineParser cmdLineParser;
	bool initSucceeded = cmdLineParser.Initialize(argc, argv);
	REQUIRE(initSucceeded);
	REQUIRE(strcmp(cmdLineParser.GetExecutablePath(), "path/to/executable.exe")==0);

	SECTION("arguments are parsed and stored")
	{
		REQUIRE(cmdLineParser.NumArguments() == 2);

		REQUIRE(cmdLineParser.HasArgument("arg1"));
		REQUIRE(cmdLineParser.HasArgument("arg2"));

		REQUIRE(!cmdLineParser.HasArgument("opt1"));
		REQUIRE(!cmdLineParser.HasArgument("opt2"));
	}

	SECTION("options are parsed and stored")
	{
		REQUIRE(cmdLineParser.NumOptions() == 2);

		REQUIRE(cmdLineParser.HasOption("opt1"));
		REQUIRE(cmdLineParser.HasOption("opt2"));
		
		REQUIRE(!cmdLineParser.HasOption("arg1"));
		REQUIRE(!cmdLineParser.HasOption("arg2"));
	}

	SECTION("key-value-pairs are parsed and stored")
	{
		REQUIRE(cmdLineParser.NumKeyValuePairs() == 2);

		REQUIRE(cmdLineParser.GetValueForKey("key1") != nullptr);
		REQUIRE(cmdLineParser.GetValueForKey("key2") != nullptr);

		REQUIRE(strcmp(cmdLineParser.GetValueForKey("key1"), "value1") == 0);
		REQUIRE(strcmp(cmdLineParser.GetValueForKey("key2"), "value2") == 0);
	}
}

TEST_CASE("Invalid Arguments - 'argc' is 0", "[core::CommandLineParser]")
{
	char* argv[] = { "path/to/executable.exe", "arg1", "arg2",
		"--key1=value1", "-opt1", "--key2=value2",
		"-opt2" };
	char argc = 0;

	freed::core::CommandLineParser cmdLineParser;
	bool initSucceeded = cmdLineParser.Initialize(argc, argv);
	REQUIRE(!initSucceeded);
	
	REQUIRE(cmdLineParser.NumArguments() == 0);
	REQUIRE(cmdLineParser.NumOptions() == 0);
	REQUIRE(cmdLineParser.NumKeyValuePairs() == 0);
}

TEST_CASE("Invalid Arguments - 'argv' is 0 and 'argc' > 0", "[core::CommandLineParser]")
{
	char** argv = nullptr;
	char argc = 4;

	freed::core::CommandLineParser cmdLineParser;
	bool initSucceeded = cmdLineParser.Initialize(argc, argv);
	REQUIRE(!initSucceeded);

	REQUIRE(cmdLineParser.NumArguments() == 0);
	REQUIRE(cmdLineParser.NumOptions() == 0);
	REQUIRE(cmdLineParser.NumKeyValuePairs() == 0);
}

TEST_CASE("Invalid Arguments - entry in 'argv' is 0, 'argc' > 0", "[core::CommandLineParser]")
{
	char* argv[] = { "path/to/executable.exe", "arg1", "arg2",
					 nullptr, "-opt1", "--key2=value2",
					 "-opt2" };
	char argc = 7;

	freed::core::CommandLineParser cmdLineParser;
	bool initSucceeded = cmdLineParser.Initialize(argc, argv);
	REQUIRE(!initSucceeded);

	REQUIRE(cmdLineParser.NumArguments() == 0);
	REQUIRE(cmdLineParser.NumOptions() == 0);
	REQUIRE(cmdLineParser.NumKeyValuePairs() == 0);
}