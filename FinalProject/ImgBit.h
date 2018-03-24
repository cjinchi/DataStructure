#pragma once
class ImgBit
{
	//unsigned char red;
	//unsigned char green;
	//unsigned char blue;
	short red;
	short green;
	short blue;
public:
	//ImgBit(unsigned char r, unsigned char g, unsigned char b);
	ImgBit(short r, short g, short b);
	ImgBit operator +(const ImgBit& temp);
	ImgBit operator /(int n);

	friend class PixImage;

};