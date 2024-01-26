#include "opencv2/highgui/highgui.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/opencv.hpp"
#include <thread>

using namespace cv;

void processVideo(VideoCapture& cap, const char* windowName) {
    namedWindow(windowName, WINDOW_AUTOSIZE);
    while (1) {
        Mat frame;
        bool bSuccess = cap.read(frame);

        if (!bSuccess) {
            break;
        }

        imshow(windowName, frame);

        if (waitKey(30) == 27) {
            break;
        }
    }
}

int main(int argc, char* argv[]) {
    VideoCapture cap1(0);
    VideoCapture cap2(2);
    VideoCapture cap3(4);
    //VideoCapture cap4(0);
    cap1.set(CAP_PROP_FPS, 30);
    cap2.set(CAP_PROP_FPS, 30);
    cap3.set(CAP_PROP_FPS, 30);
    //cap4.set(CAP_PROP_FPS, 30);

    if (!cap1.isOpened() ) //|| !cap2.isOpened() || !cap3.isOpened() || !cap4.isOpened()) {
    {    return -1;
    }

    std::thread thread1(processVideo, std::ref(cap1), "MyVideo1");
    std::thread thread2(processVideo, std::ref(cap2), "MyVideo2");
    std::thread thread3(processVideo, std::ref(cap3), "MyVideo3");
    //std::thread thread4(processVideo, std::ref(cap4), "MyVideo4");

    thread1.join();
    thread2.join();
    thread3.join();
    //thread4.join();

    return 0;
}
