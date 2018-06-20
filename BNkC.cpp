//
//  nearest neighborhood.cpp
//  NHH
//
//  Created by raku on 2017/11/09.
//  Copyright © 2017年 raku. All rights reserved.
//

#include "BNkC.hpp"
#include <vector>
#include <chrono>
#include <queue>
#include <iostream>
//****Evaluation circle****//
void evaluecircle::caculatedelta(const Point p,const double Apha){
    if (Apha>0&&Apha<1) {
        delta=Apha*C.c.distance(p)+(1-Apha)*C.r;
    }
    else delta=std::numeric_limits<double>::max();
}


//*****Blanced Nearest k-Cluster****//




evaluecircle BNkC::simpleNNH(RStarTree &tree, Point &q,int k,const double Apha){
    const auto startTime = std::chrono::system_clock::now();

    evaluecircle ec_v;
    Point_V pv;
    Point pnext;
    int j=0;
    RStarTreeUtil *rtu=new RStarTreeUtil();

    for (int i=0; i<tree.root->aggregate; i++) {
        
        pv=type_convert(rtu->kNNquery(tree, q, i+1));
        pnext=pv.back();
        evaluecircle ec=singleSEC(tree, pnext, k,q,Apha);
        if(ec.delta<ec_v.delta){
            ec_v=ec;
           // std::cout<<q.distance(pnext)<<"  "<<ec_v.delta<<"  "<<j<<std::endl;
        }
        j++;
       // std::cout<<q.distance(pnext)<<"  "<<ec_v.delta<<"  "<<i<<std::endl;
    }

    std::cout<<"order:"<<j<<std::endl;
    const auto endTime = std::chrono::system_clock::now();
    const auto timeSpan = endTime - startTime;
    std::cout << "exhaustive processing time:" << std::chrono::duration_cast<std::chrono::milliseconds>(timeSpan).count() << "[ms]"<<std::endl;
    return ec_v;
}





evaluecircle BNkC::BNkC_with_MBR(RStarTree &tree, Point &q,int k,const double Apha){

    const auto startTime = std::chrono::system_clock::now();

    RStarTreeUtil *rtu=new RStarTreeUtil();
    evaluecircle ec_v;
    Point_V pv;
    double minapha=std::min(Apha, 1-Apha);
    int j=0;
    Point pnext=rtu->NNquery(tree, q);
    evaluecircle ec=singleSEC(tree, pnext,k,q,Apha);
    double bound=ec.delta/minapha;
    pv=type_convert(rtu->QuerykNNquery(tree, q, INT_MAX, bound));

    while(!pv.empty()) {

        //std::cout<<"bound"<<bound<<"  "<<pv.size()<<"  "<<std::endl;
        pnext=pv.front();
        pv.erase(pv.begin());
        j++;

        if(pnext.distance(q)>bound){
            break;
        }
        //std::cout<<"distance"<<pnext.distance(q)<<" order："<<j<<std::endl;

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
    std::cout<<"α:"<<  Apha <<"BNkC_with_MBR processing time:"<< std::chrono::duration_cast<std::chrono::milliseconds>(timeSpan).count() << "[ms]"<<std::endl;
//    double ratio=double((timeSpan_1).count())/double((timeSpan).count());
//     std::cout<<"α:"<<  Apha <<"QuerykNNquery processing ratio:"<< ratio*100<<"%"<<std::endl<<std::endl;
    return ec_v;

}


evaluecircle BNkC::BNkC_with_points(RStarTree &tree, Point &q,int k,const double Apha){

    const auto startTime = std::chrono::system_clock::now();
    evaluecircle ec_v;
    Point_V pv;
    Point pnext;
    double minapha=std::min(Apha, 1-Apha);
    double bound=std::numeric_limits<double>::max();
    int j=0;
    RStarTreeUtil *rtu=new RStarTreeUtil();
    for (int i=0; i<tree.root->aggregate; i++) {

        pv=type_convert(rtu->kNNquery(tree, q, i+1));
        //std::cout<<"bound"<<bound<<"  "<<pv.size()<<"  "<<std::endl;
        pnext=pv.back();
        j++;

        if(pnext.distance(q)>bound){
            break;
        }
        //std::cout<<"distance"<<pnext.distance(q)<<" order："<<j<<std::endl;
        evaluecircle ec=singleSEC(tree, pnext, k, q ,Apha );
        
        if(ec.delta<ec_v.delta){
            ec_v=ec;
            bound=ec_v.delta/minapha;
            //std::cout<<"更新"<<bound<<"  "<<std::endl;

        }
    }

    std::cout<<"order:"<<j<<std::endl;
    const auto endTime = std::chrono::system_clock::now();
    const auto timeSpan = endTime - startTime;
    std::cout<<"α:"<<  Apha <<" BNkC_with_points processing time:"<< std::chrono::duration_cast<std::chrono::milliseconds>(timeSpan).count() << "[ms]"<<std::endl;
    return ec_v;
}

