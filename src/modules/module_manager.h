#include <vector>
#include <optional>
#include <memory>
#include <unordered_map>

#include "module.h"

struct ModuleManager
{
    struct Connection
    {
        Connection(size_t s, size_t sp, size_t d, size_t dp) : src(s), src_port(sp), dst(d), dst_port(dp) {}
        size_t src;
        size_t src_port;
        size_t dst;
        size_t dst_port;
    };

    bool addModule(std::shared_ptr<Module>);
    bool connect(size_t src, size_t src_port, size_t dst, size_t dst_port);
    bool check_connection(size_t src, size_t src_port, size_t dst, size_t dst_port);

    void deliver_messages();

    std::unordered_map<size_t, std::shared_ptr<Module>> modules;
    std::vector<Connection> connections;

private:
    size_t next_key;
};