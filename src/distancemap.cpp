#include "libs/distancemaplib.h"
#include "libs/baseplannerlib.h"

int main( int argc, char** argv ){
    DistMapImage I2,base;
    DistMapImage I = imread(argv[1], CV_LOAD_IMAGE_GRAYSCALE);
    if (! I.data ){cout << "!!! Failed imread(): image not found" << endl; return -1;}
    ComputeDistanceMap(I, I2, base);
    DistMapImage path;
    FindPath(I2, path, base);
    return 0;
}
