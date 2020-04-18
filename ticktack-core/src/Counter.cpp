//
// Created by clemente on 18/4/20.
//

#include "Counter.h"
#include <climits>

using namespace TickTack;

Counter::Counter(TickTackStore &tickTackStore, string key, unsigned long value) : tickTackStore(tickTackStore), key(key), value(value) {

}

Counter::~Counter() {

}

Counter::operator unsigned long() {
    return value;
}

/**
 * Increments the value performing a CAS operation. In case of overflow will throw a runtime_error.
 *
 * @param ignore
 * @return
 */
Counter &Counter::operator++(int ignore) {
    unsigned long new_val;
    unsigned long curr_val;

    do {
        curr_val = value;
        if (curr_val == ULONG_MAX) {
            throw std::runtime_error("Counter overflow");
        }
        new_val = curr_val + 1;
    } while(!std::atomic_compare_exchange_weak(&value, &curr_val, new_val));

    tickTackStore.writeChanges();
    return *this;
}