#ifndef AP_MS2_ISEARCHER_H
#define AP_MS2_ISEARCHER_H

#include "ISearchable.h"

template<typename SolutionType, typename StateType, typename CostType>
class ISearcher {
public:
    virtual SolutionType search(ISearchable<StateType, CostType> *searchable) = 0;

    virtual unsigned long getNumberOfStatesEvaluated() = 0;

    virtual ~ISearcher() {}
};

#endif //AP_MS2_ISEARCHER_H
