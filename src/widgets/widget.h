
struct Widget
{
    std::string title = "";
    bool show;
    float x, y, w, h;

    virtual void paint() const;
};