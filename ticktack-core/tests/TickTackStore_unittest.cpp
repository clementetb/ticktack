//
// Created by clemente on 18/4/20.
//

#include <sys/stat.h>
#include <string>
#include "../src/TickTackStore.h"
#include "pthread.h"
#include "gtest/gtest.h"

using namespace TickTack;
namespace {
    bool fileExists(const string path){
        struct stat buffer{};
        return (stat (path.c_str(), &buffer) == 0);
    }

    TEST(KEYSTORE_UNIT_TEST, STORE_CREATION_REMOVAL) {
        const string path = "./test1.data";

        EXPECT_EQ(false, fileExists(path));

        TickTackStore tickTackStore = TickTackStore(path);
        tickTackStore.writeChanges();

        EXPECT_EQ(true, fileExists(path));

        tickTackStore.remove();

        EXPECT_EQ(false, fileExists(path));
    }
}
