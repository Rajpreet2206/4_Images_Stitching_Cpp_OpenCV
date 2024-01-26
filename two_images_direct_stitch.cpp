#include "opencv2/highgui/highgui.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/opencv.hpp"

using namespace cv;

int main(int argc, char* argv[]){
    VideoCapture cap1(0);
    VideoCapture cap2(2);
    cap1.set(CAP_PROP_FPS, 30);
    cap2.set(CAP_PROP_FPS, 30);
    namedWindow("Frame1", WINDOW_AUTOSIZE);
    namedWindow("Frame2", WINDOW_AUTOSIZE);

while(1)
    {
        cv::Mat frame1, frame2;
        cap1 >> frame1;
        cap2 >> frame2;

        cv::imshow("Frame1", frame1);
        cv::imshow("Frame2", frame2);

        if (waitKey(30) == 's')
            {
                for(int i=0; i<1; i++){
                    cv::Stitcher::Mode mode = cv::Stitcher::PANORAMA;
                    cv::Mat pano;
                    std::vector<cv::Mat> frames_to_stitch;
                    frames_to_stitch.push_back(frame1);
                    frames_to_stitch.push_back(frame2);

                    cv::Ptr<cv::Stitcher> stitcher = cv::Stitcher::create(mode);
                    cv::Stitcher::Status status = stitcher->stitch(frames_to_stitch, pano);
                    if(status == cv::Stitcher::OK){
                        std::cout<< "Stitching was successful, Index [" << i << "]" << std::endl;
                        std::string filename = "stitcher_directly_" + std::to_string(i) + ".jpg";
                        cv::imwrite(filename, pano);
                        cv::imshow("Stitched", pano);
                    }
                    else if(status == cv::Stitcher::ERR_NEED_MORE_IMGS){
                        std::cout<<"More images required for stitching, Index [" << i << "]" << std::endl;
                    }
                    else if(status == cv::Stitcher::ERR_HOMOGRAPHY_EST_FAIL){
                        std::cout<<"Camera Parameter Adjustment Failed, Index [" << i << "]" << std::endl; 
                    }
                    else {
                        std::cout<< "Moving to the next stitching " << i+1 << std::endl;
                    }
                    //cv::imshow("Stitched", pano);
                
                }

            }

    }
    return 0;
}