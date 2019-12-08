
#include "../inc/Computorv2.hpp"

int main(int argc, char *argv[])
{
   // Computor cp;

	LexerParser lp;
	std::cout << "$>";
	for (std::string line; std::getline(std::cin, line);)
	{
		try
		{
//			std::cout << line << std::endl;
			lp.lineToTokens(line);
//			lp.parse();
			line.clear();
		}
		catch (std::exception &e)
		{
			std::cerr << e.what() << std::endl;
		}
		std::cout << "$>";
		lp.clear();
    }
    return 0;
}
