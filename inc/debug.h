#ifndef DBG_H
#define DBN_H

#include <cstdlib>
#include <cstdio>
#include <cerrno>
#include <cstring>

//IF NDEBUG IS DEFINED VOID ALL CALLS TO debug()
#ifdef NDEBUG
#define debug(M, ...)
#else
#define debug(M, ...) fprintf(stderr, "DEBUG %s:%d in %s: " M"\n", __FILE__, __LINE__, __FUNCTION__, ##__VA_ARGS__)
#endif

//If there's an error log it clearly
#define cleanErrno() (errno == 0 ? "None" : strerror(errno))

//Utils to print out errors runtime
#define logErr(M, ...)	fprintf(stderr, "[ERROR] (%s:%d in %s errno: %s) " M"\n", __FILE__, __LINE__, __FUNCTION__, cleanErrno(), ##__VA_ARGS__);
#define logWarn(M, ...)	fprintf(stderr, "[WARN]  (%s:%d in %s errno: %s) " M"\n", __FILE__, __LINE__, __FUNCTION__, cleanErrno(), ##__VA_ARGS__);
#define logInfo(M, ...) fprintf(stderr, "[INFO]  (%s:%d)" M"\n", __FILE__, __LINE__, ##__VA_ARGS__ );

//
#define check(A, M, ...) if(!(A)) {logErr(M, ##__VA_ARGS__); errno = 0; goto error;}
#define sentinel(M, ...) {logErr(M, ##__VA_ARGS__); errno = 0; goto error;}

//Check for NULL pointers
#define checkMem(A)	check((A), "Out of memory.")
//
#define checkDebug(A, M, ...) if (!(A)) {debug(M, ##__VA_ARGS__); errno = 0; goto error;}

#endif