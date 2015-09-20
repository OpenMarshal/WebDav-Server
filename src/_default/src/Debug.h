#ifndef _DEFAULT_DEBUG_H
#define	_DEFAULT_DEBUG_H


/*****************************
 * Debug
 * This is managed by the
 * makefile.
 *****************************/
#ifdef DEBUG
	#define DEBUG 1
#endif

#if DEBUG
    #define debug(format, args...) { printf(format, ##args); fflush(stdout); }
#else
    #define debug(format, args...) ;
#endif

#endif	/* _DEFAULT_DEBUG_H */

