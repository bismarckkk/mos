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

        void node::stop(std::thread& th) {
            bool ok = false;
            auto handle = th.native_handle();
            running = false;
            for (int i = 0; i < FORCE_TERMINATE_TIME; i++) {
                std::this_thread::sleep_for(std::chrono::seconds(1));
                if (!th.joinable()) {
                    ok = true;
                    break;
                }
            }
            if (!ok) {
                pthread_cancel(handle);
            }
        }
    }
}
