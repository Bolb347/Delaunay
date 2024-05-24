#include "delaunay.h"
#include "types.h"
#include <vector>
#include <cstdio>

int main() {
    std::vector<Vec2> cloud = {(Vec2){1, 1}, (Vec2){1, -1}, (Vec2){-1, 1}, (Vec2){-1, -1}};
    std::vector<Triangle2> triangulated = get_bowyer_watson(cloud);
    for (Triangle2 &item : triangulated) {
        std::printf("%f,%f, %f,%f, %f,%f\n", item.m_p1.x, item.m_p1.y, item.m_p2.x, item.m_p2.y, item.m_p3.x, item.m_p3.y);
    }
    return 0;
};
