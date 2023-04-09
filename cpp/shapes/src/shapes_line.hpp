

#include "shapes_shape.hpp"

using namespace ilrd;

class Line: public Shape
{
public:
    Line();
    virtual ~Line() {};

    virtual void Draw();

private:
    double m_length;
};
