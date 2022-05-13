#include "VisualProcessing.h"
#include "opencv2/calib3d/calib3d.hpp"
#include <QMouseEvent>
#include <iostream>
#include "qlabel.h"



using namespace cv;
//using namespace std;
using std::string;

cv::Mat image;
cv::Mat image2;
cv::Mat image11;
cv::Mat image21;
QLabel *label;
QLabel *label_2;

QPoint lastPos;
vector<Point2f> firstImg;
vector<Point2f> secondImg;
cv::Mat F;
float xoffset = 0;
//float xoffset2 = 0;
float yoffset = 0;
//float yoffset2 = 0;

int lRow = 0;  //Data collected on the left
int rRow = 0;  //Data collected on the right

vector<cv::Vec<float, 3>> epilines1, epilines2;

int choice = 0;

Mat fundamental_matrix = (Mat_<double>(3, 3) << 4.021368e-07, 5.841629e-05, -1.727590e-02,
	-6.705804e-05, -7.098293e-07, 4.999593e-02,
	1.981079e-02, -5.404245e-02, 9.969398e-01);

float threeD[8][3] = { 0, 1.5, 3.8,
0, 22.5, 3.8 ,
0, 22.5, 18.8 ,
0, 1.5, 18.8 ,
24.3, 0, 3.8 ,
3.3, 0, 3.8 ,
3.3, 0, 18.8 ,
24.3, 0, 18.8 };

float firstProjection[3][4] = { 0 };
float secondProjection[3][4] = { 0 };



VisualLab2::VisualLab2(QWidget *parent)
	: QMainWindow(parent)
//VisualLab2::VisualLab2(QWidget *parent)

{

	ui.setupUi(this);

	//this->setMouseTracking(true);
}

VisualLab2::~VisualLab2()
{

}

void VisualLab2::on_pushButton_clicked()
{
	String str = "G://0E_Document//MAC-Intersummer202105//Visual Processing//pictures//im1.jpeg";
	image = imread(str);
	//image=imread(fileName.toLatin1().data);
	//cvtColor(image2, image2, CV_BGR2RGB);
	//cv::resize(image, image, Size(520, 500));

	image11 = imread(str);
	//cv::resize(image11, image11, Size(520, 500));

	imshow("image1", image);

	String str2 = "G://0E_Document//MAC-Intersummer202105//Visual Processing//pictures//im2.jpeg";
	image2 = imread(str2);
	//image=imread(fileName.toLatin1().data);
	//cvtColor(image2, image2, CV_BGR2RGB);
	//cv::resize(image2, image2, Size(520, 500));

	image21 = imread(str2);
	//cv::resize(image21, image21, Size(520, 500));

	imshow("image2", image2);


	waitKey();


}

void VisualLab2::on_button_startCalculate_clicked()
{
	choice = 0;
	cv::setMouseCallback("image1", onMouse1, 0);
	cv::setMouseCallback("image2", onMouse2, 0);
	waitKey();
}

void VisualLab2::on_button_firstMatrix_clicked()
{
	if (firstImg.size() == 8)
	{
		float twoD[8][2] = { 0 };
		
		for (int i = 0; i < 8; i++)
		{
			twoD[i][0] = firstImg[i].x;
			twoD[i][1] = firstImg[i].y;
		}
		float **A;
		A = matrix(1, 16, 1, 12);              //an 54X12 matrix


		setA(A, threeD, twoD);         //Use the data in 3D and 2D files to get Matrix A

		MatrixXf AA(16, 12);
		//MatrixXf S(12, 1);
		for (int i = 1; i <= 16; i++)
		{
			for (int j = 1; j <= 12; j++)
			{
				AA(i - 1, j - 1) = A[i][j];
			}
		}

		JacobiSVD<MatrixXf> svd(AA, ComputeThinU | ComputeThinV);
		//std::cout << "eigenvalues:" << std::endl;
		//S = svd.singularValues();

		//ui.textEdit->insertPlainText(tr("Left number: %1\n").arg(++lRow));
		//ui.textEdit->moveCursor(QTextCursor::Start);
		Matrix<float, Dynamic, Dynamic> v = svd.matrixV();
		
		
		float cal2D[8][2] = { 0 };
		calculate2Danother(cal2D, v, threeD);         //calculate array cal2D based on 3D data and M
		double meanError = meanPixelError(twoD, cal2D, 8);     //average pixel error


		for (int i = 0, k=0; i < 3; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				firstProjection[i][j] = v(k, 11);
				k++;
			}
		}

		outputArray(twoD, "../Image1-2D-8points.txt");
		outputArrayApp(cal2D, "../Image1-2D-8points.txt", meanError);
		outputMatrixToFile(v, "../Image1-ProjectionMatrix.txt");
	}

}

