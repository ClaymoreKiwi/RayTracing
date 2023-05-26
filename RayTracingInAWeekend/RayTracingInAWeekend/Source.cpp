#include "Vec3Class.h"
#include "ColourUtil.h"

int main()
{

    // Image

    const int image_width = 256;
    const int image_height = 256;

    // Render

    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    for (int j = image_height - 1; j >= 0; --j)
    {
        //use of cerr to keep cout free to print the colour
        std::cerr << "\rScanlines Remaining: " << j << ' ' << std::flush;
        for (int i = 0; i < image_width; ++i)
        {
            //use of alias to show where the colour is being printed
            colour pixel(double(i) / (image_width - 1), double(j) / (image_height - 1), 0.25);
            write_color(pixel);
        }
    }
    std::cerr << "\nDone.\n";
}