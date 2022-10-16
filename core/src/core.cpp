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
        auto it = nodeHosts.find(name);
        if (it != nodeHosts.end()) {
            auto& nh = it->second.lib.get<internal::node& (void)>("getInstance")();
            nh.stop(it->second.th);
            nodeHosts.erase(it);
            nodeHostsMtx.unlock();
            return true;
        } else {
            nodeHostsMtx.unlock();
            return false;
        }
    }

    bool core::deleteNode(int nid) {
        nodeHostsMtx.lock();
        auto it = nodeHosts.begin();
        for (; it != nodeHosts.end(); it++) {
            if (it->second.nid == nid) {
                break;
            }
        }
        if (it != nodeHosts.end()) {
            auto& nh = it->second.lib.get<internal::node& (void)>("getInstance")();
            nh.stop(it->second.th);
            nodeHosts.erase(it);
            nodeHostsMtx.unlock();
            return true;
        } else {
            nodeHostsMtx.unlock();
            return false;
        }
    }

    std::vector<std::string> core::getNodeList() {
        std::vector<std::string> res;
        nodeHostsMtx.lock();
        for (const auto& it :nodeHosts) {
            res.push_back(it.first);
        }
        nodeHostsMtx.unlock();
        return std::move(res);
    }

    template<typename T, bool overwrite, ring_mode ring>
    int core::topicName2tid(const std::string &topicName) {
        int res;
        tidsMtx.lock();
        auto it = tids.find(topicName);
        if (it != tids.end()) {
            res = it->second;
            tidsMtx.unlock();
            return res;
        }
        int tid = now_tid++;
        tidsMtx.unlock();
        std::shared_ptr<internal::topic_sub<T, overwrite, ring>> ptr(new internal::topic_sub<T, overwrite, ring>);
        pubsMtx.lock();
        pubs.emplace(tid, ptr);
        pubsMtx.unlock();
        return tid;
    }

    template<typename T, bool overwrite, ring_mode ring>
    std::shared_ptr<internal::topic_sub<T, overwrite, ring>>
    core::newPub(int nid, const std::string &topicName) {
        int tid = topicName2tid<T, overwrite, ring>(topicName);
        pubsMtx.lock();
        auto ptr = boost::any_cast<std::shared_ptr<internal::topic_sub<T, overwrite, ring>>>(pubs[tid]);
        pubsMtx.unlock();
        ptr->mtx.lock();
        if (ptr->pub_nid != -1) {
            ptr->mtx.unlock();
            return std::shared_ptr<internal::topic_sub<T, overwrite, ring>>();
        }
        ptr->pub_nid = nid;
        ptr->mtx.unlock();
        return ptr;
    }
}