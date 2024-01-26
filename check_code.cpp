#include "opencv2/highgui/highgui.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/opencv.hpp"  // Include the main OpenCV header file

using namespace cv;

int main(int argc, char* argv[])
{
    VideoCapture cap(2); 
    cap.set(CAP_PROP_FPS, 30);
    if (!cap.isOpened())  // if not success, exit program
    {
        // std::cout << "Cannot open the video cam" << std::endl;
        return -1;
    }

    //double dWidth = cap.get(cv::CAP_PROP_FRAME_WIDTH); // get the width of frames of the video
    //double dHeight = cap.get(cv::CAP_PROP_FRAME_HEIGHT); // get the height of frames of the video

    // std::cout << "Frame size : " << dWidth << " x " << dHeight << std::endl;

    namedWindow("MyVideo", WINDOW_AUTOSIZE); // create a window called "MyVideo"
    while (1)
    {
        Mat frame;
        Mat frame2;
        Mat frame3;
        Mat frame4;
        bool bSuccess = cap.read(frame); // read a new frame from video
        if (!bSuccess) // if not success, break loop
        {
            // std::cout << "Cannot read a frame from video stream" << std::endl;
            break;
        }

        imshow("MyVideo", frame); // show the frame in "MyVideo" window

        if (waitKey(30) == 27) // wait for 'esc' key press for 30ms. If 'esc' key is pressed, break loop
        {
            // std::cout << "esc key is pressed by the user" << std::endl;
            break;
        }
    }

    return 0;
}
/*
#include<iostream>
#include<thread>
#include<chrono>

void print(){
    std::this_thread::sleep_for(std::chrono::seconds{1});
    std::cout<< "Thread ID: " << std::this_thread::get_id() << '\n';
}

void print2(){
    std::this_thread::sleep_for(std::chrono::seconds{5});
    std::cout<< "Thread ID: "<< std::this_thread::get_id()<< '\n';
}
int main(){
    auto thread_t1 = std::thread{print};
    thread_t1.join();
    std::cout<< "Thread ID: " << std::this_thread::get_id()<< '\n';
    auto thread_t2 = std::thread{print2};
    thread_t2.join();
    std::cout<< "Thread ID: " << std::this_thread::get_id() << '\n';
}

#include <opencv2/opencv.hpp>

int main() {
    if (cv::cuda::getCudaEnabledDeviceCount() > 0) {
        std::cout << "CUDA is enabled!" << std::endl;
    } else {
        std::cout << "CUDA is not enabled." << std::endl;
    }

    return 0;
}

//g++ -o check_cuda check_cuda.cpp -lopencv_core -lopencv_highgui -lopencv_cudaarithm
*/


/*
#include <opencv2/opencv.hpp>

int main() {
    // Load calibration data (intrinsic parameters) obtained from camera calibration
    cv::Mat camera_matrix;  // Intrinsic matrix
    cv::Mat distortion_coefficients;  // Distortion coefficients

    // Load camera_matrix and distortion_coefficients from your calibration results

    // Load and stitch your images
    std::vector<cv::Mat> images;  // Add your stitched images to this vector

    cv::Mat result;
    cv::Stitcher stitcher = cv::Stitcher::create();
    cv::Stitcher::Status status = stitcher.stitch(images, result);

    if (status != cv::Stitcher::OK) {
        std::cerr << "Stitching failed with status code: " << status << std::endl;
        return -1;
    }

    // Rectify the stitched image
    cv::Mat result_rectified;

    cv::Size img_size = result.size();
    cv::Mat new_camera_matrix = cv::getOptimalNewCameraMatrix(camera_matrix, distortion_coefficients, img_size, 1, img_size);

    // Generate rectification maps
    cv::Mat mapx, mapy;
    cv::initUndistortRectifyMap(camera_matrix, distortion_coefficients, cv::Mat(), new_camera_matrix, img_size, CV_16SC2, mapx, mapy);

    // Rectify the image
    cv::remap(result, result_rectified, mapx, mapy, cv::INTER_LINEAR);

    // Crop the rectified image
    cv::Rect roi;
    cv::Mat result_rectified_cropped;
    cv::getRectSubPix(result_rectified, img_size, cv::Point2f(img_size.width/2, img_size.height/2), result_rectified_cropped);

    // Save or display the rectified and cropped image
    cv::imwrite("result_rectified_cropped.jpg", result_rectified_cropped);
    cv::imshow("Rectified Image", result_rectified_cropped);
    cv::waitKey(0);

    return 0;
}

*/


