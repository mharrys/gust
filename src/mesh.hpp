#ifndef MESH_HPP_INCLUDED
#define MESH_HPP_INCLUDED

#include "vertexarray.hpp"

namespace gst
{
    class IndexBuffer;
    class NodeRenderer;
    class VertexBuffer;

    class Mesh {
        friend NodeRenderer;
    public:
        Mesh() = default;
        Mesh(std::shared_ptr<VertexArray> vertex_array);

        void draw() const;
        void make_positions(std::vector<glm::vec3> const & data);
        void make_normals(std::vector<glm::vec3> const & data);
        void make_colors(std::vector<glm::vec3> const & data);
        void make_tex_coords(std::vector<glm::vec2> const & data);
        void make_indices(std::vector<glm::uint> const & data);

        DrawMode mode;
        std::shared_ptr<VertexBuffer> positions;
        std::shared_ptr<VertexBuffer> normals;
        std::shared_ptr<VertexBuffer> colors;
        std::shared_ptr<VertexBuffer> tex_coords;
        std::shared_ptr<IndexBuffer> indices;
    protected:
        std::shared_ptr<VertexArray> vertex_array;
    };
}

#endif
