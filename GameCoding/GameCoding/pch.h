#pragma once

#include "Types.h"
#include "Enums.h"
#include "Defines.h"
#include <windows.h>
#include <vector>
#include <list>
#include <map>
#include <unordered_map>
#include <string>
#include <algorithm>
#include <set>
#include <unordered_set>
#include <functional>
#include <assert.h>

#include "Utils.h"
#include "Values.h"

using namespace std;

// C++20
#include <format>
#include <filesystem>

namespace fs = std::filesystem;

#define _CRTDEBG_MAP_ALLOC
#include <cstdlib>
#include <crtdbg.h>

#ifdef _DEBUG
#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)
#endif

#pragma comment(lib, "msimg32.lib")

// »ç¿îµå
#include <mmsystem.h>
#include <dsound.h>
#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "dsound.lib")