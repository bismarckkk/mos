//
// Created by bismarck on 10/14/22.
//

#include "core.h"
#include "node.h"

namespace mos {
    bool core::newNode(const boost::filesystem::path& libPath, const std::string& name) {
        boost::dll::shared_library lib(libPath);
        auto& nh = lib.get<internal::node& (void)>("getInstance")();
        nh.setCore(this);
        lib.get<void (const std::string&)>("init")(name);
        std::string _name = nh.getName();
        std::thread th(lib.get<void (void)>("start"));
        internal::nodeHost that {
            std::move(lib),
            now_nid++,
            std::move(th)
        };
        nodeHostsMtx.lock();
        auto res = nodeHosts.emplace(_name, std::move(that));
        nodeHostsMtx.unlock();
        return res.second;
    }

    bool core::deleteNode(const std::string& name) {
        nodeHostsMtx.lock();

        nodeHostsMtx.unlock();
    }
}