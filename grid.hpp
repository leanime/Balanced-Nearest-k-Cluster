//
//  grid.hpp
//  BNkC query
//
//  Created by raku on 2018/06/06.
//  Copyright © 2018年 raku. All rights reserved.
//

#ifndef grid_hpp
#define grid_hpp

#include <stdio.h>
#include <vector>
#include "const.h"
#include "dyy_data.hpp"

using namespace dyy;
#endif /* grid_hpp */
class GridCell
{
    public:
    GridCell(){}
    GridCell(Coord_V l, Coord_V r){leftLow = l; rightUp = r;}
    
    Coord_V leftLow, rightUp;
    
    Point_V P_v;
    
    void print();
    void setXY(int _x, int _y){x = _x, y = _y;}
    
    int x, y;
    void  Add_point(Point p);
    void  Del_point(Point p);
    
    
    };


class Grid
{
public:
    Grid(){}
    /*Cells number = num * num*/
    Grid(int num) : number(num)
    {
        step = MAXDIST / number;
        init();
    }
    
    void init();
    
    std::vector<std::vector<GridCell> > CellS_XY;
    
    double step;
    int number;
    
    
    void  Add_cell(Point P);
    void  Del_cell(Point P);
    void  Print();
    
    
};

