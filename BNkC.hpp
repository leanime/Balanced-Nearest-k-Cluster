//
//  nearest neighborhood.hpp
//  NHH
//
//  Created by raku on 2017/11/09.
//  Copyright © 2017年 raku. All rights reserved.
//

#ifndef BNkC_hpp
#define BNkC_hpp

#include <stdio.h>
#include "SmallestEnclosingCircle.hpp"
#include "dyy_RTreeUtil.hpp"
#include "gridUtil.hpp"

#endif /* nearest_neighborhood_hpp */


class evaluecircle {
public:
     Circle C ;
     double delta = std::numeric_limits<double>::max();
     evaluecircle(){};
     void caculatedelta(const Point p,const double Apha);
};

class BNkC{
public:
    BNkC(){};
    
    evaluecircle BNkC_with_points(RStarTree &tree, Point &q,int k,const double Apha);
    evaluecircle BNkC_with_MBR(RStarTree &tree, Point &q,int k,const double Apha);
    //evaluecircle BNkC_with_Grid(Grid grid, Point &q,int k,const double Apha);
    evaluecircle simpleNNH(RStarTree &tree, Point &q,int k,const double Apha);
    evaluecircle singleSEC(RStarTree &tree,Point &pnext,int k, Point &piontQ,const double Apha);
    
};


inline evaluecircle BNkC::singleSEC(RStarTree &tree,Point &pnext,int k, Point &piontQ,const double Apha){
    
    evaluecircle ec;
    Point_V pv;
    RStarTreeUtil *rtu=new RStarTreeUtil();
    pv=type_convert(rtu->kNNquery(tree, pnext, k));
    //std::cout<<" ok";
    ec.C=makeSmallestEnclosingCircle(pv);
    ec.caculatedelta(piontQ,Apha);
    rtu->~RStarTreeUtil();
    return ec;
    
}
