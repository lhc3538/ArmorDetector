#ifndef ARMORDETECTOR_H
#define ARMORDETECTOR_H
#include <iostream>
#include <cstring>
#include <queue>
#include <cv.h>
#include <highgui.h>
#include <opencv2/objdetect/objdetect.hpp>
#include "predictor.h"

using namespace cv;
using namespace std;

class ArmorDetector
{
public:
    ArmorDetector();
    ArmorDetector(String armor_cascade_name );

    void initPara();
    int detectObject(Mat &image,Rect &pos);

private:
    /**
     * @brief armor_cascade
     * The object detector described below has been initially proposed by Paul Viola
     *  and improved by Rainer Lienhart.
     */
    CascadeClassifier armor_cascade;

    /**
     * @brief scaleFactor
     * Parameter specifying how much the image size is reduced at each image scale.
     */
    double scaleFactor;

    /**
     * @brief minNeighbors
     * Parameter specifying how many neighbors each candiate rectangle should have to retain it.
     */
    int minNeighbors;

    /**
     * @brief flags
     *  Parameter with the same meaning for an old cascade as in the function cvHaarDetectObjects.
     *  It is not used for a new cascade.
     */
    int flags;

    /**
     * @brief minSize
     * Minimum possible object size. Objects smaller than that are ignored.
     */
    Size minSize;

    /**
     * @brief maxSize
     * Maximum possible object size. Objects larger than that are ignored.
     */
//    Size maxSize;

    /**
     * @brief predictor
     * Predict the armor's postion or region
     */
    Predictor predictor;
};

#endif // ARMORDETECTOR_H
