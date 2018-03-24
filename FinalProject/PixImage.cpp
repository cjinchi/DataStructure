#include"PixImage.h"
#include"config.h"
#include<iostream>
#include<fstream>
#include<cmath>
#include<assert.h>

#include<opencv2\core\core.hpp>
#include<opencv2\highgui\highgui.hpp>
using namespace cv;


PixImage::PixImage()
{
	file_is_opened = false;
}
bool PixImage::load_img(string filename)
{
	//�ú������ڶ�ȡ��Ƭ
	Mat imgmat = imread(filename);
	if (imgmat.empty())
	{
		file_is_opened = false;
		return false;
	}

	//����channelΪ3����Ƭ
	assert(imgmat.channels() == 3);

	int row = imgmat.rows;
	int col = imgmat.cols;

	//��Mat�ṹ�л�ȡͼƬ����
	for (int i = 0; i < row; i++)
	{
		vector<ImgBit> one_row;
		for (int j = 0; j < col; j++)
		{
			ImgBit bit(imgmat.ptr<uchar>(i)[j*3], imgmat.ptr<uchar>(i)[j*3 + 1], imgmat.ptr<uchar>(i)[j*3 + 2]);
			one_row.push_back(bit);
		}
		img.push_back(one_row);
	}
	file_is_opened = true;
	return true;
}

bool PixImage::Bluring(int n)
{
	if (n <= 1 ||!file_is_opened)
	{
		return false;
	}

	vector<vector<ImgBit>> temp(img);
	int row = img.size();
	int col = img[0].size();

	//��ĳһ����Ϊ���ģ������������ƫ��������nΪż��ʱ�������ϣ���ƫ�Ʊ����ң��£���ƫ��Сһ
	int dir1 = (n % 2 == 1 ? (n / 2) : (n / 2 - 1));
	int dir2 = n / 2;

	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			int left = j - dir1;
			int top = i - dir1;
			int right = j + dir2;
			int down = i + dir2;

			//�жϱ߽�
			left = (left < 0 ? 0 : left);
			top = (top < 0 ? 0 : top);
			right = (right < col ? right : col - 1);
			down = (down < row ? down : row - 1);

			ImgBit sum(0, 0, 0);
			for (int a = top; a <= down; a++)
			{
				for (int b = left; b <= right; b++)
				{
					//ImgBit������ ImgBit+ImgBit �� ImgBit/n ������ 
					sum = sum + temp[a][b];
				}
			}
			img[i][j] = sum / ((down - top + 1)*(right - left + 1));
		}
	}
	return true;
}
bool PixImage::Sobel()
{
	if (!file_is_opened)
	{
		return false;
	}

	int row = img.size();
	int col = img[0].size();

	double sum = 0;

	//ԭͼ����Ҷ�
	vector<vector<int>> gray;
	for (int i = 0; i < row; i++)
	{
		vector<int> one_row;
		for (int j = 0; j < col; j++)
		{
			int temp = (img[i][j].red * 299 + img[i][j].green * 587 + img[i][j].blue * 114 + 500) / 1000;
			sum += temp;
			one_row.push_back(temp);
		}
		gray.push_back(one_row);
	}

	vector<vector<int>> result;
	
	for (int i = 0; i < row; i++)
	{
		vector<int> one_row;
		for (int j = 0; j < col; j++)
		{
			//�߽�
			if (i == 0 || j == 0 || i == row - 1 || j == col - 1)
			{
				one_row.push_back(0);
				continue;
			}

			double gx = (gray[i + 1][j - 1] + 2 * gray[i + 1][j] + gray[i + 1][j + 1]) - (gray[i - 1][j - 1] + 2 * gray[i - 1][j] + gray[i - 1][j + 1]);
			double gy = (gray[i - 1][j - 1] + 2 * gray[i][j - 1] + gray[i + 1][j - 1]) - (gray[i - 1][j + 1] + 2 * gray[i][j + 1] + gray[i + 1][j + 1]);
			double g = sqrt(gx*gx + gy * gy);
			one_row.push_back(int(g));
		}
		result.push_back(one_row);
	}

	double mean = sum / (row*col);
	double cutoff = SCALE * mean;
	int thresh =(int) sqrt(cutoff);	//��ֵ

	ImgBit backgroud(BLACKGROUND, BLACKGROUND, BLACKGROUND);	//����
	ImgBit outline(OUTLINE, OUTLINE, OUTLINE);					//����
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			if (result[i][j]>thresh)
			{
				img[i][j] = outline;
			}
			else
			{
				img[i][j] = backgroud;
			}
		}
	}
	return true;


}

bool PixImage::save_img(string filename)
{
	//����ͼƬ

	if (!file_is_opened)
		return false;

	int row = img.size();
	int col = img[0].size();
	Mat temp(row,col, CV_8UC3);
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j <col; j ++)
		{
			temp.ptr<uchar>(i)[j*3] = img[i][j].red;
			temp.ptr<uchar>(i)[j*3 + 1] = img[i][j].green;
			temp.ptr<uchar>(i)[j*3 + 2] = img[i][j].blue;
		}
	}

	//namedWindow("result");
	//imshow("result", temp);
	//waitKey(0);
	return imwrite(filename, temp);
}
bool PixImage::is_opened()const
{
	return file_is_opened;
}