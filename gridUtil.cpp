//
//  gridUtil.cpp
//  BNkC query
//
//  Created by raku on 2018/06/08.
//  Copyright © 2018年 raku. All rights reserved.
//

#include "gridUtil.hpp"
using namespace dyy;
//****Grid Index Util****//
void gridUtil::CreateGrid(Point_V pv, Grid* grid){

    for(int i=0;i<pv.size();i++){
        grid->Add_cell(pv[i]);
    }

}

Point gridUtil::NNQuery(Grid *grid,Point q){
    const auto startTime = std::chrono::system_clock::now();
    Point  *NN_point = nullptr;
    int x= q.coords[0]/grid->step;
    int y= q.coords[1]/grid->step;
    std::vector<GridCell> gc;
    int range=0;
    double mindist = std::numeric_limits<double>::max();
    unsigned long num=grid->CellS_XY[x][y].P_v.size();
    int gnum=grid->number;

   std::cout<<x<<" "<<y;
    while(num<=0){
        for(int i=((x-range)<0)?0:(x-range);i<(((x+range)>gnum>0)?gnum:(x+range));i++){
            for (int j=((y-range)<0)?0:(y-range);j<(((y+range)>gnum>0)?gnum:(y+range));j++){
                num+=grid->CellS_XY[i][j].P_v.size();
            }
        }        range++;
    }

    for(int i=((x-range-1)<0)?0:(x-range-1);i<(((x+range+1)>gnum>0)?gnum:(x+range+1));i++){
        for (int j=((y-range-1)<0)?0:(y-range-1);j<(((y+range+1)>gnum>0)?gnum:(y+range+1));j++){
            gc.push_back(grid->CellS_XY[i][j]);

        }
    }

    for(int i=0;i<gc.size();i++){
        for(int j=0;j<gc[i].P_v.size();j++){
            if(mindist>gc[i].P_v[j].distance(q)){
                mindist=gc[i].P_v[j].distance(q);
                NN_point=&gc[i].P_v[j];
            }
        }
    }


//    std::cout<<" "<<range<<std::endl;
    const auto endTime = std::chrono::system_clock::now();
    const auto timeSpan = endTime - startTime;
    std::cout << "gird knn processing time:" << std::chrono::duration_cast<std::chrono::milliseconds>(timeSpan).count() << "[ms]"<<std::endl;

    return *NN_point;
}

Point_V gridUtil::kNNQuery(Grid *grid,Point q, int k){
    const auto startTime = std::chrono::system_clock::now();
    Point_V pA_V;
     Point  *NN_point = nullptr;
    int x= q.coords[0]/grid->step;
    int y= q.coords[1]/grid->step;
//    std::cout<<x<<"   "<<y<<std::endl;
    std::vector<GridCell> gc;
    int range=0;
    double minmindist = -std::numeric_limits<double>::min();
    unsigned long num=grid->CellS_XY[x][y].P_v.size();
    int gnum=grid->number;
    while(num<k){

        for(int i=((x-range)<0)?0:(x-range);i<=(((x+range)>gnum>0)?gnum-1:(x+range));i++){
            for (int j=((y-range)<0)?0:(y-range);j<=(((y+range)>gnum>0)?gnum-1:(y+range));j++){
                    num+=grid->CellS_XY[i][j].P_v.size();
            }
        }
        range++;
    }

    for(int i=((x-range-1)<0)?0:(x-range-1);i<=(((x+range+1)>gnum>0)?gnum-1:(x+range+1));i++){
        for (int j=((y-range-1)<0)?0:(y-range-1);j<=(((y+range+1)>gnum>0)?gnum-1:(y+range+1));j++){
                gc.push_back(grid->CellS_XY[i][j]);

        }
    }

    for(int o=0;o<k;o++){
    double mindist = std::numeric_limits<double>::max();
    for(int i=0;i<gc.size();i++){
        for(int j=0;j<gc[i].P_v.size();j++){
            if(mindist>=gc[i].P_v[j].distance(q)&&minmindist<gc[i].P_v[j].distance(q)){
                if(!pA_V.empty()){
                    if(pA_V.back().equal(gc[i].P_v[j]))
                        continue;
                    else{
                        mindist=gc[i].P_v[j].distance(q);
                        NN_point=&gc[i].P_v[j];
                    }
                }
                else{
                mindist=gc[i].P_v[j].distance(q);
                NN_point=&gc[i].P_v[j];
                }
            }
        }
     }
        pA_V.push_back(*NN_point);
        minmindist=NN_point->distance(q);
    }

//    std::cout<<" "<<range<<std::endl;

    const auto endTime = std::chrono::system_clock::now();
    const auto timeSpan = endTime - startTime;
    std::cout << "gird knn processing time:" << std::chrono::duration_cast<std::chrono::milliseconds>(timeSpan).count() << "[ms]"<<std::endl;

    return pA_V;
}



