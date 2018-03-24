#include"ImgBit.h"
ImgBit::ImgBit(short r, short g, short b)
{
	red = r;
	green = g;
	blue = b;
}
ImgBit ImgBit::operator +(const ImgBit& temp)
{
	ImgBit result(red + temp.red, green + temp.green, blue + temp.blue);
	return result;
}
ImgBit ImgBit::operator /(int n)
{
	ImgBit result(red / n, green / n, blue / n);
	return result;
}