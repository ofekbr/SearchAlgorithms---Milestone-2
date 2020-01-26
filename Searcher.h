//
// Created by shani on 15/01/2020.
//

#ifndef EX4_SEARCHER_H
#define EX4_SEARCHER_H

template <typename P, typename S>
class Searcher {
public:
    virtual S search(P problem) = 0;
    virtual int evaluatedNodes() = 0;
    virtual Searcher<P,S>* clone() = 0;

};

#endif //EX4_SEARCHER_H
