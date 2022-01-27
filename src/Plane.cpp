#include "Plane.h"
#include "Ray.h"
#include <iostream>
bool Plane::intersect(
  const Ray & ray, const double min_t, double & t, Eigen::Vector3d & n) const
{ 
  // copy vectors for ease of readability
  Eigen::Vector3d p = this->point;
  Eigen::Vector3d norm = this->normal;
  Eigen::Vector3d e = ray.origin;
  Eigen::Vector3d d = ray.direction;

  // calculate t (equation acquired from tutorial slides)
  double temp_t = (p-e).dot(norm) / (d.dot(norm));

  // valid intersection if the hit location is greater than min t
  if (temp_t >= min_t){
    t = temp_t;
    n = norm;
    return true;
  } else {
    return false;
  }
}

