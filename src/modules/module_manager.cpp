#include "module_manager.h"

#include "global.h"

using Connection = ModuleManager::Connection;

/**
 * @brief Adds a new module
 *
 * @param module The module to be added
 * @return true  Success
 * @return false Failure
 */
bool ModuleManager::addModule(std::shared_ptr<Module> module) {
  module->id = global::getNextID();
  return modules.insert({module->id, module}).second;
}

/**
 * @brief Finds a valid connection object for two global port IDs
 *
 * @param src_port source port
 * @param dst_port destination port
 * @return std::optional<ModuleManager::Connection> A connection between the two
 * ports if they both exist
 */
std::optional<Connection>
ModuleManager::connection_from_global(size_t src_port, size_t dst_port) {
  bool src_found = false;
  bool dst_found = false;
  size_t s, d, sp, dp;

  // Iterate through all modules until the right ports are found and translate
  // the global IDs to module-port tuples
  for (auto it = modules.begin();
       !(src_found && dst_found) && it != modules.end(); ++it) {
    if (!it->second)
      continue;

    // Search for input and output ports with these global IDs
    if (!src_found) {
      const auto &out = it->second->outputs;
      for (size_t i = 0; i < out.size(); ++i) {
        if (out[i].id == src_port) {
          s = it->first;
          sp = i;
          src_found = true;
          break;
        }
      }
    }

    if (!dst_found) {
      const auto &in = it->second->inputs;
      for (size_t i = 0; i < in.size(); ++i) {
        if (in[i].id == dst_port) {
          d = it->first;
          dp = i;
          dst_found = true;
          break;
        }
      }
    }
  }

  if (src_found && dst_found) {
    return ModuleManager::Connection(s, sp, d, dp);
  }
  return std::nullopt;
}

/**
 * @brief Connects two ports by their global IDs.
 *
 * @param src_port Source port
 * @param dst_port Destination port
 * @return true Success
 * @return false Failure
 */
bool ModuleManager::connect(size_t src_port, size_t dst_port) {
  const auto maybe_connection = connection_from_global(src_port, dst_port);
  if (maybe_connection.has_value()) {
    const auto conn = *maybe_connection;
    connect(conn.src, conn.src_port, conn.dst, conn.dst_port);
  }
  return maybe_connection.has_value();
};

/**
 * @brief Adds a new connection between two modules
 *
 * @param src      ID of the source module
 * @param src_port Port of the source module
 * @param dst      ID of the destination module
 * @param dst_port Port of the destination module
 * @return true    Success
 * @return false   Failure
 */
bool ModuleManager::connect(size_t src, size_t src_port, size_t dst,
                            size_t dst_port) {
  if (check_connection(src, src_port, dst, dst_port)) {
    modules[src]->outputs[src_port].connection_count++;
    modules[dst]->inputs[dst_port].connection_count++;
    connections.emplace_back(Connection{src, src_port, dst, dst_port});
    return true;
  }

  return false;
}

/**
 * @brief Disconnects two connected ports using global port IDs
 *
 * @param src_port source port
 * @param dst_port destination port
 * @return true connection was dissolved
 * @return false connection didn't exist or couldn't be dissolved
 */
bool ModuleManager::disconnect(size_t src_port, size_t dst_port) {
  auto maybe_connection = connection_from_global(src_port, dst_port);
  if (!maybe_connection)
    return false;
  auto conn = *maybe_connection;
  for (auto it = connections.begin(); it != connections.end(); ++it) {

    if (*it == conn) {
      connections.erase(it);
      return true;
    }
  }
  return false;
}

/**
 * @brief Disconnects two connected ports using their module IDs and port
 * indices
 *
 * @param src source module
 * @param src_port source port
 * @param dst destination module
 * @param dst_port destination port
 * @return true connection was dissolved
 * @return false connection didn't exist or couldn't be dissolved
 */
bool ModuleManager::disconnect(size_t src, size_t src_port, size_t dst,
                               size_t dst_port) {
  Connection conn(src, src_port, dst, dst_port);
  for (auto it = connections.begin(); it != connections.end(); ++it) {
    if (*it == conn) {
      modules[src]->outputs[src_port].connection_count++;
      modules[dst]->inputs[dst_port].connection_count++;
      connections.erase(it);
      return true;
    }
  }
  return false;
}

/**
 * @brief Checks whether a given connection would be valid in terms of existence
 * of both sides and matching data dimensions
 *
 * @param src      ID of the source module
 * @param src_port Port of the source module
 * @param dst      ID of the destination module
 * @param dst_port Port of the destination module
 * @return true    Connection would be valid
 * @return false   Connection is not possible
 */
bool ModuleManager::check_connection(size_t src, size_t src_port, size_t dst,
                                     size_t dst_port) {

  auto src_it = modules.find(src);
  auto dst_it = modules.find(dst);
  if (src_it != modules.end() && dst_it != modules.end()) {

    if (src_port < src_it->second->outputs.size() &&
        dst_port < dst_it->second->inputs.size()) {

      if (src_it->second->outputs[src_port].getDims() ==
          dst_it->second->inputs[dst_port].getDims()) {

        return true;
      }
    }
  }
  return false;
}

/**
 * @brief Passes data from all output ports to input ports connected to them
 *
 */
void ModuleManager::deliver_messages() {
  for (auto connection : connections) {
    auto src = modules[connection.src];
    auto dst = modules[connection.dst];

    /* std::cout << "(" << connection.src << ", " << connection.src_port << ")
       -- "
               << src->outputs[connection.src_port].get() << " -> ("
               << connection.dst << ", " << connection.dst_port << ")"
               << std::endl;*/

    dst->inputs[connection.dst_port].put(
        src->outputs[connection.src_port].get());
  }
}

void ModuleManager::calculate() {
  for (auto &m : modules) {
    if (m.second) {
      m.second->calculate();
    }
  }
}
