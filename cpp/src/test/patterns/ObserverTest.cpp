//
// Created by jyates on 3/25/19.
//

#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include "patterns/Observable.h"
#include "patterns/Observer.h"

class Subscriber : public Observer {
public:
    Subscriber() :  Observer(), articlesRead(0) {}
    ~Subscriber() override = default;

    int notify() override {
        ++articlesRead;
        return 0;
    }

    int getArticlesRead() const {
        return articlesRead;
    }

private:
    int articlesRead;
};

class Newspaper : public Observable {
public:
    Newspaper() = default;
    ~Newspaper() override = default;
};


TEST(ObserverPattern, Observable) { // NOLINT
    std::shared_ptr<Subscriber> subscriberPtr(new Subscriber());

    Newspaper newspaper;
    newspaper.subscribeObserver(subscriberPtr);

    newspaper.notifySubscribers();

    EXPECT_EQ(subscriberPtr->getArticlesRead(), 1);
}

int main(int argc, char** argv) {
    // Always required for gtest, which handles argument parsing.
    ::testing::InitGoogleMock(&argc, argv);

    // Run ALL tests found in this file (or in included headers).
    return RUN_ALL_TESTS();
}
