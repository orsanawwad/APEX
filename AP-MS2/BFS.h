//
// Created by USER on 14/01/2019.
//

#ifndef AP_MS2_BFS_H
#define AP_MS2_BFS_H


#include <iostream>
#include <string>
#include <queue>

#include "SearcherSolution.h"
#include "Searcher.h"

template<typename StateType, typename CostType>
class BFS : public Searcher<SearcherSolution<StateType, CostType>, StateType, CostType> {
protected:
    std::queue<State<StateType, CostType>*> queue;
public:
    virtual SearcherSolution<StateType, CostType> search(ISearchable<StateType, CostType> *searchable) {

        this->numberOfStatesEvaluated = 0;
        State<StateType, CostType> *goalState = searchable->getGoalState();

        this->queue.push(searchable->getInitialState()->clone());

        while (!this->queue.empty()) {
            State<StateType, CostType> *currentState = this->queue.front();
            this->queue.pop();
            if (*currentState == *goalState) {
                this->numberOfStatesEvaluated = this->closedStates.size();
                SearcherSolution<StateType, CostType> searcherSolution = SearcherSolution<StateType, CostType>(currentState);

                delete currentState;

                while (!queue.empty()) {
                    this->closedStates.erase(queue.front());
                    delete queue.front();
                    queue.pop();
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
                    queue.push(state->clone());
                    delete state;
                    state = NULL;
                }
            }
            delete currentState;
        }
        return SearcherSolution<StateType, CostType>(NULL);
    }
};

#endif //AP_MS2_BFS_H
