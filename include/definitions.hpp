#pragma once
#ifndef DEFINITIONS_HPP
#define DEFINITIONS_HPP
#endif
#include <vector>
#include <glm/glm.hpp>


typedef glm::vec3 vec3;
typedef glm::dvec3 dvec3;
typedef glm::dvec3 colorDBL; //color vector
typedef glm::vec3 Direction; //direction vector
typedef glm::vec4 vertex;


#define DIFFUSE "DIFFUSE"
#define MIRROR "MIRROR"
#define TRANSLUCENT "TRANSLUCENT"
#define LIGHTSOURCE "LIGHTSOURCE"

#define RAYSPERPIXEL 2
#define BOUNCES 1
#define WIDTH 800
#define HEIGHT 800
#define PI 3.141592
#define DISTANCETOINTERSECT 100.0f
#define LIGHTSAMPLES 10