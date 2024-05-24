#ifndef DELAUNAY_H
#define DELAUNAY_H

#include "types.h"
#include <array>
#include <vector>

float distance(const Vec2 &a, const Vec2 &b);

Vec2 get_circumcenter(const Triangle2 &triangle);

bool in_circumcircle(const Triangle2 &triangle, const Vec2 &point);

std::array<Vec2, 3> get_points(const Triangle2 &triangle);

std::array<Edge, 3> get_edges(const Triangle2 &triangle);

std::vector<Vec2> get_shared_points(const Triangle2 &a, const Triangle2 &b);

bool operator==(const Vec2 &a, const Vec2 &b);
bool operator==(const Triangle2 &a, const Triangle2 &b);
bool operator==(const Edge &a, const Edge &b);

void remove_from_vec(std::vector<Vec2> *vector, const Vec2 &val);
void remove_from_vec(std::vector<Edge> *vector, const Edge &val);
void remove_from_vec(std::vector<Triangle2> *vector, const Triangle2 &val);

std::vector<Edge> get_unshared_edges(std::vector<Triangle2> triangles);

std::vector<Triangle2> get_bowyer_watson(const std::vector<Vec2> &point_list);

#endif
