#pragma once
#include <iostream>
#include <memory>
#include <utility>
#include <algorithm>
#include <functional>

#include <string>
#include <sstream>
#include <vector>
#include <array>
#include <unordered_map>
#include <unordered_set>

#include "core/Core.h"
#include "core/Log.h"
#include "core/debug/Instrumentor.h"

#ifdef CB_PLATFORM_WINDOWS
	#include <Windows.h>
#endif
