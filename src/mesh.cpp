#include "mesh.hpp"

gst::Mesh::Mesh(VertexArray & vertex_array)
    : mode(DrawMode::TRIANGLES),
      vertex_array(vertex_array)
{
}

void gst::Mesh::draw()
{
    if (indices) {
        vertex_array.draw(mode, indices.data.size(), indices.get_type());
    } else {
        vertex_array.draw(mode, 0, positions.data.size());
    }
}
