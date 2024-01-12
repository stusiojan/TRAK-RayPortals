#ifndef MATERIAL_H
#define MATERIAL_H

#include "color.h"
#include "hittable.h"
#include "ray.h"
#include "vec3.h"

class lambertian : public material {
public:
  lambertian(const color &a) : albedo(a) {}

  bool scatter(const ray &r_in, const hit_record &rec, color &attenuation,
               ray &scattered) const override {
    vec3 scatter_direction = rec.normal + random_unit_vector();
    if (scatter_direction.near_zero()) {
      scatter_direction = rec.normal;
    }
    scattered = ray(rec.p, scatter_direction);
    attenuation = albedo;
    return true;
  }

private:
  color albedo;
};

class metal : public material {
public:
  metal(const color &a, double f) : albedo(a), fuzz(f) {}

  bool scatter(const ray &r_in, const hit_record &rec, color &attenuation,
               ray &scattered) const override {
    vec3 reflected = reflect(unit_vector(r_in.direction()), rec.normal);
    scattered = ray(rec.p, reflected + fuzz * random_unit_vector());
    attenuation = albedo;
    return (dot(scattered.direction(), rec.normal)) > 0;
  }

private:
  color albedo;
  double fuzz;
};

#endif // !MATERIAL_H
