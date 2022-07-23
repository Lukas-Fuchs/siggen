#include "module_manager.h"

/**
 * @brief Adds a new module
 *
 * @param module The module to be added
 * @return true  Success
 * @return false Failure
 */
bool ModuleManager::addModule(std::shared_ptr<Module> module)
{
    module->id = next_key;
    return modules.insert({next_key++, module}).second;
}

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
bool ModuleManager::connect(size_t src, size_t src_port, size_t dst, size_t dst_port)
{
    if (check_connection(src, src_port, dst, dst_port))
    {
        connections.emplace_back(Connection{src, src_port, dst, dst_port});
        return true;
    }

    return false;
}

/**
 * @brief Checks whether a given connection would be valid in terms of existence of both sides and matching data dimensions
 *
 * @param src      ID of the source module
 * @param src_port Port of the source module
 * @param dst      ID of the destination module
 * @param dst_port Port of the destination module
 * @return true    Connection would be valid
 * @return false   Connection is not possible
 */
bool ModuleManager::check_connection(size_t src, size_t src_port, size_t dst, size_t dst_port)
{
    auto src_it = modules.find(src);
    auto dst_it = modules.find(dst);
    if (src_it != modules.end() && dst_it != modules.end())
    {
        if (src_it->second->outputs.size() < src_port && dst_it->second->inputs.size() < dst_port)
        {
            if (src_it->second->outputs[src_port].getDims() == dst_it->second->inputs[dst_port].getDims())
            {
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
void ModuleManager::deliver_messages(){
    for(auto connection : connections){
        auto src = modules[connection.src];
        auto dst = modules[connection.dst];
        dst->inputs[connection.dst_port].put(src->outputs[connection.src_port].get());
    }
}
