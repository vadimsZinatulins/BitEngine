#pragma once

#include <SimpleTaskManager/make_task.h>
#include <utility>

namespace be::utils {

template<typename Function_t, typename ...Args_t>
auto runAsync(Function_t function, Args_t ...args) {
	return stm::make_task(function, args...);
}

}
