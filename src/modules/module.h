#ifndef MODULE_INCLUDED
#define MODULE_INCLUDED

#include <Eigen/Dense>
#include <string>

#include "global.h"
#include "imgui.h"

#include <iostream>

struct Port {
  void put(Eigen::MatrixXcd input) { state = input; }
  Eigen::MatrixXcd get() { return state; }

  std::tuple<size_t, size_t> getDims() { return {state.rows(), state.cols()}; }

  Port(std::string name, size_t rows, size_t cols) {
    id = global::getNextID();
    this->name = name;
    state = Eigen::MatrixXcd(rows, cols);
  }

  size_t id;
  std::string name;

  size_t connection_count = 0;
  mutable bool visible = true;

private:
  Eigen::MatrixXcd state;
};

struct Module {
  enum class Type { Generator, FFT, Unknown };

  Type type;
  size_t id;

  std::vector<Port> inputs;
  std::vector<Port> outputs;
  ImVec2 preferred_dims{150.0f, 100.0f};

  Module() { id = global::getNextID(); }

  virtual void calculate(){};
  virtual void paint() const {};
};

#endif