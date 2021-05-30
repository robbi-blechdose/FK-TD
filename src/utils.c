#include "utils.h"

void copyPoint(Point* dst, Point* src)
{
    dst->x = src->x;
    dst->y = src->y;
}

uint8_t distanceTE(Point* enemy, Point* tower)
{
    Point temp;
    temp.x = enemy->x / 16;
    temp.y = enemy->y / 16;
    return sqrt(pow(temp.x - tower->x, 2) + pow(temp.y - tower->y, 2));
}