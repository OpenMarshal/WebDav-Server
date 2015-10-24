#include "mutex.h"

Mutex::Mutex(const char* name)
{
	#if OS == WIN
		hd = ::CreateMutex( 
		0, 			// default security attributes
		0, 			// initially not owned
		name); 		// unnamed mutex
	#elif OS == LINUX
		::pthread_mutex_init(&lock, 0);
	#endif
}

Mutex::~Mutex()
{
	#if OS == WIN
		::CloseHandle(hd);
	#elif OS == LINUX
		::pthread_mutex_destroy(&lock);
	#endif
}

void Mutex::lock()
{
	#if OS == WIN
		::WaitForSingleObject(hd, INFINITE);
	#elif OS == LINUX
		::pthread_mutex_lock(&lock);
	#endif
}

void Mutex::unlock()
{
	#if OS == WIN
		::ReleaseMutex(hd);
	#elif OS == LINUX
		::pthread_mutex_unlock(lock);
	#endif
}