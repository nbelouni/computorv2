
#include "../inc/Computorv2.hpp"
#include "../inc/LexerParser.hpp"

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
			lp.parse();
			line.clear();
		}
		catch (std::exception &e)
		{
			std::cerr << e.what() << std::endl;
		}
		std::cout << "$>";
		lp.clear();
    }
/*
    LexerParser lp;

    std::cout << "$>";
    for (std::string line; std::getline(std::cin, line);)
    {
        try
        {
//            std::cout << line << std::endl;
            lp.lineToTokens(line);
//            lp.parse();
            line.clear();
        }
        catch (std::exception &e)
        {
            std::cerr << e.what() << std::endl;
        }
        std::cout << "$>";
        lp.clear();
    }


    Computor cp;

    try
    {
//        cp.testComplex();
//        cp.testRational();
        cp.testMatrix();
    }
    catch (const std::invalid_argument &e)
    {
        std::cerr << "INVALID ARGUMENT: " << e.what() << std::endl;
    }
    catch (const std::logic_error &e)
    {
        std::cerr << "LOGIC ERROR: " << e.what() << std::endl;
    }
*/
    return 0;
}
