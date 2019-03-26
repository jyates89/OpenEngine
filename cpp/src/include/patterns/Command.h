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

    Command();
    virtual ~Command();

    virtual void execute() = 0;
};

template<class CommandData>
inline Command<CommandData>::Command() {
}

template<class CommandData>
inline Command<CommandData>::~Command() {
}

#endif /* PATTERNS_COMMAND_H_ */
