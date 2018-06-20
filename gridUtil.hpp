//
//  gridUtil.hpp
//  BNkC query
//
//  Created by raku on 2018/06/08.
//  Copyright © 2018年 raku. All rights reserved.
//

#ifndef gridUtil_hpp
#define gridUtil_hpp

#include <stdio.h>
#include "dyy_data.hpp"
#include "grid.hpp"
#endif /* gridUtil_hpp */

using namespace dyy;
class gridUtil{
public:
    void CreateGrid(Point_V pv,Grid* grid);
    Point NNQuery(Grid *grid,Point q);
    Point_V kNNQuery(Grid *grid,Point q,int k);
};

