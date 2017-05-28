#ifndef PREDICTOR_H
#define PREDICTOR_H

#include <cv.h>
#include <queue>
#include "rectutil.h"

using namespace std;
using namespace cv;

class Predictor
{
public:
    Predictor();
    void push(Rect rect);
    int getZeroRectNums();
    Rect getRoiRect(int width,int height);
    Rect getRoiRect(Mat &image);
private:
    queue<Rect> last_rect;
    RectUtil rect_util;
    int zero_rect_nums;
};

#endif // PREDICTOR_H
