#include "mesh.hpp"

#include "bufferimpl.hpp"
#include "graphicsdevice.hpp"
#include "shadoweddataimpl.hpp"

gst::Mesh::Mesh(std::shared_ptr<GraphicsDevice> device, std::shared_ptr<VertexArray> vertex_array)
    : device(device),
      vertex_array(vertex_array),
      mode(DrawMode::TRIANGLES)
{
}

void gst::Mesh::draw() const
{
    if (index_buffer) {
        device->draw_elements(mode, index_buffer->get_count());
    } else {
        device->draw_arrays(mode, 0, positions_buffer->get_count());
    }
}

void gst::Mesh::set_draw_mode(DrawMode mode)
{
    this->mode = mode;
}

void gst::Mesh::set_positions(std::vector<glm::vec3> const & data)
{
    if (!positions_buffer) {
        positions_buffer = make_buffer(BufferTarget::ARRAY);
        vertex_array->add_vertex_buffer(
            positions_buffer,
            { VertexAttribute(AttributeIndex::POSITION, 3, VertexDataType::FLOAT) }
        );
    }
    positions_buffer->set_vec3_array(data);
}

void gst::Mesh::set_normals(std::vector<glm::vec3> const & data)
{
    if (!normals_buffer) {
        normals_buffer = make_buffer(BufferTarget::ARRAY);
        vertex_array->add_vertex_buffer(
            normals_buffer,
            { VertexAttribute(AttributeIndex::NORMAL, 3, VertexDataType::FLOAT) }
        );
    }
    normals_buffer->set_vec3_array(data);
}

void gst::Mesh::set_colors(std::vector<glm::vec3> const & data)
{
    if (!colors_buffer) {
        colors_buffer = make_buffer(BufferTarget::ARRAY);
        vertex_array->add_vertex_buffer(
            colors_buffer,
            { VertexAttribute(AttributeIndex::COLOR, 3, VertexDataType::FLOAT) }
        );
    }
    colors_buffer->set_vec3_array(data);
}

void gst::Mesh::set_tex_coords(std::vector<glm::vec2> const & data)
{
    if (!tex_coords_buffer) {
        tex_coords_buffer = make_buffer(BufferTarget::ARRAY);
        vertex_array->add_vertex_buffer(
            tex_coords_buffer,
            { VertexAttribute(AttributeIndex::TEX_COORD, 2, VertexDataType::FLOAT) }
        );
    }
    tex_coords_buffer->set_vec2_array(data);
}

void gst::Mesh::set_indices(std::vector<unsigned int> const & data)
{
    if (!index_buffer) {
        index_buffer = make_buffer(BufferTarget::ELEMENT_ARRAY);
        vertex_array->set_index_buffer(index_buffer);
    }
    index_buffer->set_unsigned_int_array(data);
}

std::shared_ptr<gst::Buffer> gst::Mesh::make_buffer(BufferTarget target)
{
    auto data = std::make_shared<ShadowedDataImpl>();
    auto buffer = std::make_shared<BufferImpl>(data);
    buffer->set_target(target);
    return buffer;
}
