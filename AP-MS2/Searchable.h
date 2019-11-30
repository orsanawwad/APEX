//
// Created by Orsan Awwad on 13/01/2019.
//

#ifndef AP_MS2_SEARCHABLE_H
#define AP_MS2_SEARCHABLE_H

#include <iostream>
#include <string>
#include <sstream>
#include <vector>

#include "ISearchable.h"

template<typename StateType, typename CostType>
class Searchable : public ISearchable<StateType, CostType> {
protected:
    std::vector<std::string> parseCSVLine(std::string line) {
        std::stringstream rowStream(line);
        std::vector<char> cellValue;
        std::vector<std::string> rowValues;
        char i;
        while (rowStream >> i) {
            cellValue.push_back(i);
            if (rowStream.peek() == ',') {
                rowValues.push_back(std::string(cellValue.begin(), cellValue.end()));
                cellValue.clear();
                rowStream.ignore();
            }
        }
        rowValues.push_back(std::string(cellValue.begin(), cellValue.end()));
        cellValue.clear();
        return rowValues;
    }

public:
    virtual State<StateType, CostType> *getInitialState() = 0;

    virtual State<StateType, CostType> *getGoalState() = 0;

    virtual std::unordered_set<State<StateType, CostType> *, StateHash<StateType, CostType>, StateEqual<StateType, CostType>>
    getAllPossibleStatesFrom(State<StateType, CostType> *state) = 0;

    virtual ~Searchable() {}
};

#endif //AP_MS2_SEARCHABLE_H
