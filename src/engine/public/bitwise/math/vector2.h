#pragma once

#include "bitwise/core/macros.h"

namespace bw
{

struct BW_API Vector2
{
    float x;
    float y;

    Vector2 unit();
};

}   // namespace bw