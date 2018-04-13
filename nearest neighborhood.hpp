//
//  nearest neighborhood.hpp
//  NHH
//
//  Created by raku on 2017/11/09.
//  Copyright © 2017年 raku. All rights reserved.
//

#ifndef nearest_neighborhood_hpp
#define nearest_neighborhood_hpp

#include <stdio.h>
#include "SmallestEnclosingCircle.hpp"
#include "dyy_RTreeUtil.hpp"

#endif /* nearest_neighborhood_hpp */


class evaluecircle {
public:
     Circle C ;
     double delta = std::numeric_limits<double>::max();
     evaluecircle(){};
     void caculatedelta(const Point p,const double Apha);
};


evaluecircle BalancedNearestneighborhood(RStarTree &tree, Point &q,int k);
evaluecircle BNkC(RStarTree &tree, Point &q,int k,const double Apha);
evaluecircle Nearestneighborhood(RStarTree &tree, Point &q,int k);
evaluecircle simpleNNH(RStarTree &tree, Point &q,int k);
evaluecircle singleSEC(RStarTree &tree,Point &pnext,int k, Point &piontQ,const double Apha);
