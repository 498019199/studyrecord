#pragma once
#include <common/macro.h>
#include <cassert>

#ifdef _DEBUG
	#define COMMON_ASSERT(val) assert(val)
#else
	#define COMMON_ASSERT(val) 
#endif//_DEBUG