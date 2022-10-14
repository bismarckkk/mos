//
// Created by bismarck on 10/14/22.
//

#ifndef MOS_TEST_SUB_NODE_H
#define MOS_TEST_SUB_NODE_H

#include <boost/any.hpp>
#include <boost/shared_ptr.hpp>

#include "queue.h"

namespace mos {
    namespace internal {
        struct sub_node {
            std::shared_ptr<boost::any> qu;
            int sub_nid;
        };
    }
};

#endif //MOS_TEST_SUB_NODE_H
