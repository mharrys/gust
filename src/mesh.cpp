#include "mesh.hpp"

#include "indexbuffer.hpp"
#include "vertexbuffer.hpp"

gst::Mesh::Mesh(std::shared_ptr<VertexArray> vertex_array)
    : mode(DrawMode::TRIANGLES),
      vertex_array(vertex_array)
{
}

void gst::Mesh::draw() const
{
    if (indices && *indices.get()) {
        vertex_array->draw(mode, indices->get_count(), indices->get_type());
    } else if (positions && *positions.get()) {
        vertex_array->draw(mode, 0, positions->get_count());
    }
}

void gst::Mesh::make_positions(std::vector<glm::vec3> const & data)
{
    if (!positions) {
        positions = std::make_shared<VertexBuffer>(
            VertexAttribute(AttributeIndex::POSITION, 3, VertexDataType::FLOAT)
        );
    }
    positions->set_vec3(data);
}

void gst::Mesh::make_normals(std::vector<glm::vec3> const & data)
{
    if (!normals) {
        normals = std::make_shared<VertexBuffer>(
            VertexAttribute(AttributeIndex::NORMAL, 3, VertexDataType::FLOAT)
        );
    }
    normals->set_vec3(data);
}

void gst::Mesh::make_colors(std::vector<glm::vec3> const & data)
{
    if (!colors) {
        colors = std::make_shared<VertexBuffer>(
            VertexAttribute(AttributeIndex::COLOR, 3, VertexDataType::FLOAT)
        );
    }
    colors->set_vec3(data);
}

void gst::Mesh::make_tex_coords(std::vector<glm::vec2> const & data)
{
    if (!tex_coords) {
        tex_coords = std::make_shared<VertexBuffer>(
            VertexAttribute(AttributeIndex::TEX_COORD, 2, VertexDataType::FLOAT)
        );
    }
    tex_coords->set_vec2(data);
}

void gst::Mesh::make_indices(std::vector<glm::uint> const & data)
{
    if (!indices) {
        indices = std::make_shared<IndexBuffer>();
    }
    indices->set_uint(data);
}
