#ifndef BUFFERIMPL_HPP_INCLUDED
#define BUFFERIMPL_HPP_INCLUDED

#include "buffer.hpp"

namespace gst
{
    class BufferImpl : public Buffer {
    public:
        BufferImpl(
            BufferTarget target,
            std::shared_ptr<ShadowedData> shadowed_data);
        void set_int_array(std::vector<int> const & data);
        void set_unsigned_int_array(std::vector<unsigned int> const & data);
        void set_float_array(std::vector<float> const & data);
        void set_vec2_array(std::vector<glm::vec2> const & data);
        void set_vec3_array(std::vector<glm::vec3> const & data);
        void set_vec4_array(std::vector<glm::vec4> const & data);
        void set_usage(DataUsage usage);
        BufferTarget get_target() const;
        DataUsage get_usage() const;
        ShadowedData & get_shadowed_data();
        unsigned int get_count() const;
        unsigned int get_size_bytes() const;
    private:
        BufferTarget target;
        std::shared_ptr<ShadowedData> shadowed_data;
        DataUsage usage;
    };
}

#endif
