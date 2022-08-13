#include <deque>
#include <memory>
#include <optional>
#include <unordered_map>

#include "module.h"

struct ModuleManager {
  struct Connection {
    Connection(size_t s, size_t sp, size_t d, size_t dp)
        : src(s), src_port(sp), dst(d), dst_port(dp) {}
    size_t src;
    size_t src_port;
    size_t dst;
    size_t dst_port;

    bool operator==(const Connection &other) {
      return std::tie(src, src_port, dst, dst_port) ==
             std::tie(other.src, other.src_port, other.dst, other.dst_port);
    }
  };

  bool addModule(std::shared_ptr<Module>);
  std::optional<Connection> connection_from_global(size_t src_port,
                                                   size_t dst_port);
  bool connect(size_t src_port, size_t dst_port);
  bool connect(size_t src, size_t src_port, size_t dst, size_t dst_port);
  bool disconnect(size_t src_port, size_t dst_port);
  bool disconnect(size_t src, size_t src_port, size_t dst, size_t dst_port);
  bool check_connection(size_t src, size_t src_port, size_t dst,
                        size_t dst_port);

  void deliver_messages();
  void calculate();

  std::unordered_map<size_t, std::shared_ptr<Module>> modules;
  std::deque<Connection> connections;
};