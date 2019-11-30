#ifndef AP_MS2_SEARCHERSOLUTION_H
#define AP_MS2_SEARCHERSOLUTION_H

#include <string>
#include <vector>
#include <unordered_map>
#include "Solution.h"
#include "State.h"

template<typename StateType, typename CostType>
class SearcherSolution : public Solution<std::string,CostType> {
private:
    State<StateType, CostType> *fromState;
public:

    SearcherSolution(State<StateType, CostType> *fromState1) : fromState(fromState1) {

        if (fromState != NULL) {
            fromState = fromState->clone();
            State<StateType, CostType> *cloner = fromState;
            while (cloner->getParentState() != NULL) {
                cloner->setParentState(cloner->getParentState()->clone());
                cloner = cloner->getParentState();
            }
        }
    }

    virtual CostType getCost() const {
        if (fromState == NULL) {
            return -1;
        }
        return fromState->getCost();
    }

    virtual std::string getValues() const {
        if (fromState == NULL) {
            return std::string("-1");
        }

        std::unordered_map<std::pair<int, int>, std::string, PairHash<int, int>> helperMap;
        helperMap.insert({{0, 1}, std::string("Right")});
        helperMap.insert({{0, -1}, std::string("Left")});
        helperMap.insert({{1, 0}, std::string("Down")});
        helperMap.insert({{-1, 0}, std::string("Up")});

        State<StateType, CostType> *currentState = fromState;
        std::vector<std::string> directions;
        while (currentState->getParentState() != NULL) {
            std::pair<int,int> directionPair = *currentState - *currentState->getParentState();
            directions.push_back(helperMap[directionPair]);
            currentState = currentState->getParentState();
        }
        std::stringstream ss;

        for (auto it = directions.end() - 1; it != directions.begin() - 1; --it) {
            ss << *it;
            if (it != (directions.begin())) {
                ss << ",";
            }
        }
        return std::string(ss.str());
    }

    virtual ~SearcherSolution() {
        while(fromState != NULL) {
            State<StateType, CostType> *deleter = fromState;
            deleter = fromState->getParentState();
            delete fromState;
            fromState = deleter;
            deleter = NULL;
        }
        fromState = NULL;
    }
};

#endif //AP_MS2_SEARCHERSOLUTION_H
