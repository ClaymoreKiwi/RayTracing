#include "Vec3Class.h"
#include "ColourUtil.h"
#include "Ray.h"

//hard code of sphere equasion - using quadratics to find where the ray has hit
double hit_sphere(const point3& center, double radius, const Ray& r)
{
    vec3 oc = r.Origin() - center;
    auto a = dot(r.Direction(), r.Direction());
    auto b = 2.0 * dot(oc, r.Direction());
    auto c = dot(oc, oc) - radius * radius;
    auto discriminant = b * b - 4 * a * c;

    if (discriminant < 0)
    {
        return -1.0;
    }
    else
    {
        return (-b - sqrt(discriminant)) / (2.0 * a);
    }
}

colour ray_colour(const Ray& r)
{
    auto t = hit_sphere(point3(0, 0, -1), 0.5, r);
    if (t > 0.0)
    {
        vec3 N = unit_vector(r.at(t) - vec3(0,0,-1));
        return 0.5*colour(N.X()+1,N.Y()+1,N.Z()+1);
    }
    vec3 unit_direction = unit_vector(r.Direction());
    t = 0.5 * (unit_direction.Y() + 1.0);
    /*returns a colour vector depending on where it is cast on the screen
     (value 1 is representitive of the focal distance)*/
    return (1.0 - t) * colour(1.0, 1.0, 1.0) + t * colour(0.5, 0.7, 1.0);
    //ie: Blue indicates values furthest away and any blend into white is closer (white being closest)
}

int main()
{

    // Image
    const auto aspect_ratio = 16.0 / 9.0;
    const int image_width = 400;
    const int image_height = static_cast<int>(image_width/aspect_ratio);

    //camera

    auto viewport_height = 2.0;
    auto viewport_width = aspect_ratio * viewport_height;
    auto focal_length = 1.0;

    auto origin = point3(0, 0, 0);
    auto horizontal = vec3(viewport_width, 0, 0);
    auto vertical = vec3(0, viewport_height, 0);
    auto lower_left_corner = origin - horizontal / 2 - vertical / 2 - vec3(0, 0, focal_length);

    // Render

    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    for (int j = image_height - 1; j >= 0; --j)
    {
        //use of cerr to keep cout free to print the colour
        std::cerr << "\rScanlines Remaining: " << j << ' ' << std::flush;
        for (int i = 0; i < image_width; ++i)
        {
            auto u = double(i) / (image_width - 1);
            auto v = double(j) / (image_height - 1);
            Ray r(origin, lower_left_corner + u * horizontal + v * vertical - origin);
            //colour used to print the pixels, and ray passed in to dicate colour depending on distance
            colour pixel = ray_colour(r);
            write_color(pixel);
        }
    }
    std::cerr << "\nDone.\n";
}