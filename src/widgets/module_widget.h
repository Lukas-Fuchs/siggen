#pragma once

#include <memory>

#include "widget.h"
#include "../modules/module.h"

struct ModuleWidget : public Widget {
  
 ModuleWidget(std::shared_ptr<Module> m) : module(m) {}

 void paint() const override;

 private:
    std::shared_ptr<Module> module;
};