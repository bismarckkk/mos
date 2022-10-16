//
// Created by bismarck on 10/14/22.
//

#ifndef MOS_TEST_SUB_NODE_H
#define MOS_TEST_SUB_NODE_H

#include <boost/shared_ptr.hpp>

#include "queue.h"

namespace mos {
    namespace internal {
        template<typename T, bool overwrite, ring_mode ring>
        struct sub_node {
            std::shared_ptr<queue<T, overwrite, ring>> qu;
            int sub_nid;
        };
    }
};

#endif //MOS_TEST_SUB_NODE_H
