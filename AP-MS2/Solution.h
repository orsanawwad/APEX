//
// Created by Orsan Awwad on 13/01/2019.
//

#ifndef AP_MS2_SOLUTION_H
#define AP_MS2_SOLUTION_H

template<typename ReturnType, typename CostType>
class Solution {
public:
    virtual CostType getCost() const = 0;
    virtual ReturnType getValues() const = 0;
    virtual ~Solution() {}
};

template<typename ReturnType, typename CostType>
bool operator<(const Solution<ReturnType, CostType>& lhs, const Solution<ReturnType, CostType>& rhs) {
    const auto lcost = lhs.getCost();
    const auto rcost = rhs.getCost();
    return lcost < rcost;
}

template<typename ReturnType, typename CostType>
bool operator>(const Solution<ReturnType, CostType>& lhs, const Solution<ReturnType, CostType>& rhs) {
    const auto lcost = lhs.getCost();
    const auto rcost = rhs.getCost();
    return lcost > rcost;
}

template<typename ReturnType, typename CostType>
bool operator<=(const Solution<ReturnType, CostType>& lhs, const Solution<ReturnType, CostType>& rhs) {
    const auto lcost = lhs.getCost();
    const auto rcost = rhs.getCost();
    return lcost <= rcost;
}

template<typename ReturnType, typename CostType>
bool operator>=(const Solution<ReturnType, CostType>& lhs, const Solution<ReturnType, CostType>& rhs) {
    const auto lcost = lhs.getCost();
    const auto rcost = rhs.getCost();
    return lcost >= rcost;
}

#endif //AP_MS2_SOLUTION_H
