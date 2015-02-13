#ifndef BUFFER_HPP_INCLUDED
#define BUFFER_HPP_INCLUDED

#include "glm.hpp"
#include "vertexattribute.hpp"

#include <vector>

namespace gst
{
    class BufferImpl;
    class RenderState;

    enum class BufferTarget {
        ARRAY,
        ELEMENT_ARRAY
    };

    enum class DataUsage {
        STATIC,
        DYNAMIC
    };

    class Buffer {
        friend RenderState;
    public:
        Buffer() = default;
        Buffer(BufferTarget target);

        bool operator==(Buffer const & other);
        bool operator!=(Buffer const & other);
        explicit operator bool() const;

        void set_usage(DataUsage usage);
        void set_int(std::vector<int> const & data);
        void set_uint(std::vector<unsigned int> const & data);
        void set_float(std::vector<float> const & data);
        void set_vec2(std::vector<glm::vec2> const & data);
        void set_vec3(std::vector<glm::vec3> const & data);
        void set_vec4(std::vector<glm::vec4> const & data);

        VertexDataType get_type() const;
        size_t get_count() const;
    private:
        bool need_new_storage(VertexDataType type, size_t count);
        void refresh();

        std::shared_ptr<BufferImpl> impl;
        DataUsage usage;
        VertexDataType type;
        std::shared_ptr<void> shadowed_data;
        size_t count;
        size_t bytes;
        bool dirty;
    };
}

#endif
