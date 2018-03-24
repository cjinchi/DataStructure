#pragma once

#include<string>
#include<vector>
#include"ImgBit.h"
using namespace std;

class PixImage
{
	vector<vector<ImgBit>> img;
	bool file_is_opened;

public:
	PixImage();
	bool load_img(string filename);
	bool Bluring(int n);
	bool Sobel();
	bool is_opened()const;
	bool save_img(string filename);
};