#ifndef RECTUTIL_H
#define RECTUTIL_H
#include <queue>
#include <cv.h>

using namespace std;
using namespace cv;
class RectUtil
{
public:
    RectUtil();
    Rect calculatePublicRect(queue<Rect> rects);
    bool isZeroRect(Rect &rect);
};

#endif // RECTUTIL_H