void VisualLab2::on_button_secondMatrix_clicked()
{
	if (secondImg.size() == 8)
	{
		float twoD[8][2] = { 0 };

		for (int i = 0; i < 8; i++)
		{
			twoD[i][0] = secondImg[i].x;
			twoD[i][1] = secondImg[i].y;
		}
		float **A;
		A = matrix(1, 16, 1, 12);              //an 54X12 matrix


		setA(A, threeD, twoD);         //Use the data in 3D and 2D files to get Matrix A

		MatrixXf AA(16, 12);
		//MatrixXf S(12, 1);
		for (int i = 1; i <= 16; i++)
		{
			for (int j = 1; j <= 12; j++)
			{
				AA(i - 1, j - 1) = A[i][j];
			}
		}

		JacobiSVD<MatrixXf> svd(AA, ComputeThinU | ComputeThinV);
		//std::cout << "eigenvalues:" << std::endl;
		//S = svd.singularValues();

		//ui.textEdit->insertPlainText(tr(S));
		//ui.textEdit->moveCursor(QTextCursor::Start);
		Matrix<float, Dynamic, Dynamic> v = svd.matrixV();


		float cal2D[8][2] = { 0 };
		calculate2Danother(cal2D, v, threeD);         //calculate array cal2D based on 3D data and M
		double meanError = meanPixelError(twoD, cal2D, 8);     //average pixel error

		for (int i = 0, k = 0; i < 3; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				secondProjection[i][j] = v(k, 11);
				k++;
			}
		}

		outputArray(twoD, "../Image2-2D-8points.txt");
		outputArrayApp(cal2D, "../Image2-2D-8points.txt", meanError);
		outputMatrixToFile(v, "../Image2-ProjectionMatrix.txt");
	}
}

void VisualLab2::on_button_matching_clicked()
{
	choice = 1;
	cv::setMouseCallback("image1", onMouse1, 0);
	cv::setMouseCallback("image2", onMouse2, 0);
	waitKey();
}

void VisualLab2::on_button_3d_clicked()
{
	choice = 2;
	cv::setMouseCallback("image1", onMouse1, 0);
	cv::setMouseCallback("image2", onMouse2, 0);
	waitKey();
}

