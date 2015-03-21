#ifndef MESH_HPP_INCLUDED
#define MESH_HPP_INCLUDED

#include "drawmode.hpp"

#include "glm.hpp"

#include <memory>
#include <vector>

namespace gst
{
    class Buffer;
    class IndexBuffer;
    class NodeRenderer;
    class VertexArray;
    class VertexBuffer;

    // The responsibility of this class is to describe a mesh, a collection of
    // vertices.
    class Mesh {
        friend NodeRenderer;
    public:
        Mesh() = default;
        Mesh(std::shared_ptr<VertexArray> vertex_array);
        // Set draw mode.
        void set_draw_mode(DrawMode mode);
        // Set positions from data.
        void set_positions(std::vector<glm::vec3> const & data);
        // Set normals from data (optional).
        void set_normals(std::vector<glm::vec3> const & data);
        // Set colors from data (optional).
        void set_colors(std::vector<glm::vec3> const & data);
        // Set texture coordinates from data (optional).
        void set_tex_coords(std::vector<glm::vec2> const & data);
        // Set indices from data (optional).
        void set_indices(std::vector<unsigned int> const & data);
    private:
        std::shared_ptr<VertexArray> vertex_array;
        DrawMode mode;
        std::shared_ptr<VertexBuffer> positions;
        std::shared_ptr<VertexBuffer> normals;
        std::shared_ptr<VertexBuffer> colors;
        std::shared_ptr<VertexBuffer> tex_coords;
        std::shared_ptr<IndexBuffer> index;
    };
}

#endif
