#ifndef AP_MS2_STATE_H
#define AP_MS2_STATE_H

#include <iostream>
#include <sstream>

template<typename StateType, typename CostType>
class State {
private:
    StateType state;
    CostType cost;
    State *parentState;
public:
    State(StateType state, CostType cost) : state(state), cost(cost), parentState(NULL) {}

    bool equalsTo(State<StateType, CostType> stateToCompare) { return stateToCompare.state == this->state; };

    void setParentState(State *parent) {
        this->parentState = parent;
    }

    State *getParentState() const {
        return parentState;
    }

    bool operator==(const State &rhs) const {
        return state == rhs.state;
    }

    bool operator==(const State *rhs) const {
        return state == rhs->state;
    }

    bool operator!=(const State &rhs) const {
        return state != rhs.state;
    }


    StateType getState() const {
        return state;
    }

    CostType getCost() const {
        return cost;
    }

    void setCost(CostType cost) {
        this->cost = cost;
    }

    State(State<StateType, CostType> *&pState) {
        this->state = pState->state;
        this->cost = pState->cost;
        this->parentState = pState->parentState;
    }

    State* clone() {
        return new State<StateType, CostType>(*this);
    }
};

template<typename StateType, typename CostType>
struct StateComparator {
    bool operator()(const State<StateType, CostType> *lhs, const State<StateType, CostType> *rhs) const {
        return lhs->getCost() > rhs->getCost();
    }
};

template<typename StateType, typename CostType>
struct StateEqual {
public:
    bool operator()(const State<StateType, CostType> &state1, const State<StateType, CostType> &state2) const {
        return state1.getState() == state2.getState();
    }

    bool operator()(const State<StateType, CostType> *state1, const State<StateType, CostType> *state2) const {
        return state1->getState() == state2->getState();
    }
};

template<typename StateType, typename CostType>
struct StateHash {

    std::string toString(State<StateType, CostType> state) const {
        std::stringstream aa;
        aa << state.getState().first;
        aa << ",";
        aa << state.getState().second;
        return aa.str();
    }

    std::size_t operator()(const State<StateType, CostType> &_state) const {
        return std::hash<std::string>()(toString(_state));
    }

    std::size_t operator()(const State<StateType, CostType> *_state) const {
        return std::hash<std::string>()(toString(*_state));
    }
};

template<typename T, typename G>
struct PairHash {

    std::string toString(std::pair<T, G> state) const {
        std::stringstream aa;
        aa << state.first;
        aa << ",";
        aa << state.second;
        return aa.str();
    }

    std::size_t operator()(const std::pair<T, G> &pair) const {
        return std::hash<std::string>()(toString(pair));
    }

    std::size_t operator()(const std::pair<T, G> *pair) const {
        return std::hash<std::string>()(toString(*pair));
    }
};

template<typename StateType, typename CostType>
std::pair<int,int> operator-(const State<StateType, CostType>& lhs, const State<StateType, CostType>& rhs) {
    return std::pair<int,int>(lhs.getState().first - rhs.getState().first, lhs.getState().second - rhs.getState().second);
}

#endif //AP_MS2_STATE_H
