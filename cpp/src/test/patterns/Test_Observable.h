/*
 * Test_Observable.h
 *
 *  Created on: Jun 5, 2017
 *      Author: jyates
 */

#ifndef TESTING_PATTERNS_TEST_OBSERVABLE_H_
#define TESTING_PATTERNS_TEST_OBSERVABLE_H_

#include <sstream>
#include <cxxtest/TestSuite.h>

#include "../Types/StandardDefines.h"

#include "../../Patterns/Observable.h"
#include "../../Patterns/Observer.h"

class Subscriber : public Observer {
public:
    Subscriber() :  Observer(), articlesRead(0) {}
    ~Subscriber() {}

    int notify() {
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
    Newspaper() {}
    ~Newspaper() {}

};

class Test_Observable: public CxxTest::TestSuite {
public:
    void setUp   () { }
    void tearDown() { }

    void testObservable() {
        std::shared_ptr<Subscriber> subscriberPtr(new Subscriber());

        Newspaper newspaper;
        newspaper.subscribeObserver(subscriberPtr);

        newspaper.notifySubscribers();

        TS_ASSERT(subscriberPtr->getArticlesRead() == 1);
        std::stringstream subscriberResult("Articles read: ", std::ios::app|std::ios::out);
        subscriberResult << subscriberPtr->getArticlesRead();
        TS_TRACE(subscriberResult.str().c_str());
    }

private:

};

#endif // TESTING_PATTERNS_TEST_OBSERVABLE_H_
