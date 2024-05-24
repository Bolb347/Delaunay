#include "types.h"
#include <cmath>
#include <array>
#include <vector>
#include <limits>

#define POW(x, y) std::pow(x, y)
#define ABS(x) std::abs(x)
#define SQRT(x) std::sqrt(x)
#define INF std::numeric_limits<float>::max()

std::array<Vec2, 3> get_points(const Triangle2 &triangle) {
    return {triangle.m_p1, triangle.m_p2, triangle.m_p3};
}

std::array<Edge, 3> get_edges(const Triangle2 &triangle) {
    return {(Edge){triangle.m_p1, triangle.m_p2}, (Edge){triangle.m_p2, triangle.m_p3}, (Edge){triangle.m_p3, triangle.m_p1}};
}

bool operator==(const Vec2 &a, const Vec2 &b) {
    if ((a.x == b.x) && (a.y == b.y)) {
        return true;
    } else {
        return false;
    }
}
bool operator==(const Triangle2 &a, const Triangle2 &b) {
    if ((a.m_p1 == b.m_p1) && (a.m_p2 == b.m_p2) && (a.m_p3 == b.m_p3)) {
        return true;
    } else if ((a.m_p1 == b.m_p2) && (a.m_p2 == b.m_p3) && (a.m_p3 == b.m_p1)) {
        return true;
    } else if ((a.m_p1 == b.m_p3) && (a.m_p2 == b.m_p1) && (a.m_p3 == b.m_p2)) {
        return true;
    } else {
        return false;
    }
}
bool operator==(const Edge &a, const Edge &b) {
    if (((a.m_p1 == b.m_p1) && (a.m_p2 == b.m_p2)) || ((a.m_p1 == b.m_p2) && (a.m_p2 == b.m_p1))) {
        return true;
    } else {
        return false;
    }
}

void remove_from_vec(std::vector<Vec2> *vector, const Vec2 &val) {
    vector->erase(std::remove(vector->begin(), vector->end(), val), vector->end());
}
void remove_from_vec(std::vector<Edge> *vector, const Edge &val) {
    vector->erase(std::remove(vector->begin(), vector->end(), val), vector->end());
}
void remove_from_vec(std::vector<Triangle2> *vector, const Triangle2 &val) {
    vector->erase(std::remove(vector->begin(), vector->end(), val), vector->end());
}

std::vector<Triangle2> get_bowyer_watson(std::vector<Vec2> pointList) {
    std::vector<Triangle2> triangulation;
    triangulation.emplace_back((Triangle2){(Vec2){-INF, -INF}, (Vec2){INF, -INF}, (Vec2){0, INF}}); // must be large enough to completely contain all the points in pointList
    for (Vec2 &point : pointList) { // add all the points one at a time to the triangulation
        std::vector<Triangle2> badTriangles;
        for (Triangle2 &triangle : triangulation) { // first find all the triangles that are no longer valid due to the insertion
            if () {///point is inside circumcircle of triangle
                badTriangles.emplace_back(triangle);
        }
        std::vector<Edge> polygon;
        for (Triangle2 &triangle : badTriangles) { // find the boundary of the polygonal hole
            for (Edge &edge : get_edges(triangle)) {
                if () {///edge is not shared by any other triangles in badTriangles
                    polygon.emplace_back(edge);
            }
        }
        for (Triangle2 &triangle : badTriangles) { // remove them from the data structure
            remove_from_vec(&triangulation, triangle);
        }
        for (Edge &edge : polygon) { // re-triangulate the polygonal hole
            triangulation.emplace_back((Triangle2){edge.m_p1, edge.m_p2, point}) // form a triangle from edge to point and add it to triangulation
    }
    for (Triangle2 &triangle : triangulation) { // done inserting points, now clean up
        if () {///triangle contains a vertex from original super-triangle
            remove_from_vec(&triangulation, triangle);
        }
    }
    return triangulation
}
