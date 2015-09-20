#include "Printer.h"

std::ostream* ___output = 0;

std::ostream& getOutput()
{
	if(___output == 0)
		___output = &std::cout;
	
    return *___output;
}

std::ostream& setOutput(std::ostream* output)
{
	___output = output;
}