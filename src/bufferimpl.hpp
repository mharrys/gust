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
        void set_int(std::vector<int> const & data) final;
        void set_uint(std::vector<unsigned int> const & data) final;
        void set_float(std::vector<float> const & data) final;
        void set_vec2(std::vector<glm::vec2> const & data) final;
        void set_vec3(std::vector<glm::vec3> const & data) final;
        void set_vec4(std::vector<glm::vec4> const & data) final;
        void set_usage(DataUsage usage) final;
        BufferTarget get_target() const final;
        DataUsage get_usage() const final;
        ShadowedData & get_shadowed_data() final;
    private:
        BufferTarget target;
        std::shared_ptr<ShadowedData> shadowed_data;
        DataUsage usage;
    };
}

#endif
