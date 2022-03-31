#pragma once

#include <sys/types.h>
#include <string>

namespace myfolly {
	namespace detail {
		std::string familyNameStrDefault(sa_family_t family);
		}
}