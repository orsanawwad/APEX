//
// Created by Orsan Awwad on 12/01/2019.
//

#ifndef AP_MS2_MAZEDOMAIN_H
#define AP_MS2_MAZEDOMAIN_H

#include <vector>
#include <sstream>
#include <iostream>
#include <system_error>

#include "Searchable.h"

//template<typename StateType, typename CostType>
class MazeDomain : public Searchable<std::pair<int, int>, double> {
protected:
    State<std::pair<int, int>, double> *initialState;
    State<std::pair<int, int>, double> *goalState;
    std::vector<std::vector<State<std::pair<int, int>, double> *>> values;
    double size;

    bool isValidIndex(std::pair<int, int> index) {
        if (index.first < 0 || index.second < 0) {
            return false;
        } else if (index.first >= (int) size || index.second >= (int) size) {
            return false;
        } else {
            return true;
        }
    }

public:
    MazeDomain(std::string stringValues) : initialState(NULL),
                                           goalState(NULL) {
        std::istringstream stream(stringValues);
        std::string line;
        std::pair<int, int> startPoint;
        std::pair<int, int> goalPoint;
        int count = 0;
        int row = 0;
        int column = 0;
        while (std::getline(stream, line)) {
            std::vector<std::string> parsedVector = parseCSVLine(line);
            switch (count) {
                case 0: {
                    size = parsedVector.size();
                    std::vector<State<std::pair<int, int>, double> *> rowValues;
                    for (auto &value : parsedVector) {
                        rowValues.push_back(
                                new State<std::pair<int, int>, double>({row, column}, stoi(parsedVector[column])));
                        column++;
                    }
                    values.push_back(rowValues);
                    column = 0;
                    row++;
                    if (row == size) {
                        count++;
                    }
                    break;
                }
                case 1: {
                    startPoint = {stoi(parsedVector[0]), stoi(parsedVector[1])};
                    count++;
                    break;
                }
                case 2: {
                    goalPoint = {stoi(parsedVector[0]), stoi(parsedVector[1])};
                    count++;
                    break;
                }
                default:
                    throw std::system_error(std::error_code(errno, std::generic_category()), "could not parse correctly");

            }
        }
        initialState = values[startPoint.first][startPoint.second];
        initialState->setParentState(NULL);
        initialState->setCost(0);
        goalState = values[goalPoint.first][goalPoint.second];
    }

    virtual ~MazeDomain() {
        for (auto row : values) {
            for (auto state : row) {
                delete state;
                state = NULL;
            }
        }
    }

    virtual State<std::pair<int, int>, double> *getInitialState() {
        return this->initialState;
    }

    virtual State<std::pair<int, int>, double> *getGoalState() {
        return this->goalState;
    }

    virtual std::unordered_set<State<std::pair<int, int>, double> *, StateHash<std::pair<int, int>, double>, StateEqual<std::pair<int, int>, double>>
    getAllPossibleStatesFrom(State<std::pair<int, int>, double> *state) {

        std::unordered_set<State<std::pair<int, int>, double> *, StateHash<std::pair<int, int>, double>, StateEqual<std::pair<int, int>, double>> possible;

        std::pair<int, int> origin = state->getState();
        std::pair<int, int> up = {origin.first - 1, origin.second};
        std::pair<int, int> down = {origin.first + 1, origin.second};
        std::pair<int, int> left = {origin.first, origin.second - 1};
        std::pair<int, int> right = {origin.first, origin.second + 1};

        if (isValidIndex(up)) {
            State<std::pair<int, int>, double> *upState = values[up.first][up.second]->clone();//new State<std::pair<int, int>, double>(values[up.first][up.second]);
            if (state->getParentState() == NULL || *upState != *state->getParentState()) {
                if (upState->getCost() != -1) {
                    upState->setCost(state->getCost() + upState->getCost());
                    upState->setParentState(state);
                    possible.insert(upState);
                } else {
                    delete upState;
                    upState = NULL;
                }
            } else {
                delete upState;
                upState = NULL;
            }
        }

        if (isValidIndex(down)) {
            State<std::pair<int, int>, double> *downState = values[down.first][down.second]->clone();//new State<std::pair<int, int>, double>(values[down.first][down.second]);
            if (state->getParentState() == NULL || *downState != *state->getParentState()) {
                if (downState->getCost() != -1) {
                    downState->setCost(state->getCost() + downState->getCost());
                    downState->setParentState(state);
                    possible.insert(downState);
                } else {
                    delete downState;
                    downState = NULL;
                }
            } else {
                delete downState;
                downState = NULL;
            }
        }

        if (isValidIndex(left)) {
            State<std::pair<int, int>, double> *leftState = values[left.first][left.second]->clone();//new State<std::pair<int, int>, double>(values[left.first][left.second]);
            if (state->getParentState() == NULL || *leftState != *state->getParentState()) {
                if (leftState->getCost() != -1) {
                    leftState->setCost(state->getCost() + leftState->getCost());
                    leftState->setParentState(state);
                    possible.insert(leftState);
                } else {
                    delete leftState;
                    leftState = NULL;
                }
            } else {
                delete leftState;
                leftState = NULL;
            }
        }

        if (isValidIndex(right)) {
            State<std::pair<int, int>, double> *rightState = values[right.first][right.second]->clone();//new State<std::pair<int, int>, double>(values[right.first][right.second]);
            if (state->getParentState() == NULL || *rightState != *state->getParentState()) {
                if (rightState->getCost() != -1) {
                    rightState->setCost(state->getCost() + rightState->getCost());
                    rightState->setParentState(state);
                    possible.insert(rightState);
                } else {
                    delete rightState;
                    rightState = NULL;
                }
            } else {
                delete rightState;
                rightState = NULL;
            }
        }
        return possible;
    }
};


#endif //AP_MS2_MAZEDOMAIN_H
