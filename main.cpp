#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>
#include "armordetector.h"

using namespace cv;

void detectFromVideo()
{
    //    VideoCapture cap(1);//打开默认的摄像头
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
            armorDetector.detectObject(frame,armorPos);
            imshow("Video",frame);
            if(waitKey(30)==27) //Esc键退出
            {
                stop = true;
            }
        }
}

void detectFromPic()
{

        Mat frame;
        frame = imread("data/car.jpg");
        ArmorDetector armorDetector;
        Rect armorPos;
        armorDetector.detectObject(frame,armorPos);
        namedWindow("Picture");
        imshow("Picture",frame);
        waitKey(0);
}

int main(int argc,char *argv[])
{
//    detectFromPic();
    detectFromVideo();
    return 0;
}
