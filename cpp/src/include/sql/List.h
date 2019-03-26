/*
 * List.h
 *
 *  Created on: Jul 1, 2017
 *      Author: jyates
 */

#ifndef TYPES_SQL_LIST_H_
#define TYPES_SQL_LIST_H_

#include <string>
#include <vector>

#include <utility> // std::pair, std::make_pair

#include "SQL.h"

class List : public SQL {
public:
    typedef std::pair<std::string,
                      std::string> Entry;
    typedef std::vector<Entry>     Entries;

    Entries em_entries;

    List();
    ~List();

private:

    virtual void processDecoration(std::string& decoration);
};

inline List::List() {
}

inline List::~List() {
}


inline void List::processDecoration(std::string& decoration) {
    decoration.append(" (");
    for(auto it = em_entries.begin(), end = em_entries.end(); it != end; ++it) {
        if (it->first.length() > 0) {
            decoration.append(it->first);
        }
        decoration.append(it->second.get<std::string>() + (it + 1 == end ? "" : ","));
    }
    decoration.append(") ");
}

#endif /* TYPES_SQL_LIST_H_ */
