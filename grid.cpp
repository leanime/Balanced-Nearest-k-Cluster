//
//  grid.cpp
//  BNkC query
//
//  Created by raku on 2018/06/06.
//  Copyright © 2018年 raku. All rights reserved.
//

#include "grid.hpp"
/*********************************************************************
 *Cell
 ********************************************************************/
void GridCell::Add_point(Point p){
    P_v.push_back(p);
}



void GridCell::print()
{
 
    std::cout << "Objects num: ";
    std::cout << P_v.size();
    
    std::cout << std::endl;
    std::cout << "Range: ";
    std::cout << "<" << leftLow[0] << "," << leftLow[1] << ">"<<"-";
    std::cout << "<" << rightUp[0] << "," << rightUp[1] << ">";
    std::cout << std::endl;
    std::cout << "X："<<x<<" "<< "Y："<<y<<std::endl;
    std::cout << "points:";
    for(int i=0;i<P_v.size();i++){
        P_v[i].print();
    }
    std::cout << std::endl << "-----------------------" << std::endl;
}

/*********************************************************************
 *Grid (many cells)
 ********************************************************************/

void Grid::init()
{
    CellS_XY.resize(number);
    for(int x = 0; x < number; x++){
        CellS_XY[x].resize(number);
        for(int y = 0; y < number; y++){
            auto l = {x * step, y * step};
            auto r = {(x+1) * step, (y+1) * step};
            GridCell gc(l,r);
            gc.setXY(x, y);
            CellS_XY[x][y] = gc;
        }
    }
}

void Grid::Add_cell(Point p){
    int x = p.coords[0]/step;
    int y = p.coords[1]/step;
    //std::cout<<p.coords[0];
    GridCell *cell = &(CellS_XY[x][y]);
    cell->Add_point(p);

}



void Grid::Print(){
        std::cout << "Cells number: " << number * number;
        std::cout << std::endl << "-----------------------" << std::endl;
        for(int x = 0; x < number; x++){
            for(int y = 0; y < number; y++){
                CellS_XY[x][y].print();
            }
        }
}