void onMouse1(int event, int x, int y, int flags, void* ustc)
{
	if (event == EVENT_LBUTTONDOWN)
	{
		CvPoint pt = cvPoint(x, y);
		firstImg.push_back(pt);
		circle(image, pt, 2, (0, 255, 255), 2);
		imshow("image1", image);
		if (!fundamental_matrix.empty()&&(choice == 1 ||choice == 2))
		{
			//firstImg.push_back(Point2f((ui.leftlabel->mapFromGlobal(point)).x() - xoffset, (ui.leftlabel->mapFromGlobal(point)).y() - yoffset));
			int k = firstImg.size();
			circle(image, firstImg[k - 1], 2, (255, 0, 0, 255), 2);
			computeCorrespondEpilines(firstImg, 1, fundamental_matrix, epilines1);
			line(image2, cv::Point(0, -epilines1[k - 1][2] / epilines1[k - 1][1]), Point(image2.cols, -(epilines1[k - 1][2] + epilines1[k - 1][0] * image2.cols) / epilines1[k - 1][1]), (255, 0, 0, 255), 1);

			//cv::Point p = firstImg[k - 1];
			//cv::Point matchLoc = pointMatching(pt, image2, image11, image21);
			cv::Point matchLoc2 = getStraightLineAllPoint(0, -epilines1[k - 1][2] / epilines1[k - 1][1], image2.cols, -(epilines1[k - 1][2] + epilines1[k - 1][0] * image2.cols) / epilines1[k - 1][1], pt, image2, image11, image21);
			if (choice == 2)
			{
				char temp[500];
				//cv::Point3d pt3d;
				//sfm::triangulatePoints(pt,firstProjection,pt3d);
				/*Vector3d R = calculate3Dpoint(firstProjection, secondProjection, pt.x,pt.y, matchLoc.x);
				
				sprintf(temp, "(%d,%d,%d)", int(R(0) + 0.5), int(R(1) + 0.5), int(R(2) + 0.5));
				

				putText(image2, temp, matchLoc, cv::FONT_HERSHEY_DUPLEX, 0.5, cv::Scalar(255, 255, 255), 1);*/

				Vector3d R2 = calculate3Dpoint(firstProjection, secondProjection,  pt.x, pt.y, matchLoc2.x);
				sprintf(temp, "(%d,%d,%d)", int(R2(0)+0.5), int(R2(1) + 0.5), int(R2(2) + 0.5)); //R(0), R(1), R(2));
				putText(image2, temp, matchLoc2, cv::FONT_HERSHEY_DUPLEX, 0.5, cv::Scalar(255, 255, 255), 1);

			}
			imshow("image2", image2);
		
		}
		
	}
}

void onMouse2(int event, int x, int y, int flags, void* ustc)
{
	if (event == EVENT_LBUTTONDOWN)
	{
		CvPoint pt = cvPoint(x, y);
		secondImg.push_back(pt);
		circle(image2, pt, 2, (0, 255, 255), 2);
		imshow("image2", image2);
		//imshow("image22", image21);
		if (!fundamental_matrix.empty() && (choice == 1 || choice == 2))
		{
			int k = secondImg.size();
			circle(image2, secondImg[k - 1], 2, (255, 0, 0, 255), 2);
			//circle(image2, pt, 2, (255, 0, 0, 255), 2);
			computeCorrespondEpilines(secondImg, 2, fundamental_matrix, epilines2);
			line(image, cv::Point(0, -epilines2[k - 1][2] / epilines2[k - 1][1]), Point(image.cols, -(epilines2[k - 1][2] + epilines2[k - 1][0] * image.cols) / epilines2[k - 1][1]), (255, 0, 0, 255), 1);

			//cv::Point p = secondImg[k - 1];
			//cv::Point matchLoc = pointMatching(pt, image, image21, image11);
			cv::Point matchLoc2 = getStraightLineAllPoint(0, -epilines2[k - 1][2] / epilines2[k - 1][1], image.cols, -(epilines2[k - 1][2] + epilines2[k - 1][0] * image.cols) / epilines2[k - 1][1], pt, image, image21, image11);
			if (choice == 2)
			{
				char temp[500];
				/*Vector3d R = calculate3Dpoint(secondProjection, firstProjection,  pt.x, pt.y, matchLoc.x);
				//R(0) = (int)(100.0 * R(0) + 0.5) / 100.0;
				//R(1) = (int)(100.0 * R(1) + 0.5) / 100.0;
				//R(2) = (int)(100.0 * R(2) + 0.5) / 100.0;
				
				sprintf(temp, "(%d,%d,%d)", int(R(0) + 0.5), int(R(1) + 0.5), int(R(2) + 0.5)); //R(0), R(1), R(2));
				//String temp = String(R(0));
				putText(image, temp, matchLoc, cv::FONT_HERSHEY_DUPLEX, 0.5, cv::Scalar(255, 255, 255), 1);*/

				Vector3d R2 = calculate3Dpoint(secondProjection, firstProjection, pt.x, pt.y, matchLoc2.x);
				sprintf(temp, "(%d,%d,%d)", int(R2(0) + 0.5), int(R2(1) + 0.5), int(R2(2) + 0.5)); //R(0), R(1), R(2));
				putText(image, temp, matchLoc2, cv::FONT_HERSHEY_DUPLEX, 0.5, cv::Scalar(255, 255, 255), 1);
			}
			
			imshow("image1", image);
		}
		
	}
}

