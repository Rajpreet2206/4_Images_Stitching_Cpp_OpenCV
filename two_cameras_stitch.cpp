#include "opencv2/highgui/highgui.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/opencv.hpp"  // Include the main OpenCV header file

using namespace cv;

int main(int argc, char* argv[])
{
    VideoCapture cap(0);// open the video camera no. 0
    VideoCapture cap2(2);

    cap.set(CAP_PROP_FPS, 30);
    cap2.set(CAP_PROP_FPS, 30);

    
    if (!cap.isOpened())  // if not success, exit program
    {
        // std::cout << "Cannot open the video cam" << std::endl;
        return -1;
    }


    namedWindow("MyVideo", WINDOW_AUTOSIZE); // create a window called "MyVideo"
    namedWindow("MyVideo2", WINDOW_AUTOSIZE);

     cv::Mat camera_matrix, distortion_coefficients, rotation_vectors;
    cv::FileStorage fs("calibration_data.xml", cv::FileStorage::READ);
    
    if (!fs.isOpened()) {
    std::cerr << "Error: Unable to open the XML file." << std::endl;
    return -1;
    }

    fs["cameraMatrix"] >> camera_matrix;
    fs["distortionCoefficients"] >> distortion_coefficients;
    fs["rotationVectors"] >> rotation_vectors;
    fs.release();

    if (rotation_vectors.cols <= 0) {
        std::cerr << "Error: Invalid number of rotation vectors." << std::endl;
        return -1;
    }

    while (1)
    {
        Mat frame;
        Mat frame2;

        cap >> frame;
        cap2 >> frame2;
    

        // Undistort each frame using camera matrix and distortion coefficients
        cv::Mat undistorted_frame, undistorted_frame2, undistorted_pano;
        cv::undistort(frame, undistorted_frame, camera_matrix, distortion_coefficients);
        cv::undistort(frame2, undistorted_frame2, camera_matrix, distortion_coefficients);
    
        //
        imshow("MyVideo", frame); // show the frame in "MyVideo" window
        //
        imshow("MyVideo2", frame2);

        if (waitKey(30) == 's') // wait for 'esc' key press for 30ms. If 'esc' key is pressed, break loop
        {
            for(int i=0; i<1; i++){
                cv::imwrite("image1.jpg", frame);
                cv::imwrite("image2.jpg", frame2);

                //cv::rotate(undistorted_frame, undistorted_frame, cv::ROTATE_90_COUNTERCLOCKWISE);
                cv::imwrite("image1_undistorted.jpg", undistorted_frame);
                //cv::rotate(undistorted_frame2, undistorted_frame2, cv::ROTATE_90_CLOCKWISE);
                cv::imwrite("image2_undistorted.jpg", undistorted_frame2);


                cv::Stitcher::Mode mode = cv::Stitcher::PANORAMA;
                std::string input_image_path1  = "/home/zhen/image_stitching/image1_undistorted.jpg";
                std::string input_image_path2  = "/home/zhen/image_stitching/image2_undistorted.jpg";

                cv::Mat pano;
                std::vector<cv::Mat> images_to_stitch;
                cv::Mat input_image1 = cv::imread(input_image_path1);
                //
                cv::Mat input_image2 = cv::imread(input_image_path2);
                //

                images_to_stitch.push_back(input_image2);
                images_to_stitch.push_back(input_image1);


                cv::Ptr<cv::Stitcher> stitcher = cv::Stitcher::create(mode);
                cv::Stitcher::Status status = stitcher->stitch(images_to_stitch, pano);
                cv::undistort(pano, undistorted_pano, camera_matrix, distortion_coefficients);
                cv::imwrite("undistorted_stitched.jpg", undistorted_pano);

                if (status == cv::Stitcher::OK) {
                    std::cout<< "Stitching was successful " << "Index["<< i << "]"<<std::endl;
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

