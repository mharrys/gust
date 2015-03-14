#ifndef BUFFER_HPP_INCLUDED
#define BUFFER_HPP_INCLUDED

#include "graphicsresource.hpp"

#include "glm.hpp"

#include <memory>
#include <vector>

namespace gst
{
    class ShadowedData;

    // Specifies buffer target.
    enum class BufferTarget {
        ARRAY,
        ELEMENT_ARRAY
    };

    // Specifies expected usage pattern of buffer data.
    enum class DataUsage {
        STATIC,
        DYNAMIC
    };

    // The responsibility of this class is to mirror a buffer object on the
    // graphics card.
    class Buffer : public GraphicsResource {
    public:
        virtual ~Buffer() = default;
        // Set client side data to int array.
        virtual void set_int_array(std::vector<int> const & data) = 0;
        // Set client side data to unsigned int array.
        virtual void set_unsigned_int_array(std::vector<unsigned int> const & data) = 0;
        // Set client side data to float array.
        virtual void set_float_array(std::vector<float> const & data) = 0;
        // Set client side data to vec2 array.
        virtual void set_vec2_array(std::vector<glm::vec2> const & data) = 0;
        // Set client side data to vec3 array.
        virtual void set_vec3_array(std::vector<glm::vec3> const & data) = 0;
        // Set client side data to vec4 array.
        virtual void set_vec4_array(std::vector<glm::vec4> const & data) = 0;
        // Set buffer target.
        virtual void set_target(BufferTarget target) = 0;
        // Set buffer data usage.
        virtual void set_usage(DataUsage usage) = 0;
        // Return buffer target.
        virtual BufferTarget get_target() const = 0;
        // Return buffer data usage.
        virtual DataUsage get_usage() const = 0;
        // Return buffer data.
        virtual std::shared_ptr<ShadowedData> get_shadowed_data() const = 0;
        // Return the number of elements in the buffer data.
        virtual unsigned int get_count() const = 0;
        // Return buffer data size in bytes.
        virtual unsigned int get_size_bytes() const = 0;
    };
}

#endif
