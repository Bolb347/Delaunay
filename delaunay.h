#ifndef DELAUNAY_H
#define DELAUNAY_H

#include "types.h"
#include <array>
#include <vector>

float distance(Vec2 a, Vec2 b);

Vec2 get_circumcenter(Triangle2 triangle);

bool in_circumcircle(Triangle2 triangle, Vec2 point);

std::array<Vec2, 3> get_points(Triangle2 triangle);

std::array<Edge, 3> get_edges(Triangle2 triangle);

std::vector<Vec2> get_shared_points(Triangle2 a, Triangle2 b);

bool operator==(const Vec2 &a, const Vec2 &b);
bool operator==(const Triangle2 &a, const Triangle2 &b);
bool operator==(const Edge &a, const Edge &b);

void remove_from_vec(std::vector<Vec2> *vector, Vec2 val);
void remove_from_vec(std::vector<Edge> *vector, Edge val);
void remove_from_vec(std::vector<Triangle2> *vector, Triangle2 val);

std::vector<Edge> get_unshared_edges(std::vector<Triangle2> triangles);

std::vector<Triangle2> get_bowyer_watson(std::vector<Vec2> point_list);

#endif
