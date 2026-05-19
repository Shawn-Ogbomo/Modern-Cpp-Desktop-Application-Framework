#include <iostream>
#include <fstream>
#include "../headers/exceptions.hpp"
#include "../headers/game.hpp"

auto main() -> int
{
	try
	{
		//splash screen then switch case with game...
		game();
	}

	catch (const std::invalid_argument& e)
	{
		std::cerr << e.what() << "\n";
		return 1;
	}

	catch (const Terminate& e)
	{
		std::cerr << e.what() << "\n";
		return 2;
	}

	catch (const std::out_of_range& e)
	{
		std::cerr << e.what() << "\n";
		return 3;
	}
}