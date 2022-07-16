#pragma once

#include "widget.h"

#include <vector>

struct ScopeGrid : public Widget
{
    std::vector<float> ys;
    float x_lower = 0;
    float x_upper = 1;
    float y_lower = 0;
    float y_upper = 1;

    void paint() const;
};