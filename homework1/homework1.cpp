//homework main code
//opencv 4.1.1
//VS 2019
#include <iostream>
#include <fstream>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/imgproc/types_c.h>
#include <opencv2/core/core.hpp>
#include <highgui/highgui.hpp>
using namespace cv;
using namespace std;

int main()
{

	VideoCapture cap(0);	//open a camera
	//VideoCapture cap("*.avi");	//open a video file 
	if (!cap.isOpened())
	{
		cout << "Cannot open a camera or a video file!" << endl;
		return -1;
	}
	int width = 320;
	int height = 240;
	Size s(width, height);
	int fps = 15;
	VideoWriter writer = VideoWriter("test.avi", VideoWriter::fourcc('I', '4', '2', '0'), fps, s);
	//set width & height
	cap.set(CAP_PROP_FRAME_WIDTH, width);
	cap.set(CAP_PROP_FRAME_HEIGHT, height);
	Mat srcFrame;
	FILE* pFile;
	char yuvFileName[] = "test.yuv";
	fopen_s(&pFile, yuvFileName, "w+");
	int bufLength = width * height * 3 / 2;
	unsigned char* pYuvBuffer = new unsigned char[bufLength];
	if (!pFile)
	{
		cout << "pFile open error" << endl;
		return -1;
	}
	cout << "Press 'q' for quit" << endl;
	while (cap.isOpened())
	{
		cap >> srcFrame;
		
		if (srcFrame.empty())
			break;
		writer << srcFrame;
		imshow("frame", srcFrame);
		Mat yuvFrame;
		cvtColor(srcFrame, yuvFrame, CV_BGR2YUV_I420);
		memcpy(pYuvBuffer, yuvFrame.data, bufLength * sizeof(unsigned char));
		fwrite(pYuvBuffer, bufLength * sizeof(unsigned char), 1, pFile);
		if (waitKey(1000/fps) == 'q')
			break;//press 'q' for quit
	}
	fclose(pFile);
	delete[] pYuvBuffer;
	writer.release();
	cout << "Done!" << endl;
	return 0;
}