/*4 Cameras working - 100 iterations
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/opencv.hpp"  // Include the main OpenCV header file

using namespace cv;

int main(int argc, char* argv[])
{
    VideoCapture cap(0);// open the video camera no. 0
    VideoCapture cap2(2);
    VideoCapture cap3(4);
    VideoCapture cap4(6);
    cap.set(CAP_PROP_FPS, 30);
    cap2.set(CAP_PROP_FPS, 30);
    cap3.set(CAP_PROP_FPS, 30);
    cap4.set(CAP_PROP_FPS, 30);
    
    if (!cap.isOpened())  // if not success, exit program
    {
        // std::cout << "Cannot open the video cam" << std::endl;
        return -1;
    }


    namedWindow("MyVideo", WINDOW_AUTOSIZE); // create a window called "MyVideo"
    namedWindow("MyVideo2", WINDOW_AUTOSIZE);
    namedWindow("MyVideo3", WINDOW_AUTOSIZE);
    namedWindow("MyVideo4", WINDOW_AUTOSIZE);
    while (1)
    {
        Mat frame;
        Mat frame2;
        Mat frame3;
        Mat frame4;
        cap >> frame;
        cap2 >> frame2;
        cap3 >> frame3; 
        cap4 >> frame4;       
        imshow("MyVideo", frame); // show the frame in "MyVideo" window
        imshow("MyVideo2", frame2);
        imshow("MyVideo3", frame3);
        imshow("MyVideo4", frame4);
        if (waitKey(30) == 's') // wait for 'esc' key press for 30ms. If 'esc' key is pressed, break loop
        {
            for(int i=0; i<1; i++){
                cv::imwrite("image1.jpg", frame);
                cv::imwrite("image2.jpg", frame2);
                cv::imwrite("image3.jpg", frame3);
                cv::imwrite("image4.jpg", frame4);
                cv::Stitcher::Mode mode = cv::Stitcher::PANORAMA;
                std::string input_image_path1  = "/home/zhen/image_stitching/image1.jpg";
                std::string input_image_path2  = "/home/zhen/image_stitching/image2.jpg";
                std::string input_image_path3  = "/home/zhen/image_stitching/image3.jpg";
                std::string input_image_path4  = "/home/zhen/image_stitching/image4.jpg";

                cv::Mat input_image1 = cv::imread(input_image_path1);
                cv::rotate(input_image1, input_image1, cv::ROTATE_90_COUNTERCLOCKWISE);
                cv::Mat input_image2 = cv::imread(input_image_path2);
                cv::rotate(input_image2, input_image2, cv::ROTATE_90_CLOCKWISE);
                cv::Mat input_image3 = cv::imread(input_image_path3);
                cv::Mat input_image4 = cv::imread(input_image_path4);                
                cv::Mat pano;
                std::vector<cv::Mat> images_to_stitch;
                images_to_stitch.push_back(input_image4);
                images_to_stitch.push_back(input_image3);
                images_to_stitch.push_back(input_image2);
                images_to_stitch.push_back(input_image1);

                cv::Ptr<cv::Stitcher> stitcher = cv::Stitcher::create(mode);
                cv::Stitcher::Status status = stitcher->stitch(images_to_stitch, pano);

                if (status == cv::Stitcher::OK) {
                    std::cout<< "Stitching was successful" << std::endl;
                    cv::imwrite("stitched.jpg", pano);
                } else if (status == cv::Stitcher::ERR_NEED_MORE_IMGS) {
                    std::cout<<"More  Images are Needed " << std::endl;// More images are needed
                } else if (status == cv::Stitcher::ERR_HOMOGRAPHY_EST_FAIL) {
                    std::cout<<"Homography Estimation Failed"<< std::endl;// Homography estimation failed
                } else if (status == cv::Stitcher::ERR_CAMERA_PARAMS_ADJUST_FAIL) {
                    std::cout<<"Camera Parameter adjustment failed" << std::endl;// Camera parameter adjustment failed
                } else {
                    std::cout<<"Moving for the next stitching"<< std::endl;
                    //continue;// Handle other cases as needed
                }

            }

        }
    }

    return 0;
}

*/


