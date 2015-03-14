
#ifndef SHADEDPASS_HPP_INCLUDED
#define SHADEDPASS_HPP_INCLUDED

#include "pass.hpp"

namespace gst
{
    // The responsibility of this class is to setup a program object for a
    // shaded shader pass.
    class ShadedPass : public gst::Pass {
    public:
        ShadedPass();
        ShadedPass(std::shared_ptr<gst::UniformMap> uniforms);
        void apply(gst::MatrixState & matrices, gst::LightNodes & light_nodes) final;
        // Set model view matrix annotation.
        void set_model_view_annotation(std::string const & model_view);
        // Set projection matrix annotation.
        void set_projection_annotation(std::string const & projection);
        // Set normal matrix annotation.
        void set_normal_annotation(std::string const & normal);
    private:
        std::shared_ptr<gst::UniformMap> uniforms;
        std::string model_view;
        std::string projection;
        std::string normal;
    };
}

#endif
