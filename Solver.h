//
// Created by shani on 12/01/2020.
//

#ifndef EX4_SOLVER_H
#define EX4_SOLVER_H

template <typename Problem,typename Solution>
class Solver{
    virtual Solution solve(Problem problem) = 0;
};

#endif //EX4_SOLVER_H
