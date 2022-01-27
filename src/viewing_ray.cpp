#include "viewing_ray.h"

void viewing_ray(
  const Camera & camera,
  const int i,
  const int j,
  const int width,
  const int height,
  Ray & ray)
{   
    // equations acquired from textbook chapter 4
    ray.origin = camera.e;
    ray.direction = (-camera.d * camera.w + (-camera.width/2.0 + (camera.width*(j + 0.5))/width) * camera.u + (-camera.height/2.0 + (camera.height*(i + 0.5))/height) * -camera.v).normalized();
}

