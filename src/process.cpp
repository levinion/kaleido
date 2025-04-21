#include <opencv2/opencv.hpp>
#include "kaleido/kaleido.hpp"

namespace kaleido {
cv::Mat process_image(cv::Mat src, float scale) {
  cv::Mat dst = cv::Mat(src.rows * scale, src.cols * scale, CV_8UC3);
  cv::resize(src, dst, dst.size(), cv::INTER_CUBIC);
  return dst;
}
} // namespace kaleido
