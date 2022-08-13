#pragma once

#include "module.h"

enum class SignalType { Sin, Chirp, Rect };

struct SignalGenerator : public Module {
  SignalGenerator() { outputs.emplace_back(Port("out", 1, 1)); }

  void paint() const override;
  void calculate() override;

private:
  mutable SignalType type = SignalType::Sin;
  mutable float amplitude = 1;

  mutable float sin_frequency = 1; // Frequency in Hertz
  mutable float sin_phase = 0;
};