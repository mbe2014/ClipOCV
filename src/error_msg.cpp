#include "copyright.h"

//=================================================================
// error_msg handlers.
//
// Description:
//
//=================================================================

#include "stdio.h"
#include "error_msg.h"

namespace clipocv {

void error_msg(const char *s, unsigned long p)
{
    fprintf(stderr,s,p);
}

// int exception may have scope that is too large

void clip_exception(int x)
{
    throw x;
}

} // namespace
