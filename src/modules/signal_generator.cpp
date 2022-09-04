#include "signal_generator.h"

#include "global.h"
#include "imgui.h"
#include <cmath>
#include <chrono>

void SignalGenerator::paint() const {
  switch (type) {
  case SignalType::Sin:
    ImGui::InputFloat("amplitude", &amplitude);
    ImGui::InputFloat("frequency", &sin_frequency);
    ImGui::InputFloat("phase", &sin_phase);
    break;
  case SignalType::Chirp:
    break;
  case SignalType::Rect:
    break;
  }
}

void SignalGenerator::calculate() {
    static double prev_t = global::get_time() / 1000'000'000;

    double t = double(global::get_time()) / 1'000'000;
    size_t n_frames = (t - prev_t) * global::fps;

    std::vector<complex> samples(n_frames);
    for(size_t i = 0; i < n_frames; ++i){
      prev_t += global::fps / 1'000'000;
      samples[i] = {amplitude * std::sin(sin_frequency * (prev_t + sin_phase) * M_PI_2), 0.0f};
    }

    outputs[0].put(samples);
}