//
// Created by bismarck on 10/14/22.
//

#ifndef MOS_TEST_CORE_H
#define MOS_TEST_CORE_H

#include <atomic>
#include <map>
#include <vector>
#include <string>

#include <boost/any.hpp>
#include <boost/filesystem.hpp>
#include <boost/shared_ptr.hpp>

#include "nodeHost.h"
#include "topic_subs.h"

namespace mos {
    class core {
    private:
        std::atomic<int> now_nid{0};

        std::map<std::string, internal::nodeHost> nodeHosts;
        std::map<std::string, int> tids;
        std::map<int, std::shared_ptr<internal::topic_sub>> pubs;

        std::mutex nodeHostsMtx;
        std::mutex tidsMtx;
        std::mutex pubsMtx;

    public:
        bool newNode(const boost::filesystem::path& libPath, const std::string& name="");
        bool deleteNode(const std::string& name);
        bool deleteNode(int nid);
        std::vector<std::string>& getNodeList();

        std::shared_ptr<internal::topic_sub>& newPub(int nid, std::string topicName);
        bool deletePub(int nid, std::string topicName);
        bool deletePub(int nid, int tid);

        std::shared_ptr<boost::any>& newSub(int nid, std::string topicName);
        bool deleteSub(int nid, std::string topicName);
        bool deleteSub(int nid, int tid);
    };
}

#endif //MOS_TEST_CORE_H
