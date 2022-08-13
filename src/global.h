#ifndef GLOBAL_INCLUDED
#define GLOBAL_INCLUDED

#include <chrono>
#include <ratio>

namespace global {

inline std::chrono::time_point<std::chrono::steady_clock> current_time;

/**
 * @brief Get a unique ID for use in ImGui draw calls
 *
 * @return size_t a unique ID
 */
inline size_t getNextID() {
  // While this can technically wrap, it's pretty much guaranteed to not happen
  // for obvious practical reasons
  static size_t id;
  return id++;
}

inline std::chrono::time_point<std::chrono::steady_clock> get_initial_time() {
  static auto initial = std::chrono::steady_clock::now();
  return initial;
}

inline void advance_time() { current_time = std::chrono::steady_clock::now(); }

inline uint64_t get_time() {
  return std::chrono::duration_cast<std::chrono::microseconds>(
             current_time - get_initial_time())
      .count();
}
} // namespace global

#endif