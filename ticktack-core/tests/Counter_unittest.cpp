//
// Created by clemente on 18/4/20.
//

//
// Created by clemente on 18/4/20.
//

#include <string>
#include "../src/TickTackStore.h"
#include "pthread.h"
#include "gtest/gtest.h"
#include <climits>

using namespace TickTack;
namespace {
    void *increment_50000(void *param){
        Counter &counter = *static_cast<Counter *>(param);
        for(int i=0; i<50000; i++){
            counter++;
        }
    }

    void createOverflowableStore(const string& dataPath, const string& key){
        ofstream file = ofstream(dataPath, std::ofstream::out | std::ofstream::trunc);

        file << (unsigned long)ULONG_MAX << " " << key << endl;

        file.close();
    }

    TEST(KEYSTORE_UNIT_TEST, OVERFLOW) {
        const string path = "./overflow.data";
        const string key = "akey";

        createOverflowableStore(path, key);

        TickTackStore tickTackStore = TickTackStore(path);
        Counter &counter = tickTackStore.getOrCreate("akey");

        EXPECT_EQ(18446744073709551615UL, (unsigned long) counter);

        bool exception = false;

        try {
            counter++;
        } catch (std::runtime_error &error) {
            exception = true;
        }

        ASSERT_TRUE(exception);

        EXPECT_EQ(18446744073709551615UL, (unsigned long) counter);

        tickTackStore.remove();
    }

    TEST(KEYSTORE_UNIT_TEST, BASIC_INCREMENT) {
        TickTackStore tickTackStore = TickTackStore("./basic_increment.data");
        Counter &counter = tickTackStore.getOrCreate("a key");

        EXPECT_NE(nullptr, &tickTackStore);
        EXPECT_EQ(0, (unsigned long) counter);

        counter++;
        EXPECT_EQ(1, (unsigned long) counter);

        tickTackStore.remove();
    }

    TEST(KEYSTORE_UNIT_TEST, COUNTER_MULTITHREAD) {
        TickTackStore tickTackStore = TickTackStore("./multithread.data");
        Counter &counter = tickTackStore.getOrCreate("a key");

        pthread_t t1, t2;

        pthread_create(&t1, nullptr, increment_50000, (void*) &counter);
        pthread_create(&t2, nullptr, increment_50000, (void*) &counter);

        pthread_join(t1, nullptr);
        pthread_join(t2, nullptr);

        EXPECT_EQ(100000, (unsigned long) counter);

        tickTackStore.remove();
    }
}