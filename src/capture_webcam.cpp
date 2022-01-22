#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp>
#include <opencv2/objdetect.hpp>


int main(int argc, char * argv[])
{
  cv::Mat image;
  std::vector<cv::Point> bbox;
  cv::Mat rectifiedImage;

  cv::VideoCapture cap(0);
  cv::QRCodeDetector qrDecoder = cv::QRCodeDetector();
  std::string data;

  if (!cap.isOpened()) {
    std::cout << "cannot open camera";
    return -1;
  }

  while (true) {
    cap >> image;

    data = qrDecoder.detectAndDecode(image);

    if  (qrDecoder.detect(image,bbox)){
      std::cout << "detect" << std::endl;

      cv::Rect rRect(bbox[0], bbox[2]);
      cv::rectangle(image,rRect,100);
    }
    cv::imshow("Display window", image);
    if (!data.empty()) {
      std::cout << "Decoded Data : " << data << std::endl;
    }
    cv::waitKey(25);
  }

  return 0;
}