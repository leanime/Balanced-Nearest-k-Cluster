//
//  nearest neighborhood.cpp
//  NHH
//
//  Created by raku on 2017/11/09.
//  Copyright © 2017年 raku. All rights reserved.
//

#include "nearest neighborhood.hpp"
#include <vector>
#include <chrono>
#include <iostream>
using namespace std;

void evaluecircle::caculatedelta(const Point p,const double Apha){
    if (Apha>0&&Apha<1) {
        delta=Apha*C.c.distance(p)+(1-Apha)*C.r;
    }
    else delta=std::numeric_limits<double>::max();
}


evaluecircle singleSEC(RStarTree &tree,Point &pnext,int k, Point &piontQ,const double Apha){

    evaluecircle ec;
    Point_V pv;
    RStarTreeUtil *rtu=new RStarTreeUtil();
    pv=rtu->kNNquery(tree, pnext, k);
    //std::cout<<" ok";
    ec.C=makeSmallestEnclosingCircle(pv);
    ec.caculatedelta(piontQ,Apha);
    rtu->~RStarTreeUtil();
    return ec;

}


//evaluecircle simpleNNH(RStarTree &tree, Point &q,int k){
//    const auto startTime = std::chrono::system_clock::now();
//
//    evaluecircle ec_v;
//    Point_V pv;
//    Point pnext;
//    int j=0;
//    RStarTreeUtil *rtu=new RStarTreeUtil();
//
//    for (int i=0; i<tree.root->aggregate; i++) {
//        pv= rtu->kNNquery(tree, q, i+1);
//        pnext=pv.back();
//        evaluecircle ec;
//        ec=singleSEC(tree, pnext, k,q);
//        if(ec.delta<ec_v.delta){
//            ec_v=ec;
//           // std::cout<<q.distance(pnext)<<"  "<<ec_v.delta<<"  "<<j<<std::endl;
//        }
//        j++;
//       // std::cout<<q.distance(pnext)<<"  "<<ec_v.delta<<"  "<<i<<std::endl;
//    }
//
//    std::cout<<"order:"<<j<<std::endl;
//    const auto endTime = std::chrono::system_clock::now();
//    const auto timeSpan = endTime - startTime;
//    std::cout << "exhaustive processing time:" << std::chrono::duration_cast<std::chrono::milliseconds>(timeSpan).count() << "[ms]"<<std::endl;
//    return ec_v;
//}
//
//
//
//
//
//evaluecircle Nearestneighborhood(RStarTree &tree, Point &q,int k){
//    const auto startTime = std::chrono::system_clock::now();
//
//    evaluecircle ec_v;
//    Point_V pv;
//    Point pnext;
//    //double minapha=Apha;
//    double minapha=std::min(Apha, 1-Apha);
//    double bound=std::numeric_limits<double>::max();
//    int j=0;
//    RStarTreeUtil *rtu=new RStarTreeUtil();
//
//
//    for (int i=0; i<tree.root->aggregate; i++) {
//        pv= rtu->kNNquery(tree, q, i+1);
//        //std::cout<<"bound"<<bound<<"  "<<std::endl;
//        if (pv.empty()) {
//            break;
//        }
//        pnext=pv.back();
//        j++;
//
//        if(q.distance(pnext)>bound){
//            break;
//        }
//            evaluecircle ec;
//            ec=singleSEC(tree, pnext, k,q);
//
//            if(ec.delta<ec_v.delta){
//                ec_v=ec;
//                bound=ec_v.delta/minapha;
//                //pnext.print();
//                //std::cout<<"pnext"<<bound<<q.distance(pnext)<<std::endl;
//                //std::cout<<"更新"<<bound<<"  "<<std::endl;
//        }
//
//    }
//
//    std::cout<<"order:"<<j<<std::endl;
//    const auto endTime = std::chrono::system_clock::now();
//    const auto timeSpan = endTime - startTime;
//    std::cout << "NNH processing time:" << std::chrono::duration_cast<std::chrono::milliseconds>(timeSpan).count() << "[ms]"<<std::endl;
//     return ec_v;
//}
//


evaluecircle BNkC(RStarTree &tree, Point &q,int k,const double Apha){

    const auto startTime = std::chrono::system_clock::now();

    RStarTreeUtil *rtu=new RStarTreeUtil();
    evaluecircle ec_v;
    Point_V pv;
    double minapha=std::min(Apha, 1-Apha);
    int j=0;
    Point pnext=rtu->NNquery(tree, q);
    evaluecircle ec;
    ec=singleSEC(tree, pnext,k,q,Apha);
    double bound=ec.delta/minapha;
    pv= rtu->QuerykNNquery(tree, q, INT_MAX, bound);

    while(!pv.empty()) {

        //std::cout<<"bound"<<bound<<"  "<<pv.size()<<"  "<<std::endl;
        pnext=pv.front();
        pv.erase(pv.begin());
        j++;

        if(pnext.distance(q)>bound){
            break;
        }
        //std::cout<<"distance"<<pnext.distance(q)<<" order："<<j<<std::endl;
        evaluecircle ec;
        ec=singleSEC(tree, pnext, k,q,Apha);

        if(ec.delta<ec_v.delta){
            ec_v=ec;
            bound=ec_v.delta/minapha;
           // std::cout<<"更新"<<bound<<"  "<<std::endl;


        }

    }



    std::cout<<"order:"<<j<<std::endl;
    const auto endTime = std::chrono::system_clock::now();
    const auto timeSpan = endTime - startTime;
    std::cout<<"α:"<<  Apha <<" BNkC processing time:"<< std::chrono::duration_cast<std::chrono::milliseconds>(timeSpan).count() << "[ms]"<<std::endl;
    return ec_v;

}



//
//evaluecircle BalancedNearestneighborhood(RStarTree &tree, Point &q,int k){
//
//    const auto startTime = std::chrono::system_clock::now();
//    evaluecircle ec_v;
//    Point_V pv;
//    Point pnext;
//    //double minapha=Apha;
//    double minapha=std::min(Apha, 1-Apha);
//    double bound=std::numeric_limits<double>::max();
//    int j=0;
//    RStarTreeUtil *rtu=new RStarTreeUtil();
//    for (int i=0; i<tree.root->aggregate; i++) {
//
//        pv= rtu->QuerykNNquery(tree, q, i+1,bound);
//        //std::cout<<"bound"<<bound<<"  "<<pv.size()<<"  "<<std::endl;
//        pnext=pv.back();
//        j++;
//
//        if(pnext.distance(q)>bound){
//            break;
//        }
//        //std::cout<<"distance"<<pnext.distance(q)<<" order："<<j<<std::endl;
//        evaluecircle ec;
//        ec=singleSEC(tree, pnext, k,q);
//
//        if(ec.delta<ec_v.delta){
//            ec_v=ec;
//            bound=ec_v.delta/minapha;
//            //std::cout<<"更新"<<bound<<"  "<<std::endl;
//
//
//        }
//
//    }
//
//
//
//    //std::cout<<"order:"<<j<<std::endl;
//    const auto endTime = std::chrono::system_clock::now();
//    const auto timeSpan = endTime - startTime;
//    std::cout << "BNNH processing time:" << std::chrono::duration_cast<std::chrono::milliseconds>(timeSpan).count() << "[ms]"<<std::endl;
//    return ec_v;
//}
