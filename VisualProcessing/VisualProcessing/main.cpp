#include "VisualProcessing.h"
#include <QtWidgets/QApplication>
#include<opencv2/opencv.hpp>
#include<opencv2/highgui.hpp>
using namespace cv;

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	VisualLab2 w;
	w.setWindowTitle("Visual Processing");
	w.show();
	//cv::setMouseCallback("src", w.onMouse, 0);
	return a.exec();
}
