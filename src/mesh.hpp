#ifndef MESH_HPP_INCLUDED
#define MESH_HPP_INCLUDED

#include "indexbuffer.hpp"
#include "vertexarray.hpp"
#include "vertexbuffer.hpp"

#include <memory>

namespace gst
{
    class NodeProgramUpdater;

    class Mesh {
        friend NodeProgramUpdater;
    public:
        Mesh() = default;
        Mesh(VertexArray & vertex_array);

        void draw();

        VertexBuffer<glm::vec3> positions;
        VertexBuffer<glm::vec3> normals;
        VertexBuffer<glm::vec4> colors;
        VertexBuffer<glm::vec2> tex_coords;
        IndexBuffer<glm::uint> indices;

        DrawMode mode;
    protected:
        VertexArray vertex_array;
    };
}

#endif
