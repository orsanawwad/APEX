//
// Created by USER on 14/01/2019.
//

#ifndef AP_MS2_ASTARALGO_H
#define AP_MS2_ASTARALGO_H



#include "MyPriorityQueue.h"
#include <iostream>
#include <string>

#include "SearcherSolution.h"
#include "Searcher.h"

template<typename StateType, typename CostType>
class AstarAlgo : public Searcher<SearcherSolution<StateType, CostType>, StateType, CostType> {
protected:
    MyPriorityQueue<State<StateType, CostType> *, std::vector<State<StateType, CostType> *>, StateComparator<StateType, CostType>> priorityQueue;

    CostType manhattanDistanceHeuristics(State<StateType, CostType> *left, State<StateType, CostType> *right) {
        auto result = *left - *right;
        CostType resultEstimate = abs(result.first) + abs(result.second);
        return resultEstimate;
    }

public:
    virtual SearcherSolution<StateType, CostType> search(ISearchable<StateType, CostType> *searchable) {

        this->numberOfStatesEvaluated = 0;
        State<StateType, CostType> *goalState = searchable->getGoalState();

        auto init = searchable->getInitialState()->clone();

        init->setCost(init->getCost() + manhattanDistanceHeuristics(init,goalState));

        this->priorityQueue.push(init);

        while (!this->priorityQueue.empty()) {
            State<StateType, CostType> *currentState = this->priorityQueue.top();
            this->priorityQueue.pop();
            if (*currentState == *goalState) {
                this->numberOfStatesEvaluated = this->closedStates.size();
                SearcherSolution<StateType, CostType> goalSolution = SearcherSolution<StateType, CostType>(currentState);

                while (!priorityQueue.empty()) {
                    this->closedStates.erase(priorityQueue.top());
                    delete priorityQueue.top();
                    priorityQueue.pop();
                }

                delete currentState;

                return goalSolution;
            };
            this->closedStates.insert(currentState);

            std::unordered_set<State<StateType, CostType> *, StateHash<StateType, CostType>, StateEqual<StateType, CostType>> possibleStates = searchable->getAllPossibleStatesFrom(
                    currentState);

            for (auto state : possibleStates) {
                state->setCost(state->getCost() + manhattanDistanceHeuristics(state,goalState) - manhattanDistanceHeuristics(currentState, goalState));
                if (this->closedStates.find(state) == this->closedStates.end() &&
                    this->priorityQueue.find(state) == this->priorityQueue.end()) {
                    this->priorityQueue.push(state->clone());
                } else if (this->priorityQueue.find(state) != this->priorityQueue.end()) {
                    State<StateType, CostType> *stateToCompare = *this->priorityQueue.find(state);;
                    if (state->getCost() < stateToCompare->getCost()) {
                        this->priorityQueue.remove(stateToCompare);
                        this->priorityQueue.push(state->clone());
                    }
                }
                delete state;
                state = NULL;
            }
            delete currentState;
        }

        return SearcherSolution<StateType, CostType>(NULL);
    }
};


#endif //AP_MS2_ASTARALGO_H