//在第一个图上选择，在第二个图上显示
void lookImgMatching()
{
	int k = firstImg.size();
	cv::Point p = firstImg[k - 1];
	pointMatching(p, image2, image11, image21);
}

void lookImg2Matching()
{
	int k = secondImg.size();
	cv::Point p = secondImg[k - 1];
	pointMatching(p, image, image21, image11);
}


cv::Point pointMatching(cv::Point p, cv::Mat imageNumber, cv::Mat img, cv::Mat img2)
{
	//int k = imgPoints.size();
	//cv::Point p = imgPoints[k - 1];

	int offsetX = 20;
	int offsetY = 20;
	int sideLength = 2*offsetX;

	p.x = p.x - offsetX;
	p.y = p.y - offsetY;
	if (p.x < 0)
	{
		offsetX = offsetX + p.x;
		p.x = 0;
	}
	if (p.y < 0)
	{
		offsetY = offsetY + p.y;
		p.y = 0;
	}
	if (p.x + sideLength > imageNumber.cols)
	{
		offsetX = offsetX + p.x + sideLength - imageNumber.cols;
		p.x = imageNumber.cols - sideLength;
	}
	if (p.y + sideLength > imageNumber.rows)
	{
		offsetY = offsetY + p.y + sideLength - imageNumber.rows;
		p.y = imageNumber.rows - sideLength;
	}

	cv::Mat templateImage(img, cv::Rect(p, cv::Size(sideLength, sideLength)));
	//imshow("im", templateImage);

	p.x = p.x - 20;
	p.y = p.y - 20;
	if (p.x < 0) p.x = 0;
	if (p.y < 0) p.y = 0;
	if (p.x + 100 > imageNumber.cols) p.x = imageNumber.cols - 80;
	if (p.y + 100 > imageNumber.rows) p.y = imageNumber.rows - 80;

	cv::Mat testimg(img2, cv::Rect(p, cv::Size(80, 80)));
	

	/*p.x = 0;
	p.y = 0;
	cv::Mat testimg = img2;*/
	//imshow("im2", testimg);

	int result_cols = testimg.cols - templateImage.cols + 1;
	int result_rows = testimg.rows - templateImage.rows + 1;

	cv::Mat result = cv::Mat(result_cols, result_rows, CV_32FC1);
	//cv::matchTemplate( testimg, templateImage, result, CV_TM_SQDIFF);  
	cv::matchTemplate(testimg, templateImage, result, CV_TM_CCOEFF_NORMED);

	double minVal, maxVal;
	cv::Point minLoc, maxLoc, matchLoc;
	cv::minMaxLoc(result, &minVal, &maxVal, &minLoc, &maxLoc, Mat());
	//matchLoc = minLoc;		//CV_TM_SQDIFF
	matchLoc = maxLoc;        //CV_TM_CCOEFF_NORMED
	matchLoc.x = p.x + matchLoc.x + offsetX;
	matchLoc.y = p.y + matchLoc.y + offsetY;


	drawRedCrossline(imageNumber, matchLoc);
	//cv::rectangle(image, cv::Rect(matchLoc, cv::Size(templateImage.cols, templateImage.rows)), Scalar(0, 0, 255), 2, 8, 0);
	return matchLoc;
}

