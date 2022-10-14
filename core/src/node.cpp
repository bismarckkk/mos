//
// Created by bismarck on 10/14/22.
//

#include "node.h"

namespace mos {
    namespace internal {
        std::string node::getName() {
            return name;
        }

        void node::setCore(core* ptr) {
            core_ptr = ptr;
        }
    }
}
