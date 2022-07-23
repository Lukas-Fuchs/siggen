#include "widget.h"
#include "../modules/module.h"

struct ModuleWidget : public Widget {
  
 
 void paint() const override;

 private:
    std::shared_ptr<Module> module;
}