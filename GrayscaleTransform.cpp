# include <Siv3D.hpp> // OpenSiv3D v0.6.11

void GrayscaleTransform(Image& image_in, Image& image_out)
{
	for (int32 y = 0; y < image_in.height(); ++y)
	{
		for (int32 x = 0; x < image_in.width(); ++x)
		{
			Color in = image_in[y][x];
			Color& out = image_out[y][x];
			const uint8 brightness = (uint8)(in.r * 0.299 + in.g * 0.587 + in.b * 0.114);
			out.r = brightness;
			out.g = brightness;
			out.b = brightness;
			out.a = 255;
		}
	}
}

void GrayscaleTransform(Image& image_in)
{
	Image image_out(image_in.width(), image_in.height());
	GrayscaleTransform(image_in, image_out);
	image_in = image_out;
}

void Main()
{
	Image image(U"input.png");

	GrayscaleTransform(image);

	image.save(U"result.png");

	Texture texture(image);

	while (System::Update())
	{
		texture.draw();
	}
}
