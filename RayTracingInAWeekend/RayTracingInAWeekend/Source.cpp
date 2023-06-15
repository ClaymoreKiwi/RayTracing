#include "mathutil.h"
#include "ColourUtil.h"
#include "HittableS.h"
#include "sphere.h"
#include "camera.h"

//hard code of sphere equasion - using quadratics to find where the ray has hit
double hit_sphere(const point3& center, double radius, const Ray& r)
{
    vec3 oc = r.Origin() - center;
    auto a = r.Direction().length_squared();
    auto half_b = dot(oc, r.Direction());
    auto c = oc.length_squared() - radius * radius;
    auto discriminant = half_b * half_b - a * c;

    if (discriminant < 0)
    {
        return -1.0;
    }
    else
    {
        return (-half_b - sqrt(discriminant)) / a;
    }
}

colour ray_colour(const Ray& r, const hittable& world)
{
    hit_record rec;
    if (world.hit(r, 0, infinity, rec))
    {
        return 0.5 * (rec.normal + colour(1, 1, 1));
    }
    vec3 unit_direction = unit_vector(r.Direction());
    auto t = 0.5 * (unit_direction.Y() + 1.0);
    return (1.0 - t) * colour(1.0, 1.0, 1.0) + t * colour(0.5, 0.7, 1.0);
}

int main()
{

    // Image
    const auto aspect_ratio = 16.0 / 9.0;
    const int image_width = 400;
    const int image_height = static_cast<int>(image_width/aspect_ratio);
    const int samples_per_pixel = 100;

    //world
    hittable_list world;
    world.add(std::make_shared<sphere>(point3(0, 0, -1), 0.5));
    world.add(std::make_shared<sphere>(point3(0, -100.5, -1), 100));

    //camera

    camera cam;

    // Render

    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    for (int j = image_height - 1; j >= 0; --j)
    {
        //use of cerr to keep cout free to print the colour
        std::cerr << "\rScanlines Remaining: " << j << ' ' << std::flush;
        for (int i = 0; i < image_width; ++i)
        {
            colour pixel_colour(0, 0, 0);
            for (int s = 0; s < samples_per_pixel; ++s)
            {
                auto u = (i + random_double()) / (image_width - 1);
                auto v = (j + random_double()) / (image_height - 1);
                Ray r = cam.get_ray(u, v);
                pixel_colour += ray_colour(r, world);
            }
            write_color(std::cout, pixel_colour, samples_per_pixel);
        }
    }
    std::cerr << "\nDone.\n";
}