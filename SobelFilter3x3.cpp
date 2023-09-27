# include <Siv3D.hpp> // OpenSiv3D v0.6.11

void SobelFilter3x3(Image& image_in, Image& image_out)
{
	constexpr int32 kernel_v[3][3] =
	{
		{-1,0,1},
		{-2,0,2},
		{-1,0,1}
	};

	constexpr int32 kernelH[3][3] =
	{
		{-1,-2,-1},
		{0,0,0},
		{1,2,1}
	};


	for (int32 y = 0; y < image_in.height(); ++y)
	{
		for (int32 x = 0; x < image_in.width(); ++x)
		{
			Color& out = image_out[y][x];
			double value_r_v = 0;
			double value_g_v = 0;
			double value_b_v = 0;
			double value_r_h = 0;
			double value_g_h = 0;
			double value_b_h = 0;

			for (int32 i = -1; i <= 1; ++i)
			{
				const int32 y_ = (y + i < 0 || y + i >= image_in.height()) ? y : y + i;
				for (int32 j = -1; j <= 1; ++j)
				{
					const int32 x_ = (x + j < 0 || x + j >= image_in.height()) ? x : x + j;
					Color& in = image_in[y_][x_];

					value_r_v += in.r * kernel_v[i + 1][j + 1];
					value_g_v += in.g * kernel_v[i + 1][j + 1];
					value_b_v += in.b * kernel_v[i + 1][j + 1];

					value_r_h += in.r * kernelH[i + 1][j + 1];
					value_g_h += in.g * kernelH[i + 1][j + 1];
					value_b_h += in.b * kernelH[i + 1][j + 1];
				}
			}

			out.r = (uint8)Math::Sqrt(value_r_v * value_r_v + value_r_h * value_r_h);
			out.g = (uint8)Math::Sqrt(value_g_v * value_g_v + value_g_h * value_g_h);
			out.b = (uint8)Math::Sqrt(value_b_v * value_b_v + value_b_h * value_b_h);
			out.a = 255;
		}
	}
}

void SobelFilter3x3(Image& image_in)
{
	Image image_out(image_in.width(), image_in.height());
	SobelFilter3x3(image_in, image_out);
	image_in = image_out;
}

void Main()
{
	Image image(U"input.png");

	SobelFilter3x3(image);

	image.save(U"result.png");

	Texture texture(image);

	while (System::Update())
	{
		texture.draw();
	}
}
