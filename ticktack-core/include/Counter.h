//
// Created by clemente on 18/4/20.
//

#ifndef TICKTACK_COUNTER_H
#define TICKTACK_COUNTER_H

#include <string>
#include <atomic>

using namespace std;

namespace TickTack {
    class TickTackStore;

    class Counter {
    public:
        /**
         * Creates a Counter with key = @param key and value @param value
         *
         * @param tickTackStore
         * @param key
         * @param value
         */
        Counter(TickTackStore &tickTackStore, string key, unsigned long value);

        virtual ~Counter();

        /**
         * Increments atomically by one unit the Counter value
         *
         * @param inc
         * @return
         */
        Counter &operator++(int inc);

        /**
         * Returns the Counter value as an unsigned long
         * @return
         */
        explicit operator unsigned long();

    private:
        TickTackStore &tickTackStore;
        string key;
        atomic_ulong value;
    };
}


#endif //TICKTACK_COUNTER_H
