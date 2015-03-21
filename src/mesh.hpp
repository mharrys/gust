#ifndef MESH_HPP_INCLUDED
#define MESH_HPP_INCLUDED

#include "vertexarray.hpp"

#include "glm.hpp"

namespace gst
{
    class Buffer;
    class GraphicsDevice;
    class NodeRenderer;

    class Mesh {
        friend NodeRenderer;
    public:
        Mesh() = default;
        Mesh(std::shared_ptr<GraphicsDevice> device, std::shared_ptr<VertexArray> vertex_array);
        void draw() const;
        void set_draw_mode(DrawMode mode);
        void set_positions(std::vector<glm::vec3> const & data);
        void set_normals(std::vector<glm::vec3> const & data);
        void set_colors(std::vector<glm::vec3> const & data);
        void set_tex_coords(std::vector<glm::vec2> const & data);
        void set_indices(std::vector<unsigned int> const & data);
    private:
        std::shared_ptr<GraphicsDevice> device;
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