cv::Point getStraightLineAllPoint(int x0, int y0, int x1, int y1, cv::Point p, cv::Mat imageNumber, cv::Mat img, cv::Mat img2)
{
	//////////////////////取点击图像的区域
	int offsetX = 25;
	int offsetY = 25;
	int sideLength = 2 * offsetX;

	p.x = p.x - offsetX;
	p.y = p.y - offsetY;
	if (p.x < 0)
	{
		offsetX = offsetX + p.x;
		p.x = 0;
	}
	if (p.y < 0)
	{
		offsetY = offsetY + p.y;
		p.y = 0;
	}
	if (p.x + sideLength > imageNumber.cols)
	{
		offsetX = offsetX + p.x + sideLength - imageNumber.cols;
		p.x = imageNumber.cols - sideLength;
	}
	if (p.y + sideLength > imageNumber.rows)
	{
		offsetY = offsetY + p.y + sideLength - imageNumber.rows;
		p.y = imageNumber.rows - sideLength;
	}
	
	cv::Mat templateImage(img, cv::Rect(p, cv::Size(sideLength, sideLength)));
	//imshow("tem", templateImage);
	/////////////沿极线切割图像

	
	Mat dst;
	Mat roi = Mat::zeros(img2.size(), CV_8U);

	vector<vector<Point>> contour;
	vector<Point> pts;

	double a = 0, b = 0, h;
	b = y0;
	a = (y1 - b) / x1;
	int b1 = b - sideLength;
	int b2 = b + sideLength;

	if (b1 < 0 && b2 > 0)
	{
		pts.push_back(Point(0, 0));
		pts.push_back(Point(-b1 / a, 0));
	}
	else if (b1< imageNumber.rows && b2>imageNumber.rows)
	{
		pts.push_back(Point(0, imageNumber.rows));
		pts.push_back(Point(0, b1));
	}
	else if (b1 < 0)
	{
		pts.push_back(Point(-b1 / a, 0));
	}
	else if (b1 > 0 && b1 < imageNumber.rows)
	{
		pts.push_back(Point(0, b1));
	}
	else if (b1 > imageNumber.rows)
	{
		pts.push_back(Point((imageNumber.rows - b1) / a, imageNumber.rows));
	}

	if (y1 - sideLength < 0 && y1 + sideLength > 0)
	{
		pts.push_back(Point(-b1 / a, 0));
		pts.push_back(Point(imageNumber.cols, 0));
		pts.push_back(Point(imageNumber.cols, y1 + sideLength));
	}
	else if (y1 - sideLength < imageNumber.rows && y1 + sideLength > imageNumber.rows)
	{
		pts.push_back(Point(imageNumber.cols, y1 - sideLength));
		pts.push_back(Point(imageNumber.cols, imageNumber.rows));
		pts.push_back(Point((imageNumber.rows - b2) / a, imageNumber.rows));
	}
	else if (y1 - sideLength < 0 && y1 + sideLength < 0)
	{
		pts.push_back(Point(-b1 / a, 0));
		pts.push_back(Point(-b2 / a, 0));
	}
	else if (y1 - sideLength > 0 && y1 - sideLength < imageNumber.rows &&y1 + sideLength > 0 && y1 + sideLength < imageNumber.rows)
	{
		pts.push_back(Point(imageNumber.cols, y1 - sideLength));
		pts.push_back(Point(imageNumber.cols, y1 + sideLength));
	}
	else if (y1 - sideLength > imageNumber.rows && y1 + sideLength > imageNumber.rows)
	{
		pts.push_back(Point((imageNumber.rows - b1) / a, imageNumber.rows));
		pts.push_back(Point((imageNumber.rows - b2) / a, imageNumber.rows));
	}

	if (b + sideLength < 0)
	{
		pts.push_back(Point(-b2 / a, 0));
	}
	else if (b + sideLength > 0 && b + sideLength < imageNumber.rows)
	{
		pts.push_back(Point(0, b2));
	}
	else if (b + sideLength > imageNumber.rows)
	{
		pts.push_back(Point((imageNumber.rows - b2) / a, imageNumber.rows));
	}

	contour.push_back(pts);

	drawContours(roi, contour, 0, Scalar::all(255), -1);
	img2.copyTo(dst, roi);
	
	cv::Mat testimg = dst;
	//imshow("test", testimg);

	int result_cols = testimg.cols - templateImage.cols + 1;
	int result_rows = testimg.rows - templateImage.rows + 1;

	cv::Mat result = cv::Mat(result_cols, result_rows, CV_32FC1);
	//cv::matchTemplate(testimg, templateImage, result, CV_TM_SQDIFF);
	cv::matchTemplate(testimg, templateImage, result, CV_TM_CCOEFF_NORMED);

	double minVal, maxVal;
	cv::Point minLoc, maxLoc, matchLoc;
	cv::minMaxLoc(result, &minVal, &maxVal, &minLoc, &maxLoc, Mat());
	//matchLoc = minLoc;
	matchLoc = maxLoc;

	matchLoc.x = matchLoc.x + offsetX;
	matchLoc.y = matchLoc.y + offsetY;


	drawBlueCrossline(imageNumber, matchLoc);

	return matchLoc;

}

