# include <Siv3D.hpp> // OpenSiv3D v0.6.11

void Binarize(Image& image_in, Image& image_out, uint8 threshold = 128)
{
	for (int32 y = 0; y < image_in.height(); ++y)
	{
		for (int32 x = 0; x < image_in.width(); ++x)
		{
			Color in = image_in[y][x];
			Color& out = image_out[y][x];

			if (in.r < threshold)
				out.r = 0;
			else
				out.r = 255;

			if (in.g < threshold)
				out.g = 0;
			else
				out.g = 255;

			if (in.b < threshold)
				out.b = 0;
			else
				out.b = 255;

			out.a = 255;
		}
	}
}

void Binarize(Image& image_in, uint8 threshold = 128)
{
	Image image_out(image_in.width(), image_in.height());
	Binarize(image_in, image_out, threshold);
	image_in = image_out;
}

void Main()
{
	Image image(U"input.png");

	Binarize(image);

	image.save(U"result.png");

	Texture texture(image);

	while (System::Update())
	{
		texture.draw();
	}
}
