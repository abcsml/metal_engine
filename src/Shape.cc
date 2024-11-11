#include "Shape.h"
#include "MTLEngine.h"

RenderUnit* Shape::genTriangle(float points[3][2]) {
    VertexUnit triangle;
    triangle.data_ = {
        {points[0][0], points[0][1], 0},
        {points[1][0], points[1][1], 0},
        {points[2][0], points[2][1], 0}
    };

    RenderUnit* render = new RenderUnit(&triangle);
    return render;
}

RenderUnit* Shape::genTriangle(float ratio) {
    float x = std::sqrt(3)/2 * ratio;
    float y = 0.5 * ratio;
    float points[3][2] = {{-x,-y}, {x,-y}, {0.0f,x}};
    return genTriangle(points);
}

RenderUnit* Shape::genQuad(float l, float w) {
    VertexUnit quad;
    quad.data_ = {
        {-l/2, w/2, 0},
        {-l/2, -w/2, 0},
        {l/2, w/2, 0},
        {l/2, -w/2, 0}
    };
    RenderUnit* render = new RenderUnit(&quad);
    return render;
}

RenderUnit* Shape::genQuad(float ratio) {
    return genQuad(ratio, ratio);
}

RenderUnit* Shape::genCircle(float r, int n) {
    // float radius = r/cos(2*3.1415/2/n);
    float radius = r;
    std::vector<VertexData> vertices(n+1);
    std::vector<std::uint16_t> vertexIndices(3*(n+1));
    for (int i = 0; i < n+1; ++i) {
        float y = radius*cos(1.0/n*i*2*3.1415)/2;
        float x = radius*sin(1.0/n*i*2*3.1415)/2;
        vertices[i] = {x, y, 0};

        vertexIndices[i*3] = n;
        vertexIndices[i*3+1] = i;
        vertexIndices[i*3+2] = i+1;
    }
    vertices[n] = {0, 0, 0};
    vertexIndices[3*n+1] = n-1;
    vertexIndices[3*n+2] = 0;

    VertexUnit v;
    VertexIndexUnit i;
    v.data_ = vertices;
    i.data_ = vertexIndices;

    RenderUnit* render = new RenderUnit(&v, &i);
    // 新问题： 相对大小与绝对大小

    return render;
}

RenderUnit* Shape::genCircle(float ratio) {
    return genCircle(ratio, 32);
}
