#include "types.h"
#include <cmath>
#include <array>
#include <vector>
#include <limits>

#define SQR(x) std::pow(x, 2)
#define ABS(x) std::abs(x)
#define SQRT(x) std::sqrt(x)
#define INF std::numeric_limits<float>::max()

float distance(const Vec2 &a, const Vec2 &b) {
    return SQRT(SQR(b.x - a.x) + SQR(b.y - a.y));
}

Vec2 get_circumcenter(const Triangle2 &triangle) {
    Vec2 A = triangle.m_p1;
    Vec2 B = triangle.m_p2;
    Vec2 C = triangle.m_p3;
    float D = 2 * ((A.x * (B.y - C.y)) + (B.x * (C.y - A.y)) + (C.x * (A.y - B.y)));
    float x = (1/D) * (((SQR(A.x) + SQR(A.y)) * (B.y - C.y)) + ((SQR(B.x) + SQR(B.y)) * (C.y - A.y)) + ((SQR(C.x) + SQR(C.y)) * (A.y - B.y)));
    float y = (1/D) * (((SQR(A.x) + SQR(A.y)) * (C.x - B.x)) + ((SQR(B.x) + SQR(B.y)) * (A.x - C.x)) + ((SQR(C.x) + SQR(C.y)) * (B.x - A.x)));
    return {x, y};
}

bool in_circumcircle(const Triangle2 &triangle, const Vec2 &point) {
    Vec2 center = get_circumcenter(triangle);
    if (distance(center, point) > distance(center, triangle.m_p1)) {
        return false;
    } else {
        return true;
    }
}

std::array<Vec2, 3> get_points(const Triangle2 &triangle) {
    return {triangle.m_p1, triangle.m_p2, triangle.m_p3};
}

std::array<Edge, 3> get_edges(const Triangle2 &triangle) {
    return {(Edge){triangle.m_p1, triangle.m_p2}, (Edge){triangle.m_p2, triangle.m_p3}, (Edge){triangle.m_p3, triangle.m_p1}};
}

std::vector<Vec2> get_shared_points(const Triangle2 &a, const Triangle2 &b) {
    std::vector<Vec2> shared;
    for (Vec2 &point_a : get_points(a)) {
        for (Vec2 &point_b : get_points(b)) {
            if (point_a == point_b) {
                shared.emplace_back(point_a);
            }
        }
    }
    return shared;
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
    std::vector<Vec2>::iterator itr = vector->begin();
    while (itr != vector->end()) {
        if (*itr == val) {
            vector->erase(itr);
        } else {
            itr ++;
        }
    }
}
void remove_from_vec(std::vector<Edge> *vector, const Edge &val) {
    std::vector<Edge>::iterator itr = vector->begin();
    while (itr != vector->end()) {
        if (*itr == val) {
            vector->erase(itr);
        } else {
            itr ++;
        }
    }
}
void remove_from_vec(std::vector<Triangle2> *vector, const Triangle2 &val) {
    std::vector<Edge>::iterator itr = vector->begin();
    while (itr != vector->end()) {
        if (*itr == val) {
            vector->erase(itr);
        } else {
            itr ++;
        }
    }
}

std::vector<Edge> get_unshared_edges(std::vector<Triangle2> triangles) {
    std::vector<Edge> unshared;
    for (Triangle2 &triangle : triangles) {
        for (Edge &edge : get_edges(triangle)) {
            unshared.emplace_back();
        }
    }
    for (Triangle2 &triangle : triangles) {
        for (Triangle2 &other : triangles) {
            if (triangle != other) {
                for (Edge &edge_t : get_edges(triangle)) {
                    for (Edge &edge_o : get_edges(other)) {
                        if (edge_t == edge_o) {
                            remove_from_vec(&unshared, edge_t);
                        }
                    }
                }
            }
        }
    }
    return unshared;
}

std::vector<Triangle2> get_bowyer_watson(const std::vector<Vec2> &point_list) {
    std::vector<Triangle2> triangulation;
    Triangle2 super = {(Vec2){-INF, -INF}, (Vec2){INF, -INF}, (Vec2){0, INF}};
    triangulation.emplace_back(super); // must be large enough to completely contain all the points in pointList
    for (Vec2 &point : point_list) { // add all the points one at a time to the triangulation
        std::vector<Triangle2> bad_triangles;
        for (Triangle2 &triangle : triangulation) { // first find all the triangles that are no longer valid due to the insertion
            if (in_circumcircle(triangle, point)) {
                bad_triangles.emplace_back(triangle);
        }
        std::vector<Edge> polygon;
        for (Edge &edge : get_unshared_edges(bad_triangles)) { // find the boundary of the polygonal hole
            polygon.emplace_back(edge);
        }
        for (Triangle2 &triangle : bad_triangles) { // remove them from the data structure
            remove_from_vec(&triangulation, triangle);
        }
        for (Edge &edge : polygon) { // re-triangulate the polygonal hole
            triangulation.emplace_back((Triangle2){edge.m_p1, edge.m_p2, point}); // form a triangle from edge to point and add it to triangulation
    }
    for (Triangle2 &triangle : triangulation) { // done inserting points, now clean up
        if (get_shared_points(triangle, super).size() > 0) {
            remove_from_vec(&triangulation, triangle);
        }
    }
    return triangulation;
}
