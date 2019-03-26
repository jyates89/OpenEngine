/*
 * Strategy.h
 *
 *  Created on: May 30, 2017
 *      Author: jyates
 */

#ifndef PATTERNS_STRATEGY_H_
#define PATTERNS_STRATEGY_H_

class Strategy {
public:
    Strategy();
    virtual ~Strategy();

    virtual void executeStrategy() = 0;
private:

};

inline Strategy::Strategy() {
}

inline Strategy::~Strategy() {
}

#endif /* PATTERNS_STRATEGY_H_ */
