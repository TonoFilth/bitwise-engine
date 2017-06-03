#pragma once

#include "bitwise/core/export.h"

namespace bw
{

struct BW_API Vector2
{
    float x;
    float y;

    Vector2 unit();
};

}   // namespace bw