#include "ShapeUnit.h"

ShapeUnit::ShapeUnit(ShapeType type, uint32_t color)
: type_(type), color_(color) {

}

VertexUnit ShapeUnit::genVertexUnit() {
    VertexUnit vertex;
    if (type_ == Circle) {
        vertex.data_.resize(circleSmooth_+1);
        int n = circleSmooth_;
        float radius = circle_.radius;
        for (int i = 0; i < n+1; ++i) {
            float y = radius*cos(1.0/n*i*2*3.1415)/2;
            float x = radius*sin(1.0/n*i*2*3.1415)/2;
            vertex.data_[i] = {x, y, 0};
        }
        vertex.data_[n] = {0, 0, 0};
    }
    else if (type_ == Triangle) {
        vertex.data_ = {
            {triangle_.A[0], triangle_.A[1], 0},
            {triangle_.B[0], triangle_.B[1], 0},
            {triangle_.C[0], triangle_.C[1], 0},
        };
    }
    else if (type_ == Rectangle) {
        vertex.data_ = {
            {rectangle_.A.x, rectangle_.A.y, 0},
            {rectangle_.B.x, rectangle_.B.y, 0},
            {-rectangle_.B.x, -rectangle_.B.y, 0},
            {-rectangle_.A.x, -rectangle_.A.y, 0},
        };
    }

    return vertex;
}

VertexIndexUnit ShapeUnit::genVertexIndexUnit() {
    VertexIndexUnit vertexIndex;
    if (type_ == Circle) {
        int n = circleSmooth_;
        if (!onlyFrame_) {
            vertexIndex.data_.resize(3*(n+1));
            for (int i = 0; i < n+1; ++i) {
                vertexIndex.data_[i*3] = n;
                vertexIndex.data_[i*3+1] = i;
                vertexIndex.data_[i*3+2] = i+1;
            }
            vertexIndex.data_[3*n+1] = n-1;
            vertexIndex.data_[3*n+2] = 0;
        } else {
            vertexIndex.data_.resize(n+1);
            for (int i = 0; i < n; ++i) {
                vertexIndex.data_[i] = i;
            }
            vertexIndex.data_[n] = 0;
        }
    }
    else if (type_ == Triangle) {
        vertexIndex.data_ = {0, 1, 2};
    }
    else if (type_ == Rectangle) {
        if (!onlyFrame_) {
            vertexIndex.data_ = {0, 1, 2, 3};
        } else {
            vertexIndex.data_ = {0, 1, 3, 2};
        }
    }

    return vertexIndex;
}
