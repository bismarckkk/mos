//
// Created by bismarck on 10/14/22.
//

#ifndef MOS_TEST_TOPIC_SUBS_H
#define MOS_TEST_TOPIC_SUBS_H

#include <mutex>
#include <vector>

#include "sub_node.h"

namespace mos {
    namespace internal {
        struct topic_sub {
            std::mutex mtx;
            std::vector<sub_node> queues;
        };
    }
};

#endif //MOS_TEST_TOPIC_SUBS_H
