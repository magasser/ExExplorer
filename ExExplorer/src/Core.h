#pragma once

#include "Log.h"

#ifdef EE_DEBUG
#define EE_ASSERT(condition, ...) { if (!(condition)) { EE_LOG_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#endif
