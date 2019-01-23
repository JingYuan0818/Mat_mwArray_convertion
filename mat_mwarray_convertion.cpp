mwArray mat2mwArray(const Mat imgSrc)
{
	
	int h, w, c;
	h = imgSrc.rows;
	w = imgSrc.cols;
	c = imgSrc.channels();

	//cout << h << endl;
	//cout << w << endl;

	if (c == 1) // gray image
	{

		mwSize dims[2] = { h, w };
		mwArray pMat(2, dims, mxUINT8_CLASS);

		Mat t = imgSrc.t();
		UINT8* x = (UINT8*)t.data;

		cout << t.rows << endl;
		cout << t.cols << endl;

		pMat.SetData(x, h*w);

		return pMat;
	}

	else if (c == 3) // 3-channel image
	{
		mwSize dims[3] = { h, w, c };
		mwArray pMat(3, dims, mxUINT8_CLASS);

		for (int r = 0; r < h; ++r)
		{
			for (int c = 0; c < w; ++c)
			{
				pMat(r + 1, c + 1, 1) = (UINT8)imgSrc.at<Vec3b>(r, c)[2];
				pMat(r + 1, c + 1, 2) = (UINT8)imgSrc.at<Vec3b>(r, c)[1];
				pMat(r + 1, c + 1, 3) = (UINT8)imgSrc.at<Vec3b>(r, c)[0];

			}
		}

		return pMat;
	}
	
}
Mat mwArray2mat(const mwArray data)
{
	mwArray dims = data.GetDimensions();
	//cout << dims(1) << endl;


	int n = data.NumberOfDimensions();
	int M = dims(1);
	int N = dims(2);
	if (n == 2)
	{
		int h = M;
		int w = N;
		cv::Mat image(h, w, CV_8UC1);




		for (int i = 0; i < h; i++)
		{
			for (int j = 0; j < w; j++)
			{
				int index = data(i+1, j+1);
				image.row(i).col(j).data[0] = index;
			}
		}

		return image;
	}
	else if (n == 3)
	{
		int h = M;
		int w = N;
		int c = dims(3);
		
		cv::Mat image(h, w, CV_8UC3);
		for (int i = 0; i < h; i++)
		{
			for (int j = 0; j < w; j++)
			{

				image.row(i).col(j).data[0] = data(i+1, j + 1, 3);
				image.row(i).col(j).data[1] = data(i+1, j + 1, 2);
				image.row(i).col(j).data[2] = data(i+1, j + 1, 1);

			}
		}
		return image;
	}

}
