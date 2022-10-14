//
// Created by bismarck on 22-10-11.
//
#include "queue.h"

using boost::lockfree::spsc_queue;

namespace mos {
    namespace internal {
        template<typename T, bool overwrite, ring_mode ring>
        void queue<T, overwrite, ring>::setCV(std::condition_variable* _cv) {
            cv.store(_cv);
        }

        template<typename T, bool overwrite, ring_mode ring>
        template<bool isPub, ring_mode _ring>
        typename std::enable_if<_ring==ring_mode::NO_RING, void>::type
        queue<T, overwrite, ring>::ring_action () {}

        template<typename T, bool overwrite, ring_mode ring>
        template<bool isPub, ring_mode _ring>
        typename std::enable_if<
                (_ring==ring_mode::RING_BY_PUB&&isPub) ||
                (_ring==ring_mode::RING_BY_SUB&&!isPub)
                , void>::type
        queue<T, overwrite, ring>::ring_action() {
            std::condition_variable* _cv = cv.load();
            if (_cv != nullptr) {
                _cv->notify_all();
            }
        }

        template<typename T, bool overwrite, ring_mode ring>
        template<bool _overwrite>
        typename std::enable_if<_overwrite, bool>::type
        queue<T, overwrite, ring>::get(T& t) {
            mtx.lock();
            bool r = spsc_queue<T>::pop(t);
            mtx.unlock();
            return r;
        }

        template<typename T, bool overwrite, ring_mode ring>
        template<bool _overwrite>
        typename std::enable_if<!_overwrite, bool>::type
        queue<T, overwrite, ring>::get(T& t) {
            return spsc_queue<T>::pop(t);
        }

        template<typename T, bool overwrite, ring_mode ring>
        template<bool _overwrite>
        typename std::enable_if<_overwrite, bool>::type
        queue<T, overwrite, ring>::push(T& t) {
            if (spsc_queue<T>::write_available() <= 0) {
                mtx.lock();
                spsc_queue<T>::pop();
                mtx.unlock();
            }
            return spsc_queue<T>::push(t);
        }

        template<typename T, bool overwrite, ring_mode ring>
        template<bool _overwrite>
        typename std::enable_if<!_overwrite, bool>::type
        queue<T, overwrite, ring>::push(T& t) {
            return spsc_queue<T>::push(t);
        }

        template<typename T, bool overwrite, ring_mode ring>
        bool queue<T, overwrite, ring>::empty() {
            return spsc_queue<T>::read_available();
        }
    }
}
