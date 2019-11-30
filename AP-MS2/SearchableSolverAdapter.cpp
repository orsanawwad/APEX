//
// Created by Orsan Awwad on 2019-01-15.
//

#include "SearchableSolverAdapter.h"
#include "BFS.h"
#include "DFS.h"
#include "AstarAlgo.h"
#include "BestFirstSearch.h"


std::string SearchableSolverAdapter::solve(ISearchable<std::pair<int, int>, double> *searchable) {
    BFS<std::pair<int,int>,double> bfs;
    DFS<std::pair<int,int>,double> dfs;
    BestFirstSearch<std::pair<int,int>,double> bestFirstSearch;
    AstarAlgo<std::pair<int,int>,double> aStarAlgo;

    auto solution1 = bfs.search(searchable);
    auto solution2 = dfs.search(searchable);
    auto solution3 = bestFirstSearch.search(searchable);
    auto solution4 = aStarAlgo.search(searchable);

    auto &finalSolution = std::min(std::min(solution1,solution2),std::min(solution3,solution4));

    std::cout << solution1.getValues() << std::endl;
    std::cout << solution1.getCost() << std::endl;
    std::cout << bfs.getNumberOfStatesEvaluated() << std::endl;

    std::cout << solution2.getValues() << std::endl;
    std::cout << solution2.getCost() << std::endl;
    std::cout << dfs.getNumberOfStatesEvaluated() << std::endl;

    std::cout << solution3.getValues() << std::endl;
    std::cout << solution3.getCost() << std::endl;
    std::cout << bestFirstSearch.getNumberOfStatesEvaluated() << std::endl;

    std::cout << solution4.getValues() << std::endl;
    std::cout << solution4.getCost() << std::endl;
    std::cout << aStarAlgo.getNumberOfStatesEvaluated() << std::endl;

    return finalSolution.getValues();
}
