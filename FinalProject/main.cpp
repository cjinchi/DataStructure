
#include<opencv2\core\core.hpp>
#include<opencv2\highgui\highgui.hpp>
using namespace cv;
#include<iostream>
using namespace std;
#include"PixImage.h"
#include<io.h>
#include"config.h"

int main()
{
	int num = 1;
	

	_finddata_t fileinfo;
	string src_path = SRC_PATH;
	string dest_path = DEST_PATH;
	string find_path = src_path+"//*";

	long file_long = _findfirst(find_path.c_str(), &fileinfo);
	_findnext(file_long, &fileinfo);
	while (_findnext(file_long, &fileinfo) == 0)
	{
		PixImage x;
		x.load_img(src_path + "//" + fileinfo.name);
		if (!x.is_opened())
		{
			cout << "ERROR" << endl;
			return -1;
		}
		//DO sth here
		if(DEST_PATH=="sobel")
			x.Sobel();
		else
			x.Bluring(6);
		x.save_img(dest_path + "//" + fileinfo.name);
		cout << "已处理" << num<<"张照片！" << endl;
		num++;
	}
	_findclose(file_long);
	
	return 0;

}