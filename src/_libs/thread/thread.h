#ifndef _LIBS_THREAD_H
#define	_LIBS_THREAD_H

#include "General.h"

#if OS == WIN
	#include <windows.h>
#elif OS == LINUX
	#include <pthread.h>
#endif

typedef void (*thread_method)(void* data);

class Thread
{
public:
	Thread(thread_method fun_ptr, void* data = 0)
		: fun_ptr(fun_ptr),
		data(data)
	{ }
	
	int start(void* data);
	int start();
	
	void* join();
	
private:
	thread_method fun_ptr;
	void* data;
	
	#if OS == WIN
		DWORD thId;
		HANDLE thHandle;
	#elif OS == LINUX
		pthread_t thHandle;
	#endif
};



#endif	/* _LIBS_THREAD_H */

