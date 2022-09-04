#include <stddef.h>
#include <span>
#include <imgui.h>

namespace ImGui{
    struct GraphSettings {
        size_t offset = 0;
        
        float min_x = 0;
        float max_x = 1;
        float min_y = 0;
        float max_y = 1;

        ImVec2 dimensions;
    };

    void Graph(GraphSettings& settings, const std::span<float>& ys);
}