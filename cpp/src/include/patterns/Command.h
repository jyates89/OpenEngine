/*
 * Command.h
 *
 *  Created on: May 19, 2017
 *      Author: jyates
 */

#ifndef PATTERNS_COMMAND_H_
#define PATTERNS_COMMAND_H_

template<class CommandData>
class Command {
public:
    CommandData em_commandData;

    Command() = default;
    virtual ~Command() = default;

    virtual void execute() = 0;
};

#endif /* PATTERNS_COMMAND_H_ */
