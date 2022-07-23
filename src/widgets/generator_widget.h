#include "widget.h"

struct GeneratorWidget : public Widget
{
    /* Lausbub -> */ static const constexpr char *const signal_types[] = {"sin",
                                                                          "chirp",
                                                                          "saw",
                                                                          "square",
                                                                          "function",
                                                                          "file"};
    mutable int current_stype = 0;

    void paint() const override;
};