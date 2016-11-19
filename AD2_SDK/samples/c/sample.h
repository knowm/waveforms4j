#include <stdio.h>
#include <stdlib.h>

#ifdef WIN32
#include "../../inc/dwf.h"
#else
#include "../../inc/dwf.h"
#endif

#ifdef WIN32
    #include <windows.h>
    #define Wait(ts) Sleep((int)(1000*ts))
#else
    #include <unistd.h>
    #include <sys/time.h>
    #define Wait(ts) usleep((int)(1000000*ts))
#endif
