//
// Created by bismarck on 22-10-11.
//

#ifndef MOS_NODE_H
#define MOS_NODE_H

#include <atomic>
#include <vector>
#include <string>

#include <boost/serialization/singleton.hpp>

#include "core.h"
#include "publisher.h"
#include "subscriber.h"

namespace mos {
    namespace internal {
        class node: public boost::serialization::singleton<node> {
        private:
            std::vector<subscriber> subscriberList;
            std::string name;
            core* core_ptr{nullptr};
            std::atomic<bool> running;

        public:
            std::string getName();
            void setCore(core*);
        };
    }
}

#endif //MOS_NODE_H
