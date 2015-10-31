#include "distancemaplib.h"

int rows_num, cols_num;
priorityq pq;

bool inRange(int a, int b){
    bool out=false;
    if(a>=0 && a<cols_num && b>=0 && b<rows_num)
        out = true;
    return out;
}

void ComputeDistanceMap (const DistMapImage I, DistMapImage& I2, DistMapImage& base){
    double dist;
    double min, max;
    rows_num=I.rows;
    cols_num=I.cols;
    I2 = Mat::ones( rows_num, cols_num, CV_8UC1 )*255;
    Mat I3;
    cell *head = new cell;
    if(!head) {cerr << "Errors in head" << endl; waitKey(0);}
    head->parent = NULL;
    for(int y=0;y<I.rows;y++){
        for(int x=0;x<I.cols;x++){
            double color = I.at<double>(Point(x,y));
            if(color < 100){
                cell *c = new cell;
                c->parent = NULL;
                c->point.x=x;
                c->point.y=y;
                c->value=0;
                head->point.x = c->point.x;
                head->point.y = c->point.y;
                head->value = c->value;
                head->parent = c;
                pq.push(*head);
                I2.at<double>(Point(x,y))=0;
            }
        }
    }
    base = I2;
    int cnt = 0;
    eight_point neighbours;
    cell cc;
    cell c1;
    cc.parent = NULL;
    c1.parent = NULL;
    int x_dad = 0;
    int y_dad = 0;
    while(!pq.empty()){
        cnt++;
        cc=pq.top();
        pq.pop();
        x_dad=cc.parent->point.x;
        y_dad=cc.parent->point.y;
        int x=cc.point.x;
        int y=cc.point.y;
        neighbours.clear();
        for(int i=x-1; i<x+2; i++){
            for(int j=y-1; j<y+2; j++){
                if(inRange(i,j)){
                    if(I2.at<double>(j,i)>0 && (i!=x || j!=y) ){
                        neighbours.push_back(Point(i,j));
                    }
                }
            }
        }
        for(int i = 0; i < neighbours.size(); i++){
            dist = sqrt((neighbours[i].x-x_dad)*(neighbours[i].x-x_dad)+(neighbours[i].y-y_dad)*(neighbours[i].y-y_dad));
            if(I2.at<double>(Point(neighbours[i].x,neighbours[i].y)) > dist ){
                c1.point.x = neighbours[i].x;
                c1.point.y = neighbours[i].y;
                c1.value = dist;
                c1.parent = cc.parent;
                I2.at<double>(Point(neighbours[i].x,neighbours[i].y)) = dist;
                pq.push(c1);
            }
        }
        if(cnt%250==0){
            minMaxLoc(I2, &min, &max);
            I2.convertTo(I3, CV_8UC1, 255.0/(max - min), -min * 255.0/(max - min));
            imshow( "Distance Map", I3 );
            waitKey(1);
        }
    }
    minMaxLoc(I2, &min, &max);
    I2.convertTo(I3, CV_8UC1, 255.0/(max - min), -min * 255.0/(max - min));
    imshow( "Distance Map", I3 );
    waitKey(1);
}