void drawRedCrossline(cv::Mat img9, cv::Point point)
{

	line(img9, cvPoint(point.x - 4, point.y), cvPoint(point.x + 4, point.y), Scalar(0, 0, 255), 2, 8, 0);
	//绘制竖线
	line(img9, cvPoint(point.x, point.y - 4), cvPoint(point.x, point.y + 4), Scalar(0,  0, 255), 2, 8, 0);

}

void drawBlueCrossline(cv::Mat img9, cv::Point point)
{
	line(img9, cvPoint(point.x - 4, point.y), cvPoint(point.x + 4, point.y), Scalar(0, 255, 0), 2, 8, 0);
	//绘制竖线
	line(img9, cvPoint(point.x, point.y - 4), cvPoint(point.x, point.y + 4), Scalar(0, 255, 0), 2, 8, 0);

}

void setA(float **A, float threeD[8][3], float twoD[8][2])		//Use the data in 3D and 2D files to get Matrix A
{
	int y = -1;
	for (int i = 1; i <= 16; i++)
	{
		y = i % 2;
		if (y == 1)
		{
			for (int j = 1; j <= 12; j++)
			{
				if (j <= 3)
				{
					A[i][j] = 0 - threeD[(i - 1) / 2][j - 1];
				}
				else if (j == 4)
				{
					A[i][4] = -1;
				}
				else if (j >= 5 && j <= 8)
				{
					A[i][j] = 0;
				}
				else if (j >= 9 && j <= 11)
				{
					A[i][j] = twoD[(i - 1) / 2][0] * threeD[(i - 1) / 2][j - 9];
				}
				else if (j == 12)
				{
					A[i][j] = twoD[(i - 1) / 2][0];
				}
			}
		}
		else if (y == 0)
		{
			for (int j = 1; j <= 12; j++)
			{
				if (j <= 4)
				{
					A[i][j] = 0;
				}
				else if (j >= 5 && j <= 7)
				{
					A[i][j] = 0 - threeD[(i - 2) / 2][j - 5];
				}
				else if (j == 8)
				{
					A[i][8] = -1;
				}
				else if (j >= 9 && j <= 11)
				{
					A[i][j] = twoD[(i - 2) / 2][1] * threeD[(i - 2) / 2][j - 9];
				}
				else if (j == 12)
				{
					A[i][j] = twoD[(i - 2) / 2][1];
				}
			}
		}
	}

}

float **matrix(int n1, int n2, int m1, int m2) {
	/* create a matrix, for example matrix (1, 3, 1, 4); */
	float **mat;
	int i;

	mat = (float **)malloc((n2 - n1 + 1) * sizeof(float*));

	mat -= n1;

	for (i = n1; i <= n2; i++)
	{
		mat[i] = (float *)malloc((m2 - m1 + 1) * sizeof(float));
		mat[i] -= m1;
	}

	return(mat);
}

void outputArray(float array[][2], String str)  //output matrix A to A.txt
{
	std::ofstream outfile(str, std::ios::trunc);
	outfile << "Mouse selected points:" << std::endl;
	for (int i = 0; i < 8; i++)
	{
		outfile << i + 1 << "、(";
		for (int j = 0; j < 2; j++)
		{
			outfile << array[i][j] ;
			if (j == 0) outfile << " , ";
		}
		outfile << ")" << std::endl;
	}
	outfile << std::endl;
	outfile.close();
}

