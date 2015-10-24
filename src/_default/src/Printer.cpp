#include "Printer.h"
#include "_libs/mutex/mutex.h"

static std::ostream* ___output = 0;
static ::Mutex mutex;

::Mutex& getOutputMutex()
{
	return mutex;
}

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