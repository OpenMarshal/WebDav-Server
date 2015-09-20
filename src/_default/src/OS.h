#ifndef _DEFAULT_OS_H
#define	_DEFAULT_OS_H


/*****************************
 * Constants
 * /!\ DO NOT TOUCH
 *****************************/
#define WIN 1
#define LINUX 2



/*****************************
 * Select the OS :
 *    WIN
 *    LINUX
 * This is managed by the
 * makefile.
 *****************************/

// Windows
#if defined(__WIN32__)
    #define OS WIN
#elif defined(_WIN32)
    #define OS WIN
#elif defined(__CYGWIN__)
    #define OS WIN
#elif defined(__CYGWIN32__)
    #define OS WIN
#elif defined(__BORLANDC__)
    #define OS WIN
#elif defined(__MINGW32__)
    #define OS WIN
#elif defined(WIN32)
    #define OS WIN
#elif defined(windows)
    #define OS WIN
#endif

// Linux
#if defined(linux)
    #define OS LINUX
#elif defined(__linux__)
    #define OS LINUX
#endif

// Other
#ifndef OS
    #error OS or compiler not supported.
#endif


#endif	/* _DEFAULT_OS_H */

