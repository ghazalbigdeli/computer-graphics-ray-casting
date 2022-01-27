#include "first_hit.h"
#include <iostream>

bool first_hit(
  const Ray & ray, 
  const double min_t,
  const std::vector< std::shared_ptr<Object> > & objects,
  int & hit_id, 
  double & t,
  Eigen::Vector3d & n)
{
  hit_id = -1;
  bool intersect_bool = false;
  double closest_hit = INFINITY;

  // loop through objects and look for closest hit
  for (int i = 0; i < objects.size(); i++){
    intersect_bool = objects.at(i).get()->intersect(ray, min_t, t, n);
    
    if (intersect_bool){
      // make sure object is farther than min_t
      if (t >= min_t && t < closest_hit){
        // store closest hit index
        hit_id = i;
        closest_hit = t;
      }
    }
  }

  // if hit_id is negative, no object found along ray
  if (hit_id == -1){
    return false;
  } else { // object found, get t and norm of the hit location
    objects.at(hit_id).get()->intersect(ray, min_t, t, n);
    return true;
  }
}