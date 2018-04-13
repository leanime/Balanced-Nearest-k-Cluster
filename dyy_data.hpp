#ifndef _DYY_DATA_HPP_
#define _DYY_DATA_HPP_

#include <vector>
#include <iostream>
#include <fstream>
#include <cassert>
#include <string>
#include "const.h"
#include "dyy_RStarTree.hpp"

/*
  Data model used in the research of YuyangDong
 */

namespace dyy{
/*********************************************************************
 * Point
 ********************************************************************/
class Point
{
public:
    Coord_V coords;
    double x;
    double y;
    int id;
    Point(){};
    Point(Coord_V v){coords = v;}
    Point(Coord a, Coord b)
    {
        coords.push_back(a);
        coords.push_back(b);
        x=a;
        y=b;
    }
    
    
    

    friend std::istream& operator>>(std::istream& in, Point& p);
    bool operator< (const Point& p) const;

public:
    void print();
    Point subtract(const Point &p) const;
    double distance(const Point &p) const;
    // Signed area / determinant thing
    double cross(const Point &p) const;
    bool equal(const Point &p) const;

};


/*********************************************************************
 * Data
 ********************************************************************/

typedef std::vector<Point> Point_V;
typedef std::vector<LeafNodeEntry> Entry_V;

class Data
{
public:

    Point_V Products;
    Point_V Weights;
    Point_V Queries;

    Point_V Q2;

    RStarTree RtreeP;
    RStarTree RtreeW;

    Data(){};
    ~Data(){};

    Entry_V entriesP;
    Entry_V entriesW;

    static void loadPoint(std::string fileName, Point_V &v);
    static void buildTree(Point_V& points, Entry_V& entries, RStarTree* tree);

};


}



#endif /*_DYY_DATA_HPP_*/
