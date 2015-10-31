#include "baseplannerlib.h"

void FindPath(DistMapImage distmap, DistMapImage& path, DistMapImage base){
    int cols=distmap.cols;
    int rows=distmap.rows;
    int x,y;
    eight_point neighbours;
    simplepriorityq pq;
    simplecell c,cc;
    double updated_path_value, path_value, alpha;
    Point start, goal;
    bool right_points = false;
    int goalx, goaly, startx, starty;
    while(!right_points){
        while(!right_points){
            cout << "Type start point coordinates \n x = ";
            cin >> startx;
            cout << " y = ";
            cin >> starty;
            start = Point(startx, starty);
            if( startx<distmap.cols && startx>=0 && starty<distmap.rows && starty>=0 && distmap.at<double>(start)!=0 ){
                right_points = true;
            }
            else cout << "Bad coords, retry" << "\n";
        }
        right_points=false;
        while(!right_points){
            cout << "Type goal point coordinates \n x = ";
            cin >> goalx;
            cout << " y = ";
            cin >> goaly;
            goal = Point(goalx, goaly);
            if( goalx<distmap.cols && goalx>=0 && goaly<distmap.rows && goaly>=0 && distmap.at<double>(goal)!=0 ){
                right_points = true;
            }
            else cout << "Bad coords, retry" << "\n";
        }
    }
    waitKey(1);
    c.point = start;
    c.value = 0;
    pq.push(c);
    Mat1d workarea = Mat1d::ones(rows,cols)*-1.0d;
    workarea.at<double>(start)=1.0d;
    workarea.at<double>(goal)=1.0d;
    bool goal_found=false;
    cout << "Choose the parameter value in bewteen 1 (shortest path) and 0.0001 (safest path) \n";
    cin >> alpha;
    if(alpha < 0.0001d || alpha > 1.0d)alpha=1.0d;
    while(!pq.empty()  && !goal_found ){
        cc = pq.top();
        path_value = cc.value;
        pq.pop();
        x = cc.point.x;
        y = cc.point.y;
        neighbours.clear();
        for(int j = y-1; j < y + 2; j++){
            for(int i = x-1; i < x+2; i++){
                if( (i!=x || j!=y) && distmap.at<double>(j,i) != 0.0d ){
                    neighbours.push_back(Point(i,j));
                }
            }
        }
        for(int i = 0; i <neighbours.size(); i++){
            updated_path_value = path_value + abs(x - neighbours[i].x) + abs(y - neighbours[i].y);
            if( neighbours[i].x >= 0 && neighbours[i].x < cols && neighbours[i].y >= 0 && neighbours[i].y < rows ){
                if(Point(neighbours[i].x,neighbours[i].y) == goal ){
                    goal_found = true;
                    workarea.at<double>(neighbours[i].y, neighbours[i].x) = updated_path_value + 1.0d/((distmap.at<double>(neighbours[i].y, neighbours[i].x)+1)*alpha);
                    cerr << "Goal reached! \n";
                }
                if(workarea.at<double>(neighbours[i].y,neighbours[i].x)==-1.0d){
                    workarea.at<double>(neighbours[i].y, neighbours[i].x) = updated_path_value + 1.0d/((distmap.at<double>(neighbours[i].y, neighbours[i].x)+1)*alpha);
                    simplecell new_c;
                    new_c.point = Point(neighbours[i].x,neighbours[i].y);
                    new_c.value = workarea.at<double>(neighbours[i].y, neighbours[i].x);
                    pq.push(new_c);
                }
            }
        }
    }
    imshow( "Explored Area", workarea );
    waitKey(0);
    int x_index = -1;
    int y_index = -1;
    bool target_reached = false;
    Point current = goal;
    while(!target_reached){
        double minimo = 999999.0d;
        x = current.x;
        y = current.y;
        for(int j = y-1; j < y + 2; j++){
            for(int i = x-1; i < x+2; i++){
                if( Point(i,j) == start ){
                    target_reached=true;
                    x_index = i;
                    y_index = j;
                }
                else if( i >= 0 && i < cols && j >= 0 && j < rows && (i!=x || j!=y) && distmap.at<double>(j,i) != 0.0d ){
                    if(workarea.at<double>(j,i)<minimo && workarea.at<double>(j,i)!=-1.0d && workarea.at<double>(j,i)!=1.0d){
                        minimo = workarea.at<double>(j,i);
                        x_index = i;
                        y_index = j;
                    }
                }
            }
        }
        base.at<double>(y_index,x_index)=0.0d;
        current.x=x_index;
        current.y=y_index;
    }
    imshow( "path", base );
    waitKey(0);
}
