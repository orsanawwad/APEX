//
// Created by USER on 14/01/2019.
//

#ifndef AP_MS2_DFS_H
#define AP_MS2_DFS_H

#include <iostream>
#include <string>
#include <stack>

#include "SearcherSolution.h"
#include "Searcher.h"

template<typename StateType, typename CostType>
class DFS : public Searcher<SearcherSolution<StateType, CostType>, StateType, CostType> {
protected:
    std::stack<State<StateType, CostType>*> stack;
public:
    virtual SearcherSolution<StateType, CostType> search(ISearchable<StateType, CostType> *searchable) {

        this->numberOfStatesEvaluated = 0;
        State<StateType, CostType> *goalState = searchable->getGoalState();

        this->stack.push(searchable->getInitialState()->clone());

        while (!this->stack.empty()) {
            State<StateType, CostType> *currentState = this->stack.top();
            this->stack.pop();
            if (*currentState == *goalState) {
                this->numberOfStatesEvaluated = this->closedStates.size();
                SearcherSolution<StateType, CostType> searcherSolution = SearcherSolution<StateType, CostType>(currentState);

                delete currentState;

                while (!stack.empty()) {
                    this->closedStates.erase(stack.top());
                    delete stack.top();
                    stack.pop();
                }

                for (auto closed : this->closedStates) {
                    delete closed;
                }

                return searcherSolution;
            } else if (this->closedStates.find(currentState) == this->closedStates.end()) {

                this->closedStates.insert(currentState);
                std::unordered_set<State<StateType, CostType> *, StateHash<StateType, CostType>, StateEqual<StateType, CostType>> possibleStates = searchable->getAllPossibleStatesFrom(
                        currentState);
                for (auto state : possibleStates) {
                    stack.push(state->clone());
                    delete state;
                    state = NULL;
                }
            }
            delete currentState;
        }
        return SearcherSolution<StateType, CostType>(NULL);
    }
};

#endif //AP_MS2_DFS_H
