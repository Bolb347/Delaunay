#ifndef TYPES_H
#define TYPES_H

typedef struct Vec2 {
    float x, y;
} Vec2;

typedef struct Triangle2 {
    Vec2 m_p1, m_p2, m_p3;
} Triangle2;

typedef struct Edge {
    Vec2 m_p1, m_p2;
} Edge;

#endif
