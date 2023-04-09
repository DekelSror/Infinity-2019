#ifndef RD66_SHAPE_HPP
#define RD66_SHAPE_HPP

#include "point.hpp"
#include "glut_utils.h"

namespace ilrd
{

class Shape
{
public:
    Shape();
    virtual ~Shape() {};

    virtual void Draw() = 0;

private:
    Point m_center;
    int m_angle;
    double m_scale;
    enum COLORS m_color;
};

} // namespace ilrd


#endif // RD66_SHAPE_HPP
