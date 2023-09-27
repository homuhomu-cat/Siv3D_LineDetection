# include <Siv3D.hpp> // OpenSiv3D v0.6.11

void GaussianFilter3x3(Image& image_in, Image& image_out)
{
	constexpr int32 kernel[3][3] =
	{
		{1,2,1},
		{2,4,2},
		{1,2,1}
	};

	for (int32 y = 0; y < image_in.height(); ++y)
	{
		for (int32 x = 0; x < image_in.width(); ++x)
		{
			Color& out = image_out[y][x];
			double value_r = 0;
			double value_g = 0;
			double value_b = 0;

			for (int32 i = -1; i <= 1; ++i)
			{
				const int32 y_ = (y + i < 0 || y + i >= image_in.height()) ? y : y + i;
				for (int32 j = -1; j <= 1; ++j)
				{
					const int32 x_ = (x + j < 0 || x + j >= image_in.height()) ? x : x + j;
					Color& in = image_in[y_][x_];

					value_r += in.r * (kernel[i + 1][j + 1] / 16.0);
					value_g += in.g * (kernel[i + 1][j + 1] / 16.0);
					value_b += in.b * (kernel[i + 1][j + 1] / 16.0);
				}
			}

			out.r = (uint8)value_r;
			out.g = (uint8)value_g;
			out.b = (uint8)value_b;
			out.a = 255;
		}
	}
}

void GaussianFilter3x3(Image& image_in)
{
	Image image_out(image_in.width(), image_in.height());
	GaussianFilter3x3(image_in, image_out);
	image_in = image_out;
}

void Main()
{
	Image image(U"input.png");

	GaussianFilter3x3(image);

	image.save(U"result.png");

	Texture texture(image);

	while (System::Update())
	{
		texture.draw();
	}
}
