#ifndef _LIBS_MUTEX_H
#define	_LIBS_MUTEX_H

#include "src/OS.h"

#if OS == WIN
	#include <windows.h>
#elif OS == LINUX
	#include <pthread.h>
#endif

class Mutex
{
public:
	Mutex()
		: Mutex(0)
	{ }
	Mutex(const char* name);
	~Mutex();
	
	void lock();
	void unlock();
	
private:
	#if OS == WIN
		HANDLE hd;
	#elif OS == LINUX
		pthread_mutex_t lock;
	#endif
};



#endif	/* _LIBS_MUTEX_H */

