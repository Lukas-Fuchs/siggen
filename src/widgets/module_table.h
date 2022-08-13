#include <deque>
#include <optional>

#include "../modules/module_manager.h"
#include "module_widget.h"
#include "widget.h"

struct ModuleTable : public Widget {
  std::shared_ptr<ModuleManager> manager;
  std::deque<ModuleWidget> modules;

  ModuleTable(std::shared_ptr<ModuleManager> manager, float w = 500,
              float h = 250);
  void paint() const override;
};