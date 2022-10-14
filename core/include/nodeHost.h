//
// Created by bismarck on 10/14/22.
//

#ifndef MOS_TEST_NODEHOST_H
#define MOS_TEST_NODEHOST_H

#include <thread>

#include <boost/dll.hpp>

namespace mos {
    namespace internal {
        struct nodeHost {
            boost::dll::shared_library lib;
            int nid;
            std::thread th;
        };
    }
}

#endif //MOS_TEST_NODEHOST_H
