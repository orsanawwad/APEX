//
// Created by Orsan Awwad on 2019-01-15.
//

#ifndef AP_MS2_SEARCHERSOLVERADAPTER_H
#define AP_MS2_SEARCHERSOLVERADAPTER_H


#include "ISolver.h"
#include "ISearcher.h"

//TODO: Change generics
class SearchableSolverAdapter : public server_side::ISolver<ISearchable<std::pair<int,int>,double>*,std::string> {
public:

    virtual std::string solve(ISearchable<std::pair<int, int>, double> *problem);

};


#endif //AP_MS2_SEARCHERSOLVERADAPTER_H
