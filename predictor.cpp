#include "predictor.h"
#include <iostream>

#define MAX_RECTS 10
Predictor::Predictor()
{
    for (int i=0;i<MAX_RECTS;i++)
        last_rect.push(Rect(0,0,0,0));
    zero_rect_nums = MAX_RECTS;
}

void Predictor::push(Rect rect)
{
    if (rect_util.isZeroRect(rect))
        ++zero_rect_nums;
    if ( rect_util.isZeroRect(last_rect.front()) )
        --zero_rect_nums;

    if (zero_rect_nums < 0)
        zero_rect_nums = 0;
    else if(zero_rect_nums > MAX_RECTS)
        zero_rect_nums = MAX_RECTS;

    last_rect.push(rect);
    last_rect.pop();
}

int Predictor::getZeroRectNums()
{
    return zero_rect_nums;
}

Rect Predictor::getRoiRect(int width, int height)
{
//    cout << "width=" << width << " height=" << height;
    Rect roi_rect = rect_util.calculatePublicRect(last_rect);
    int x2 = roi_rect.x+roi_rect.width, y2 = roi_rect.y+roi_rect.height;
    int reverse_x = width - x2, reverse_y = height - y2;

    reverse_x = reverse_x * (MAX_RECTS - zero_rect_nums) / (MAX_RECTS + 1);
    reverse_y = reverse_y * (MAX_RECTS - zero_rect_nums) / (MAX_RECTS + 1);

    roi_rect.x = roi_rect.x * (MAX_RECTS - zero_rect_nums) / (MAX_RECTS + 1);
    roi_rect.y = roi_rect.y * (MAX_RECTS - zero_rect_nums) / (MAX_RECTS + 1);

    x2 = width - reverse_x;
    y2 = height - reverse_y;

    roi_rect.width = x2 - roi_rect.x;
    roi_rect.height = y2 - roi_rect.y;

    if(roi_rect.x < 0)
        roi_rect.x = 0;
    if(roi_rect.y < 0)
        roi_rect.y = 0;
    if(roi_rect.x+roi_rect.width > width)
        roi_rect.width = width - roi_rect.x;
    if(roi_rect.y+roi_rect.height > height)
        roi_rect.height = height - roi_rect.y;

//    cout << "x=" << roi_rect.x << ",y=" << roi_rect.y << ",width=" << roi_rect.width << ",height=" << roi_rect.height << endl;
//    cout << "zero_nums=" << zero_rect_nums << endl;
    return roi_rect;
}

Rect Predictor::getRoiRect(Mat &image)
{
    int x1 = 0, y1 = 0;
    int x2 = image.cols, cols = image.cols;
    int y2 = image.rows, rows = image.rows;

    /* traverse every col from left */
    for (int c=0;c<cols;++c) {

        int r;
        for(r=0;r<rows;++r) {
            /* more white */
            if(image.at<uchar>(r,c)>90) {
                x1 = c - 60;
                break;
            }
        }
        if(r!=rows)
            break;
    }
    /* traverse every col from right */
    for (int c=cols-1;c>=0;--c) {
        int r;
        for(r=0;r<rows;++r) {
            /* more white */
            if(image.at<uchar>(r,c)>90) {
                x2 = c + 60;
                break;
            }
        }
        if(r!=rows)
            break;
    }
    /* traverse every row from top */
    for (int r=0;r<rows;++r) {
        int c;
        for(c=0;c<cols;++c) {
            /* more white */
            if(image.at<uchar>(r,c)>90) {
                y1 = r - 60;
                break;
            }
        }
        if(c!=cols)
            break;
    }
    /* traverse every row from bottom */
    for (int r=rows-1;r>=0;--r) {
        int c;
        for(c=0;c<cols;++c) {
            /* more white */
            if(image.at<uchar>(r,c)>90) {
                y2 = r + 60;
                break;
            }
        }
        if(c!=cols)
            break;
    }

    if (x1 < 0)
        x1 = 0;
    if (y1 < 0)
        y1 = 0;
    if (x2 >= cols)
        x2 = cols-1;
    if (y2 >= rows)
        y2 = rows-1;

    return Rect(x1,y1,x2-x1,y2-y1);
}
