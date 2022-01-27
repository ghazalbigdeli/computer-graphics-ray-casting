#include "Triangle.h"
#include "Ray.h"
#include <Eigen/Geometry>

bool Triangle::intersect(
  const Ray & ray, const double min_t, double & t, Eigen::Vector3d & n) const
{
  Eigen::Matrix3f A;
  Eigen::Matrix3f beta_matrix;
  Eigen::Matrix3f gamma_matrix;
  Eigen::Matrix3f t_matrix;
  // copy vectors for ease of readability
  Eigen::Vector3d a = std::get<0>(this->corners);
  Eigen::Vector3d b = std::get<1>(this->corners);
  Eigen::Vector3d c = std::get<2>(this->corners);
  double A_determinant, gamma, beta;

  // all equations acquired from textbook chapter 4

  A << (a[0] - b[0]), (a[0] - c[0]), ray.direction[0], 
        (a[1] - b[1]), (a[1] - c[1]), ray.direction[1],
        (a[2] - b[2]), (a[2] - c[2]), ray.direction[2];

  A_determinant = A.determinant();

  beta_matrix << (a[0] - ray.origin[0]), (a[0] - c[0]), ray.direction[0],
                  (a[1] - ray.origin[1]), (a[1] - c[1]), ray.direction[1],
                  (a[2] - ray.origin[2]), (a[2] - c[2]), ray.direction[2];
  
  gamma_matrix << (a[0] - b[0]), (a[0] - ray.origin[0]), ray.direction[0],
                  (a[1] - b[1]), (a[1] - ray.origin[1]), ray.direction[1],
                  (a[2] - b[2]), (a[2] - ray.origin[2]), ray.direction[2];

  t_matrix << (a[0] - b[0]), (a[0] - c[0]), (a[0] - ray.origin[0]),
              (a[1] - b[1]), (a[1] - c[1]), (a[1] - ray.origin[1]),
              (a[2] - b[2]), (a[2] - c[2]), (a[2] - ray.origin[2]);

  // check validity of t, gamma, and beta before returning

  t = t_matrix.determinant() / A_determinant;
  if (t < min_t){
    return false;
  }

  gamma = gamma_matrix.determinant() / A_determinant;
  if (gamma < 0){
    return false;
  }

  beta = beta_matrix.determinant() / A_determinant;
  if (beta < 0){
    return false;
  }

  if (beta + gamma > 1){
    return false;
  }
  
  n = ((b - a).cross(c - a)).normalized(); // normal vector

  return true;
}