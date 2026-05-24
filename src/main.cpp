#include <fstream>
#include <iostream>

#include "../headers/game.hpp"
#include "../headers/exceptions.hpp"

auto main() -> int
{
	try
	{
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