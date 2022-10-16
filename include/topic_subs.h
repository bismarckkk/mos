//
// Created by bismarck on 10/14/22.
//

#ifndef MOS_TEST_TOPIC_SUBS_H
#define MOS_TEST_TOPIC_SUBS_H

#include <condition_variable>
#include <mutex>
#include <vector>

#include "sub_node.h"

namespace mos {
    namespace internal {
        template<typename T, bool overwrite, ring_mode ring>
        struct topic_sub {
            std::mutex mtx;
            int pub_nid{-1};
            std::condition_variable* cv{nullptr};
            std::vector<sub_node<T, overwrite, ring>> queues;
        };
    }
};

#endif //MOS_TEST_TOPIC_SUBS_H
