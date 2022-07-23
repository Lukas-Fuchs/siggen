#include <vector>
#include <optional>

#include "widget.h"

struct ModuleTable : public Widget
{
    std::vector<std::optional<Widget>> modules;

    ModuleTable(float w = 500, float h = 250);
    void paint() const override;
};