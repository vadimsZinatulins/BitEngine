#ifndef __BE_UTILS_GLOBALS_H__
#define __BE_UTILS_GLOBALS_H__

namespace BE
{
namespace Utils
{

#if defined(_WIN64)
#define CACHE_LINE_SIZE 64
#else
#define CACHE_LINE_SIZE 32
#endif

}
}

#endif // !__BE_UTILS_GLOBALS_H__
