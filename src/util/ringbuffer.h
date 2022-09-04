#include <vector>
#include <stddef.h>
#include <iterator>

template <typename T> struct Ringbuffer {
  Ringbuffer(size_t size) { resize(size); }

  size_t size() const { return data_vector.size(); }

  void resize(size_t size) {
    data_vector.resize(size);
    current_idx = 0;
  }

  void put(T x) {
    data_vector[current_idx++] = x;
    current_idx %= data_vector.size();
  }

  void put(std::vector<T> v){
    for(size_t i = current_idx; i < v.size(); ++i){
      data_vector[i % data_vector.size()] = v[i]; 
    }
    current_idx += v.size();
    current_idx %= data_vector.size();
  }

  const T get() const { return data_vector[current_idx]; }
  const T back() const {
    return data_vector[(current_idx - 1) % data_vector.size()];
  }

  const std::vector<T>::iterator begin(){
    return data_vector.begin();
  }

  const T *data() const { return data_vector.data(); }
  const size_t offset() const { return current_idx; }

private:
  std::vector<T> data_vector;
  size_t current_idx;
};