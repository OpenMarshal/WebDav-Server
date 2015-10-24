#ifndef _DEFAULT_PRINTER_H
#define	_DEFAULT_PRINTER_H

#include "_libs/mutex/mutex.h"
#include <iostream>

Mutex& getOutputMutex();
std::ostream& getOutput();
std::ostream& setOutput(std::ostream* output);

#endif	/* _DEFAULT_PRINTER_H */

