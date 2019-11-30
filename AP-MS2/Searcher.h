//
// Created by Orsan Awwad on 13/01/2019.
//

#ifndef AP_MS2_SEARCHER_H
#define AP_MS2_SEARCHER_H

#include "ISearcher.h"
#include "MyPriorityQueue.h"

template<typename SolutionType, typename StateType, typename CostType>
class Searcher : public ISearcher<SolutionType, StateType, CostType> {
protected:
    unsigned long numberOfStatesEvaluated = 0;
    std::unordered_set<State<StateType, CostType> *, StateHash<StateType, CostType>, StateEqual<StateType, CostType>> closedStates;
public:
    virtual SolutionType search(ISearchable<StateType, CostType> *searchable) = 0;

    virtual unsigned long getNumberOfStatesEvaluated() {
        return this->numberOfStatesEvaluated;
    }

    virtual ~Searcher() {
        for (auto state : closedStates) {
            delete state;
        }
    }
};

#endif //AP_MS2_SEARCHER_H
