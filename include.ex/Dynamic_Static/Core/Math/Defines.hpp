
/*
==========================================
    Copyright 2011-2018 Dynamic_Static
        Patrick Purcell
    Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#include "Dynamic_Static/Core/Defines.hpp"

#pragma once

#include "Dynamic_Static/Core/Defines.hpp"

#define GLM_FORCE_RADIANS
#define GLM_FORCE_SIZE_T_LENGTH
#define GLM_ENABLE_EXPERIMENTAL
#define GLM_FORCE_DEPTH_ZERO_TO_ONE

#if DYNAMIC_STATIC_MSVC
    #pragma warning(push, 0)
#endif

#include "glm/glm.hpp"
#include "glm/gtc/quaternion.hpp"
#include "glm/gtx/norm.hpp"
#include "glm/gtx/quaternion.hpp"
#include "glm/gtx/string_cast.hpp"
#include "glm/gtx/transform.hpp"

#if DYNAMIC_STATIC_MSVC
    #pragma warning(pop)
#endif

#define _USE_MATH_DEFINES
#include <math.h>
#include <algorithm>
#include <cmath>
#include <ostream>