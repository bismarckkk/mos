//
// Created by bismarck on 22-10-11.
//

#ifndef MOS_QUEUE_H
#define MOS_QUEUE_H

#include <atomic>
#include <mutex>
#include <condition_variable>

#include <boost/lockfree/spsc_queue.hpp>

namespace mos {
    enum class ring_mode {
        NO_RING,
        RING_BY_PUB,
        RING_BY_SUB
    };

    namespace internal {
        template<typename T, bool overwrite, ring_mode ring>
        class queue: private boost::lockfree::spsc_queue<T> {
        private:
            std::mutex mtx;
            std::atomic<std::condition_variable*> cv{nullptr};
        public:
            void setCV(std::condition_variable* _cv);

            template<bool isPub, ring_mode _ring=ring>
            typename std::enable_if<_ring==ring_mode::NO_RING, void>::type
            ring_action();

            template<bool isPub, ring_mode _ring=ring>
            typename std::enable_if<
                (_ring==ring_mode::RING_BY_PUB&&isPub) ||
                (_ring==ring_mode::RING_BY_SUB&&!isPub)
                , void>::type
            ring_action();

            template<bool _overwrite = overwrite>
            typename std::enable_if<_overwrite, bool>::type get(T& t);

            template<bool _overwrite = overwrite>
            typename std::enable_if<!_overwrite, bool>::type get(T& t);

            template<bool _overwrite = overwrite>
            typename std::enable_if<_overwrite, bool>::type push(T& t);

            template<bool _overwrite = overwrite>
            typename std::enable_if<!_overwrite, bool>::type push(T& t);

            bool empty();
        };
    }
}

#endif //MOS_QUEUE_H