//
/*Working Version - 4 cameras input and stitching

#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/stitching.hpp>

#include <iostream>
#include <fstream>

int main(){
cv::VideoCapture camera0(0);
    cv::VideoCapture camera2(2);
    cv::VideoCapture camera4(4);
    cv::VideoCapture camera6(6);

    if(!camera0.isOpened()) return 1;
    if(!camera2.isOpened()) return 1;
    if(!camera4.isOpened()) return 1;
    if(!camera6.isOpened()) return 1;

    while(true){
        cv::Mat save_image;
        cv::Mat frame0;
        camera0 >> frame0;
        cv::Mat frame2;
        camera2 >> frame2;
        cv::Mat frame4;
        camera4 >> frame4;
        cv::Mat frame6;
        camera6 >> frame6;

        cv::imshow("Video0", frame0);
        cv::imshow("Video2", frame2);
        cv::imshow("Video4", frame4);
        cv::imshow("Video6", frame6);
        


                int c = cv::waitKey(40);
                if('s'== c){
                cv::imwrite("image1.jpg", frame0);
                cv::imwrite("image2.jpg", frame2);
                cv::imwrite("image3.jpg", frame4);
                cv::imwrite("image4.jpg", frame6);
                cv::Stitcher::Mode mode = cv::Stitcher::PANORAMA;
                std::string input_image_path1  = "/home/zhen/image_stitching/image1.jpg";
                std::string input_image_path2  = "/home/zhen/image_stitching/image2.jpg";
                std::string input_image_path3  = "/home/zhen/image_stitching/image3.jpg";
                std::string input_image_path4  = "/home/zhen/image_stitching/image4.jpg";



                cv::Mat input_image1 = cv::imread(input_image_path1);
                cv::rotate(input_image1, input_image1, cv::ROTATE_90_COUNTERCLOCKWISE);
                cv::Mat input_image2 = cv::imread(input_image_path2);
                cv::rotate(input_image2, input_image2, cv::ROTATE_90_CLOCKWISE);
                cv::Mat input_image3 = cv::imread(input_image_path3);
                cv::Mat input_image4 = cv::imread(input_image_path4);
                
                cv::Mat pano;
                std::vector<cv::Mat> images_to_stitch;
                images_to_stitch.push_back(input_image1);
                //images_to_stitch.push_back(input_image2);
                images_to_stitch.push_back(input_image3);
                images_to_stitch.push_back(input_image4);

                cv::Ptr<cv::Stitcher> stitcher = cv::Stitcher::create(mode);
                cv::Stitcher::Status status = stitcher->stitch(images_to_stitch, pano);

                if (status != cv::Stitcher::OK) {
                    std::cout << "Can't Stitch Images \n";
                    return -1;
                }
                cv::imwrite("stitched.jpg", pano);
                

                }
        }
    return 0;

}

*/

