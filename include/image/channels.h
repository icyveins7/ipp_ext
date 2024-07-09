#pragma once

#include "ippi.h"

namespace ippi{

// Define possible types for malloc
enum class channels{
    C1, // 1 channel
    C2, // 2 channels
    C3, // 3 channels
    C4, // 4 channels
    AC4 // 4 channels with alpha at end
};

}
