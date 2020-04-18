//
// Created by clemente on 18/4/20.
//

#include <stdio.h>
#include "TickTackStore.h"

using namespace TickTack;
/**
 * It will load the store contents into memory using the counterMap structure
 *
 * @param dataPath
 */
TickTackStore::TickTackStore(const string dataPath) : dataPath(dataPath) {
    ifstream file = ifstream(dataPath);

    if (file.is_open()) {
        unsigned long value;
        string key;

        while (file >> value >> key){
            counterMap[key] = new Counter(*this, key, value);
        }

        file.close();
    }
}

TickTackStore::~TickTackStore() {
    map<string, Counter*>::iterator it;

    for ( it = counterMap.begin(); it != counterMap.end(); it++ )
    {
        Counter *counter = it->second;
        delete counter;
    }
}

/**
 * It removes the store from disk by removing the data file
 */
void TickTackStore::remove(){
    std::remove(dataPath.data());
}

/**
 * Gets or creates a counter and modifies the data file on disk
 *
 * @param key
 * @return
 */
Counter &TickTackStore::getOrCreate(string key) {
    if(counterMap.find(key) == counterMap.end()){
        counterMap[key] = new Counter(*this, key, 0);
    }

    writeChanges();
    return *counterMap[key];
}

/**
 * Dumps the data in memory into a data file on disk
 *
 * TODO: we could do the write on the background
 */
void TickTackStore::writeChanges() {
    // this happens in a thread
    ofstream file = ofstream(dataPath, std::ofstream::out | std::ofstream::trunc);

    map<string, Counter*>::iterator it;
    for ( it = counterMap.begin(); it != counterMap.end(); it++ )
    {
        Counter *counter = it->second;
        file << (unsigned long) *counter << " " << it->first << endl;
    }

    file.close();
}