#pragma once
#include <Core/UUID.h>

namespace LLGP 
{
	class Object
	{
	public:
		Object() : uuid() {}
		Object(const Object&) = default;

		UUID uuid;

		inline bool operator==(const Object& rhs) { return (uint64_t)this->uuid == (uint64_t)rhs.uuid; }
#if !_HAS_CXX20
		inline bool operator!=(const Object& rhs) { return !(*this == rhs); }
#endif
	};
}