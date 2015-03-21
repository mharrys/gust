#include "mesh.hpp"

#include "indexbuffer.hpp"
#include "graphicsdevice.hpp"
#include "vertexbuffer.hpp"

gst::Mesh::Mesh(std::shared_ptr<GraphicsDevice> device, std::shared_ptr<VertexArray> vertex_array)
    : device(device),
      vertex_array(vertex_array),
      mode(DrawMode::TRIANGLES)
{
}

void gst::Mesh::draw() const
{
    if (index) {
        device->draw_elements(mode, index->get_count());
    } else {
        device->draw_arrays(mode, 0, positions->get_count());
    }
}

void gst::Mesh::set_draw_mode(DrawMode mode)
{
    this->mode = mode;
}

void gst::Mesh::set_positions(std::vector<glm::vec3> const & data)
{
    if (!positions) {
        VertexAttribute attribute = {
            AttributeIndex::POSITION, 3, VertexDataType::FLOAT, 0, 0
        };
        positions = std::make_shared<VertexBuffer>(attribute);
        vertex_array->add_vertex_buffer(positions);
    }
    positions->set_vec3_array(data);
}

void gst::Mesh::set_normals(std::vector<glm::vec3> const & data)
{
    if (!normals) {
        VertexAttribute attribute = {
            AttributeIndex::NORMAL, 3, VertexDataType::FLOAT, 0, 0
        };
        normals = std::make_shared<VertexBuffer>(attribute);
        vertex_array->add_vertex_buffer(normals);
    }
    normals->set_vec3_array(data);
}

void gst::Mesh::set_colors(std::vector<glm::vec3> const & data)
{
    if (!colors) {
        VertexAttribute attribute = {
            AttributeIndex::COLOR, 3, VertexDataType::FLOAT, 0, 0
        };
        colors = std::make_shared<VertexBuffer>(attribute);
        vertex_array->add_vertex_buffer(colors);
    }
    colors->set_vec3_array(data);
}

void gst::Mesh::set_tex_coords(std::vector<glm::vec2> const & data)
{
    if (!tex_coords) {
        VertexAttribute attribute = {
            AttributeIndex::TEX_COORD, 2, VertexDataType::FLOAT, 0, 0
        };
        tex_coords = std::make_shared<VertexBuffer>(attribute);
        vertex_array->add_vertex_buffer(tex_coords);
    }
    tex_coords->set_vec2_array(data);
}

void gst::Mesh::set_indices(std::vector<unsigned int> const & data)
{
    if (!index) {
        index = std::make_shared<IndexBuffer>();
        vertex_array->set_index_buffer(index);
    }
    index->set_unsigned_int_array(data);
}
