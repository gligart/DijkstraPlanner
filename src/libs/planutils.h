#ifndef _PLANUTILS
#define _PLANUTILS

#include<iostream>
#include<queue>
#include<vector>
#include<functional>
#include<opencv2/opencv.hpp>
#include<algorithm>

using namespace std;
using namespace cv;

struct cell{
    Point point;
    float value;
    struct cell *parent;
};

struct simplecell{
    Point point;
    float value;
};

class mycompare{
public:
    bool operator() (cell& lhs,cell& rhs){
        if(lhs.value>rhs.value)return true;
        else return false;
    }
};

class simple_cell_comparator{
public:
    bool operator() (simplecell& lhs, simplecell& rhs){
        if(lhs.value>rhs.value)return true;
        else return false;
    }
};

    typedef cv::Mat1d DistMapImage;
    typedef std::priority_queue< cell, vector<cell>, mycompare > priorityq;
    typedef std::priority_queue< simplecell, vector<simplecell>, simple_cell_comparator> simplepriorityq;
    typedef vector<Point> eight_point;

#endif
