#include "armordetector.h"
#include <iostream>
#include "rectutil.h"

ArmorDetector::ArmorDetector()
{
    if( !armor_cascade.load( "data/maincar.xml" ) )
    {
        cout << "Load cascade failed!" << endl;
    }
    initPara();
}

ArmorDetector::ArmorDetector(String armor_cascade_name )
{
    if( !armor_cascade.load( armor_cascade_name ) )
    {
        cout << "Load cascade failed!" << endl;

    }
    initPara();
}

void ArmorDetector::initPara()
{
    scaleFactor = 1.14;
    minNeighbors = 4;
    flags = 0
            //|CV_HAAR_FIND_BIGGEST_OBJECT
            //|CV_HAAR_DO_ROUGH_SEARCH
            //|CV_HAAR_DO_CANNY_PRUNING
            |CV_HAAR_SCALE_IMAGE;
    minSize = Size(31, 29);
}

/**
 * @brief ArmorDetector::detectObject
 * detect object by "detectMultiScale"
 * @param image
 * Matrix containing an image where objects are detected.
 * @param pos
 * rectangle contains the detected object.
 * @return
 * whether contains the detected object in the image.
 */
int ArmorDetector::detectObject(Mat &image,Rect &pos)
{
    Mat cvFrame_gray;
    cvtColor( image, cvFrame_gray, CV_BGR2GRAY );
//    equalizeHist( cvFrame_gray, cvFrame_gray );

    /*get last_rects' public rect*/
    RectUtil rect_util;
    Rect roi_rect;
    Rect dyc_rect;
    roi_rect = predictor.getRoiRect(cvFrame_gray);
    dyc_rect = predictor.getRoiRect(image.cols,image.rows);
    roi_rect = roi_rect & dyc_rect;

    rectangle(image,roi_rect,Scalar(255,0,0),3);

    if (!rect_util.isZeroRect(roi_rect))
    {
        cvFrame_gray = cvFrame_gray(roi_rect);
    }
    vector<Rect> armors;
    armor_cascade.detectMultiScale(cvFrame_gray, armors, scaleFactor, minNeighbors);
//    armor_cascade.detectMultiScale(cvFrame_gray, armors, 1.14, 4, 0|CV_HAAR_SCALE_IMAGE, Size(32,29));
    for( size_t i = 0; i < armors.size(); i++ )
    {
        Rect real_rect = Rect(armors[i].x+roi_rect.x,
                              armors[i].y+roi_rect.y,
                              armors[i].width,
                              armors[i].height);
        rectangle(image,real_rect,Scalar(255,0,255),3);
    }

    if(armors.size()<=0)
    {
        /* add new rect to last_rect,and del oldest rect*/
        predictor.push(Rect(0,0,0,0));
        return 0;
    }
    else
    {
        /* add new rect to last_rect,and del oldest rect*/
        Rect real_rect = Rect(armors[0].x+roi_rect.x,
                              armors[0].y+roi_rect.y,
                              armors[0].width,
                              armors[0].height);
        predictor.push(real_rect);
        pos = real_rect;
        return 1;
    }
}
