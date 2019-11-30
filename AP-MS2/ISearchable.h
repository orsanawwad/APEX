#ifndef AP_MS2_ISEARCHABLE_H
#define AP_MS2_ISEARCHABLE_H


#include <unordered_set>
#include "State.h"

template<typename StateType, typename CostType>
class ISearchable {
public:
    virtual State<StateType, CostType> *getInitialState() = 0;

    virtual State<StateType, CostType> *getGoalState() = 0;

    virtual std::unordered_set<State<StateType, CostType> *, StateHash<StateType, CostType>, StateEqual<StateType, CostType>>
    getAllPossibleStatesFrom(State<StateType, CostType> *state) = 0;

    virtual ~ISearchable() {}
};

#endif //AP_MS2_ISEARCHABLE_H