/*Single Video Smooth 30 FPS
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/opencv.hpp"  // Include the main OpenCV header file

using namespace cv;

int main(int argc, char* argv[])
{
    VideoCapture cap(0); // open the video camera no. 0
    cap.set(CAP_PROP_FPS, 30);
    if (!cap.isOpened())  // if not success, exit program
    {
        // std::cout << "Cannot open the video cam" << std::endl;
        return -1;
    }

    double dWidth = cap.get(cv::CAP_PROP_FRAME_WIDTH); // get the width of frames of the video
    double dHeight = cap.get(cv::CAP_PROP_FRAME_HEIGHT); // get the height of frames of the video

    // std::cout << "Frame size : " << dWidth << " x " << dHeight << std::endl;

    namedWindow("MyVideo", WINDOW_AUTOSIZE); // create a window called "MyVideo"

    while (1)
    {
        Mat frame;

        bool bSuccess = cap.read(frame); // read a new frame from video

        if (!bSuccess) // if not success, break loop
        {
            // std::cout << "Cannot read a frame from video stream" << std::endl;
            break;
        }

        imshow("MyVideo", frame); // show the frame in "MyVideo" window

        if (waitKey(30) == 27) // wait for 'esc' key press for 30ms. If 'esc' key is pressed, break loop
        {
            // std::cout << "esc key is pressed by the user" << std::endl;
            break;
        }
    }

    return 0;
}

        
*/

/* 10 Iterations image stitching
 std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    cv::Stitcher::Mode mode = cv::Stitcher::PANORAMA;

        for(int i=0; i<10; i++){
            std::string input_image_path1  = "/home/zhen/image_stitching/capture2.jpeg";
            std::string input_image_path2  = "/home/zhen/image_stitching/capture22.jpeg";
            std::string input_image_path3  = "/home/zhen/image_stitching/capture222.jpeg";
            std::string input_image_path4  = "/home/zhen/image_stitching/capture2222.jpeg";

            cv::Mat input_image1 = cv::imread(input_image_path1);
            //cv::rotate(input_image1, input_image1, cv::ROTATE_90_COUNTERCLOCKWISE);
            cv::Mat input_image2 = cv::imread(input_image_path2);
            //cv::rotate(input_image2, input_image2, cv::ROTATE_90_CLOCKWISE);
            cv::Mat input_image3 = cv::imread(input_image_path3);
            cv::Mat input_image4 = cv::imread(input_image_path4);
            
            cv::Mat pano;
            std::vector<cv::Mat> images_to_stitch;
            images_to_stitch.push_back(input_image1);
            images_to_stitch.push_back(input_image2);
            images_to_stitch.push_back(input_image3);
            images_to_stitch.push_back(input_image4);

            cv::Ptr<cv::Stitcher> stitcher = cv::Stitcher::create(mode);
            cv::Stitcher::Status status = stitcher->stitch(images_to_stitch, pano);

            if (status != cv::Stitcher::OK) {
                std::cout << "Can't Stitch Images \n";
                return -1;      
            }
            cv::imwrite("stitched.jpg", pano); 
        }  
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    std::cout << "Time taken to stich images = "<<  std::chrono::duration_cast<std::chrono::seconds>(end-begin).count()<< "[µs]" << std::endl;
    return 0;
*/

/* MultiTHreading Code for video capture
#include <iostream>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/opencv.hpp>
#include <future>

using namespace cv;

void processFrameAsync(Mat frame)
{
    // Your image processing code here
    // This function runs asynchronously in a separate thread
}

int main()
{
    VideoCapture cap(0);

    if (!cap.isOpened())
    {
        std::cerr << "Cannot open the video cam" << std::endl;
        return -1;
    }

    cap.set(CAP_PROP_FPS, 30);

    namedWindow("MyVideo", WINDOW_AUTOSIZE);

    while (1)
    {
        Mat frame;
        bool bSuccess = cap.read(frame);

        if (!bSuccess)
        {
            std::cerr << "Cannot read a frame from video stream" << std::endl;
            break;
        }

        // Asynchronously process the frame in a separate thread
        auto fut = std::async(std::launch::async, processFrameAsync, frame);

        imshow("MyVideo", frame);

        if (waitKey(30) == 27)
        {
            std::cout << "esc key is pressed by the user" << std::endl;
            break;
        }

        // Wait for the processing thread to finish
        fut.wait();
    }

    return 0;
}

*/