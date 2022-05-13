#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_VisualLab2.h"


QT_BEGIN_NAMESPACE
namespace Ui {
	class VisualLab2Class;
} // namespace Ui

QT_END_NAMESPACE

#include <QGraphicsScene>  
#include <QGraphicsView>                   //graphicsview类
#include <opencv2\imgproc\imgproc.hpp>
#include <opencv2\core\core.hpp>
#include <opencv2\highgui\highgui.hpp>  //opencv申明
#include <qfiledialog.h>                //getopenfilename 类申明
#include <qlabel.h>                     //label类
#include "opencv2/imgproc/types_c.h"
//#include <opencv2\sfm\triangulation.hpp>


#include <vector>

#include <Eigen/SVD>  
#include <Eigen/Core>  
#include <Eigen/Dense>   

#include<iostream>
#include<fstream>
#include<iomanip>

//using namespace std;
using std::vector;
using namespace cv;
using namespace Eigen;
//using namespace Eigen::internal;
//using namespace Eigen::Architecture;

class VisualLab2 :  public QMainWindow
{
	Q_OBJECT

public:
	//friend class QWidget;
	//friend void QWidget::paintEvent(QPaintEvent *);
	VisualLab2(QWidget *parent = Q_NULLPTR);
	//VisualLab2();
	~VisualLab2();
	//int count = 0;
	//添加槽函数
private slots:

	void on_pushButton_clicked();
	
	//按格式on_控件名_clicked命名函数，QT会默认完成函数和按钮动作的链接，如果不这样命名的话就去设置信号槽函数
	void on_button_startCalculate_clicked();
	void on_button_firstMatrix_clicked();
	void on_button_secondMatrix_clicked();
	void on_button_matching_clicked();
	void on_button_3d_clicked();
private:
	Ui::VisualLab2Class ui;

	/*cv::Mat image;
	cv::Mat image2;
	cv::Mat image3;
	QLabel *label;
	QLabel *label_2;
	
	QPoint lastPos;
	vector<Point2f> firstImg;
	vector<Point2f> secondImg;
	cv::Mat F;
	float xoffset = 0;
	float xoffset2 = 0;
	float yoffset = 0;
	float yoffset2 = 0;

	int lRow = 0;  //Data collected on the left
	int rRow = 0;  //Data collected on the right
	Mat fundamental_matrix;
	vector<cv::Vec<float, 3>> epilines1, epilines2;

	//void paintEvent(QPaintEvent *event);



//To obtain position
protected:  //mouse
	void mousePressEvent(QMouseEvent *event);         
	void mouseReleaseEvent(QMouseEvent *event);

	

	void savePixelValues(QPoint point, QPoint point2);*/
	
	//void paintOnePolar(QPoint point);

	//void lookMatching();
	//void onMouse(int event, int x, int y, int flags, void* param);
};

void onMouse1(int event, int x, int y, int flags, void* ustc);
void onMouse2(int event, int x, int y, int flags, void* ustc);

void lookImgMatching();
void lookImg2Matching();

cv::Point pointMatching(cv::Point p, cv::Mat imageNumber, cv::Mat img, cv::Mat img2);

cv::Point getStraightLineAllPoint(int x0, int y0, int x1, int y1, cv::Point p, cv::Mat imageNumber, cv::Mat img, cv::Mat img2);

void drawRedCrossline(cv::Mat img9, cv::Point point);
void drawBlueCrossline(cv::Mat img9, cv::Point point);

void setA(float **A, float threeD[8][3], float twoD[8][2]);
float **matrix(int n1, int n2, int m1, int m2);

void outputArray(float array[][2], String str);
void outputArrayApp(float array[][2], String str, double meanerror);
void outputMatrixToFile(Matrix<float, Dynamic, Dynamic> v, String str);

double meanPixelError(float twoD[][2], float cal2D[][2], int n);
void calculate2Danother(float cal2D[8][2], Matrix<float, Dynamic, Dynamic> v, float threeD[8][3]);
Vector3d calculate3Dpoint(float m[][4], float n[][4], float x, float y, float x1);