#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>
#include <time.h>
#include <stdio.h>
#include "armordetector.h"

using namespace cv;

void detectFromCam()
{
    clock_t start, finish;
    double  duration;

    VideoCapture cap(0);//打开默认的摄像头
    if(!cap.isOpened())
    {
        return ;
    }
    Mat frame;
    bool stop = false;
    ArmorDetector armorDetector;
    Rect armorPos;

    while(!stop)
    {
        cap.read(frame); //  或cap>>frame;

        start = clock();
        armorDetector.detectObject(frame,armorPos);
        finish = clock();
        duration = (double)(finish - start) / CLOCKS_PER_SEC;
        printf("time: %lf s\n", duration) ;
        cout << armorPos << endl << endl;

        imshow("Cam",frame);
        if(waitKey(30)==27) //Esc键退出
        {
            stop = true;
        }
    }
}

void detectFromVideo()
{
    clock_t start, finish;
    double  duration;

    VideoCapture cap;
    cap.open("data/video.mp4");

    if(!cap.isOpened())
    {
        return ;
    }
    Mat frame;
    bool stop = false;
    ArmorDetector armorDetector;
    Rect armorPos;
    while(!stop)
    {
        cap.read(frame); //  或cap>>frame;

        start = clock();
        armorDetector.detectObject(frame,armorPos);
        finish = clock();
        duration = (double)(finish - start) / CLOCKS_PER_SEC;
        printf("time: %lf s\n", duration) ;
        cout << armorPos << endl << endl;

        imshow("Video",frame);
        if(waitKey(30)==27) //Esc键退出
        {
            stop = true;
        }
    }
}

void detectFromPic()
{
    clock_t start, finish;
    double  duration;

    Mat frame;
    frame = imread("data/car.jpg");
    ArmorDetector armorDetector;
    Rect armorPos;

    start = clock();
    armorDetector.detectObject(frame,armorPos);
    finish = clock();
    duration = (double)(finish - start) / CLOCKS_PER_SEC;
    printf("time: %lf s\n", duration) ;
    cout << armorPos << endl;

    namedWindow("Picture");
    imshow("Picture",frame);
    waitKey(0);
}

int main(int argc,char *argv[])
{
//    detectFromPic();
//    detectFromVideo();
    detectFromCam();
    return 0;
}
