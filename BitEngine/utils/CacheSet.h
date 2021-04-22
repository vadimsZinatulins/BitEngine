#ifndef __BE_UTILS_CACHE_SET_H__
#define __BE_UTILS_CACHE_SET_H__

#include "Globals.h"

#include <cstddef>
#include <iostream>

namespace BE
{
namespace Utils
{

enum class CacheUtilization
{
	Full = 1,
	Half = 2,
	Quarter = 4
};

template<typename T, CacheUtilization CU = CacheUtilization::Full>
class CacheSet
{
public:
	static constexpr std::size_t SetSize{ (CACHE_LINE_SIZE / static_cast<int>(CU) - sizeof(std::size_t)) / sizeof(T) };

	CacheSet()
	{
		std::cout << SetSize << std::endl;
	};

	~CacheSet() = default;

private:
	T m_array[SetSize];
	std::size_t m_numElements;
};

}
}

#endif // !__BE_UTILS_CACHE_SET_H__
