#include "delaunay.h"
#include "types.h"
#include <cmath>
#include <array>
#include <vector>
#include <algorithm>
#include <limits>

#define SQR(x) std::pow(x, 2)
#define ABS(x) std::abs(x)
#define SQRT(x) std::sqrt(x)
#define INF std::numeric_limits<float>::max()

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

float distance(Vec2 a, Vec2 b) {
    return SQRT(SQR(b.x - a.x) + SQR(b.y - a.y));
}

Vec2 get_circumcenter(Triangle2 triangle) {
    Vec2 A = triangle.m_p1;
    Vec2 B = triangle.m_p2;
    Vec2 C = triangle.m_p3;
    float D = 2 * ((A.x * (B.y - C.y)) + (B.x * (C.y - A.y)) + (C.x * (A.y - B.y)));
    float x = (1/D) * (((SQR(A.x) + SQR(A.y)) * (B.y - C.y)) + ((SQR(B.x) + SQR(B.y)) * (C.y - A.y)) + ((SQR(C.x) + SQR(C.y)) * (A.y - B.y)));
    float y = (1/D) * (((SQR(A.x) + SQR(A.y)) * (C.x - B.x)) + ((SQR(B.x) + SQR(B.y)) * (A.x - C.x)) + ((SQR(C.x) + SQR(C.y)) * (B.x - A.x)));
    return {x, y};
}

bool in_circumcircle(Triangle2 triangle, Vec2 point) {
    Vec2 center = get_circumcenter(triangle);
    if (distance(center, point) > distance(center, triangle.m_p1)) {
        return false;
    } else {
        return true;
    }
}

std::array<Vec2, 3> get_points(Triangle2 triangle) {
    return {triangle.m_p1, triangle.m_p2, triangle.m_p3};
}

std::array<Edge, 3> get_edges(Triangle2 triangle) {
    return {(Edge){triangle.m_p1, triangle.m_p2}, (Edge){triangle.m_p2, triangle.m_p3}, (Edge){triangle.m_p3, triangle.m_p1}};
}

bool shared_points(Triangle2 a, Triangle2 b) {
    for (Vec2 point_a : get_points(a)) {
        for (Vec2 point_b : get_points(b)) {
            if (point_a == point_b) {
                return true;
            }
        }
    }
    return false;
}

void remove_from_vec(std::vector<Vec2> *vector, Vec2 val) {
    for (int i = 0; i < vector->size();) {
        if ((*vector)[i] == val) {
            vector->erase(vector->begin() + i);
        } else {
            i ++;
        }
    }
}
void remove_from_vec(std::vector<Edge> *vector, Edge val) {
    for (int i = 0; i < vector->size();) {
        if ((*vector)[i] == val) {
            vector->erase(vector->begin() + i);
        } else {
            i ++;
        }
    }
}
void remove_from_vec(std::vector<Triangle2> *vector, Triangle2 val) {
    for (int i = 0; i < vector->size();) {
        if ((*vector)[i] == val) {
            vector->erase(vector->begin() + i);
        } else {
            i ++;
        }
    }
}

std::vector<Edge> get_unique_edges(std::vector<Edge> edges) {
    std::vector<Edge> unique;
    for (int i = 0; i < edges.size(); i ++) {
        bool is_unique = true;
        for (int j = 0; j < edges.size(); j ++) {
            if ((i != j) && edges[i] == edges[j]) {
                is_unique = false;
                break;
            }
        }
        if (is_unique == true) {
            unique.emplace_back(edges[i]);
        }
    }
    return unique;
}

std::vector<Triangle2> get_bowyer_watson(std::vector<Vec2> point_list) {
    std::vector<Triangle2> triangulation;
    Triangle2 super = {(Vec2){-INF, -INF}, (Vec2){INF, -INF}, (Vec2){0, INF}};
    triangulation.emplace_back(super); // must be large enough to completely contain all the points in pointList
    for (Vec2 point : point_list) { // add all the points one at a time to the triangulation
        std::vector<Triangle2> bad_triangles;
        for (Triangle2 triangle : triangulation) { // first find all the triangles that are no longer valid due to the insertion
            if (in_circumcircle(triangle, point)) {
                bad_triangles.emplace_back(triangle); //if a point is inside of the circumcircle of a triangle, then that triangle is Delaunay invalid
            }
        }
        std::vector<Edge> polygon;
        for (Triangle2 triangle : bad_triangles) {
            for (Edge edge : get_edges(triangle)) {
                polygon.emplace_back(edge); //adds every edge in the invalid triangles to the polygonal hole
            }
        }
        polygon = get_unique_edges(polygon); //removes any duplicate, hence shared edges from the polygon, leaving just the outside of the polygon
        for (Triangle2 triangle : bad_triangles) { // remove them from the data structure
            remove_from_vec(&triangulation, triangle);
        }
        for (Edge edge : polygon) { //generates a triangle from each polygonal edge and the point, creating Delaunay valid triangles
            triangulation.emplace_back((Triangle2){edge.m_p1, edge.m_p2, point}); // form a triangle from edge to point and add it to triangulation
        }
    }
    for (Triangle2 triangle : triangulation) { // done inserting points, now clean up
        if (shared_points(triangle, super)) {
            remove_from_vec(&triangulation, triangle); //removes any triangles sharing points with the super triangle, to remove any unoriginal points
        }
    }
    return triangulation;
}
