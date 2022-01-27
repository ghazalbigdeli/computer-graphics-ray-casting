#include "Sphere.h"
#include "Ray.h"
#include <cmath>
bool Sphere::intersect(
  const Ray & ray, const double min_t, double & t, Eigen::Vector3d & n) const
{
  // copy vectors for easy of readability
  Eigen::Vector3d d = ray.direction;
  Eigen::Vector3d e = ray.origin;
  Eigen::Vector3d c = this->center;
  Eigen::Vector3d p;
  
  // all equations acquired from textbook chapter 4
  
  // solve quadtratic equation
  double discriminant = pow((d.dot(e - c)), 2) - d.dot(d) * ((e-c).dot(e-c) - pow(this->radius,2));

  // if discriminant is negative then there are no solutions
  if (discriminant < 0){
    return false;
  }

  double t_1 = (-d.dot(e-c) + sqrt(discriminant)) / (d.dot(d));
  double t_2 = (-d.dot(e-c) - sqrt(discriminant)) / (d.dot(d));

  // find the point that's closer (entering the sphere)
  if (std::min(t_1, t_2) < min_t){
    if (std::max(t_1, t_2) < min_t){
      return false;
    } else {
      t = std::max(t_1, t_2);
    }
  } else {
    t = std::min(t_1, t_2);
  }

  p = e + t * d;
  n = (p - c).normalized(); // normal vector

  return true;
}