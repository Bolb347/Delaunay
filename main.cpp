#include "delaunay.h"
#include "types.h"
#include <vector>

int main() {
    std::vector<Vec2> cloud = {(Vec2){1, 1}, (Vec2){1, -1}, (Vec2){-1, 1}, (Vec2){-1, -1}};
    std::vector<Triangle2> triangulated = get_bowyer_watson(cloud);
    return 0;
};
