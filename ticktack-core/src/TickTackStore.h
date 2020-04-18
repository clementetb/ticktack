//
// Created by clemente on 18/4/20.
//

#ifndef TICKTACK_CORE_TICKTACKSTORE_H
#define TICKTACK_CORE_TICKTACKSTORE_H

#include <string>
#include <iostream>
#include <fstream>
#include <map>
#include "Counter.h"

using namespace std;

namespace TickTack {
    class Counter;

    class TickTackStore {
    public:
        /**
         *
         * @param dataPath  location to store the counters
         */
        TickTackStore(string
                      dataPath);

        virtual ~TickTackStore();

        /**
         * This function creates or retrieves a Counter from disk
         * if it is a new Counter its value would be 0
         * else it would be the latest value it had
         *
         * @param key Counter's key to retrieve or to be created
         * @return Counter
         */
        Counter &getOrCreate(string key);

        /**
         * Writes changes into disk
         */
        void writeChanges();

        /**
         * Deletes the store from disk
         */
        void remove();

    private:
        string dataPath;
        map<string, Counter *> counterMap;
    };
}


#endif //TICKTACK_CORE_TICKTACKSTORE_H
