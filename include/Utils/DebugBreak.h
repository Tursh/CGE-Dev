#include <csignal>

#ifdef __MINGW32__
#define debugBreak() DebugBreak()
#else
#define debugBreak() raise(SIGTRAP)
#endif
