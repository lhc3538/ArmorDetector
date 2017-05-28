#include "rectutil.h"
#include <vector>
#include <algorithm>
RectUtil::RectUtil()
{

}

Rect RectUtil::calculatePublicRect(queue<Rect> rects)
{
    int INF = 0x3f3f3f3f;
    int x1 = INF, y1 = INF, x2 = 0, y2 = 0;
    while(!rects.empty())
    {
        Rect temp_rect = rects.front();
        rects.pop();
        if (isZeroRect(temp_rect))
            continue;
        x1 = min(temp_rect.x,x1);
        y1 = min(temp_rect.y,y1);
        x2 = max(temp_rect.x+temp_rect.width,x2);
        y2 = max(temp_rect.y+temp_rect.height,y2);
    }
    return (x1 == INF)?Rect(0,0,0,0):Rect(x1,y1,x2-x1,y2-y1);
}

bool RectUtil::isZeroRect(Rect &rect)
{
    if(rect.x == 0 && rect.y == 0
            && rect.height == 0 && rect.width == 0)
        return true;
    else
        return false;
}
