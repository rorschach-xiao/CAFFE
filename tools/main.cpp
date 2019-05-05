#include <iostream>
#include "MTCNN.h"
#include "opencv2/opencv.hpp"
#include <time.h>

using namespace std;
using namespace cv;

int main() {

    vector<string> model_file = {
            "C:/Users/Ф��/caffe-windows/tools/model/det1.prototxt",
            "C:/Users/Ф��/caffe-windows/tools/model/det2.prototxt",
            "C:/Users/Ф��/caffe-windows/tools/model/det3.prototxt"
//            "../model/det4.prototxt"
    };

    vector<string> trained_file = {
            "C:/Users/Ф��/caffe-windows/tools/model/det1.caffemodel",
            "C:/Users/Ф��/caffe-windows/tools/model/det2.caffemodel",
            "C:/Users/Ф��/caffe-windows/tools/model/det3.caffemodel"
//            "../model/det4.caffemodel"
    };

    MTCNN mtcnn(model_file, trained_file);

    vector<Rect> rectangles;
    string img_path = "C:/Users/Ф��/caffe-windows/tools/result/pic2.jpg";
    Mat img = imread(img_path);

	int count = 1;
	unsigned start = time(NULL);
	for(int i=0; i < count; i++) {
		mtcnn.detection_TEST(img, rectangles);
	}
	unsigned end = time(NULL);
	unsigned ave = (end-start)*1000.0/count;
	std::cout << "Run " << count << " times, "<<"Average time:" << ave << std::endl; 

    return 0;
}

/*
 * 
int main() {


    //the vector used to input the address of the net model
    vector<string> model_file = {
            "../model/det1.prototxt",
            "../model/det2.prototxt",
            "../model/det3.prototxt"
//            "../model/det4.prototxt"
    };

    //the vector used to input the address of the net parameters
    vector<string> trained_file = {
            "../model/det1.caffemodel",
            "../model/det2.caffemodel",
            "../model/det3.caffemodel"
//            "../model/det4.caffemodel"
    };

    MTCNN mtcnn(model_file, trained_file);

//    VideoCapture cap(0);
    VideoCapture cap("../../0294_02_004_angelina_jolie.avi");

    VideoWriter writer;
    writer.open("../result/0294_02_004_angelina_jolie.avi",CV_FOURCC('M', 'J', 'P', 'G'), 25, Size(1280,720), true);

    Mat img;
    int frame_count = 0;
    while(cap.read(img))
    {
        vector<Rect> rectangles;
        vector<float> confidences;
        std::vector<std::vector<cv::Point>> alignment;
        mtcnn.detection(img, rectangles, confidences, alignment);

        for(int i = 0; i < rectangles.size(); i++)
        {
            int green = confidences[i] * 255;
            int red = (1 - confidences[i]) * 255;
            rectangle(img, rectangles[i], cv::Scalar(0, green, red), 3);
            for(int j = 0; j < alignment[i].size(); j++)
            {
                cv::circle(img, alignment[i][j], 5, cv::Scalar(255, 255, 0), 3);
            }
        }

        frame_count++;
        cv::putText(img, std::to_string(frame_count), cvPoint(3, 13),
                    cv::FONT_HERSHEY_COMPLEX_SMALL, 0.8, cvScalar(0, 255, 0), 1, CV_AA);
        writer.write(img);
        imshow("Live", img);
        waitKey(1);
    }

    return 0;
}


*/