void outputArrayApp(float array[][2], String str, double meanerror)  //output matrix A to A.txt
{
	std::ofstream outfile(str, std::ios::app);
	outfile << "The calculated points:" << std::endl;
	for (int i = 0; i < 8; i++)
	{
		outfile << i + 1 << "、(";
		for (int j = 0; j < 2; j++)
		{
			outfile << array[i][j] ;
			if (j == 0) outfile << " , ";
		}
		outfile << ")" << std::endl;
	}
	outfile << std::endl <<"Mean error:"<<std::endl;
	outfile << meanerror;
	outfile.close();
}

void outputMatrixToFile(Matrix<float, Dynamic, Dynamic> v, String str)  //output matrix A to A.txt
{
	std::ofstream outfile(str, std::ios::trunc);
	
	outfile << v(0, 11) << " " << v(1, 11) << " " << v(2, 11) << " " << v(3, 11) << std::endl;
	outfile << v(4, 11) << " " << v(5, 11) << " " << v(6, 11) << " " << v(7, 11) << std::endl;
	outfile << v(8, 11) << " " << v(9, 11) << " " << v(10, 11) << " " << v(11, 11) << std::endl;
	
	outfile.close();
}

double meanPixelError(float twoD[][2], float cal2D[][2], int n)               //average pixel error and output
{
	double sumSqrt = 0;
	double first, second;
	for (int i = 0; i < n; i++)
	{
		first = pow((twoD[i][0] - cal2D[i][0]), 2);
		second = pow((twoD[i][1] - cal2D[i][1]), 2);
		sumSqrt = sumSqrt + sqrt(first + second);
	}

	//cout << "Mean pixel error: " << sumSqrt / n << endl;
	return sumSqrt / n;
}

void calculate2Danother(float cal2D[8][2], Matrix<float, Dynamic, Dynamic> v, float threeD[8][3])      //calculate array cal2D based on 3D data and M
{
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			if (j == 0)
			{
				cal2D[i][0] = (v(0, 11) * threeD[i][0] + v(1, 11)* threeD[i][1] + v(2, 11) * threeD[i][2] + v(3, 11)) /
					(v(8, 11) * threeD[i][0] + v(9, 11) * threeD[i][1] + v(10, 11) * threeD[i][2] + v(11, 11));
			}
			else if (j == 1)
			{
				cal2D[i][1] = (v(4, 11) * threeD[i][0] + v(5, 11) * threeD[i][1] + v(6, 11)* threeD[i][2] + v(7, 11)) /
					(v(8, 11) * threeD[i][0] + v(9, 11) * threeD[i][1] + v(10, 11) * threeD[i][2] + v(11, 11));
			}
			//cout << "v = " << (v(11, 8) * threeD[i][0] + v(11, 9) * threeD[i][1] + v(11, 10) * threeD[i][2] + v(11, 11)) << endl;
		}
	}
}

Vector3d calculate3Dpoint(float m[][4], float n[][4], float x, float y, float x1)
{
	float aa[3][3] = { 0 };

	aa[0][0] = x * m[2][0] - m[0][0];
	aa[0][1] = x * m[2][1] - m[0][1];
	aa[0][2] = x * m[2][2] - m[0][2];
	aa[1][0] = y * m[2][0] - m[1][0];
	aa[1][1] = y * m[2][1] - m[1][1];
	aa[1][2] = y * m[2][2] - m[1][2];
	aa[2][0] = x1 * n[2][0] - n[0][0];
	aa[2][1] = x1 * n[2][1] - n[0][1];
	aa[2][2] = x1 * n[2][2] - n[0][2];

	Matrix3d A;
	A << aa[0][0], aa[0][1], aa[0][2],
		aa[1][0], aa[1][1], aa[1][2],
		aa[2][0], aa[2][1], aa[2][2];

	float bb[3];
	bb[0] = m[0][3] - x * m[2][3];
	bb[1] = m[1][3] - y * m[2][3];
	bb[2] = n[0][3] - x1 * n[2][3];

	Vector3d B;
	B << bb[0], bb[1], bb[2];

	Vector3d R = A.colPivHouseholderQr().solve(B);

	//std::cout << R(0);
	return R;


}
