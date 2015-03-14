#ifndef BASICPASS_HPP_INCLUDED
#define BASICPASS_HPP_INCLUDED

#include "pass.hpp"

namespace gst
{
    class AnnotationFormatter;

    // The responsibility of this class is to setup everything for a basic
    // shader pass.
    class BasicPass : public Pass {
    public:
        BasicPass();
        BasicPass(std::shared_ptr<UniformCollection> uniforms);
        void apply(MatrixState & matrices, LightNodes & light_nodes) final;
        // Set model view annotation.
        void set_model_view_annotation(std::string const & model_view);
        // Set projection annotation.
        void set_projection_annotation(std::string const & projection);
    private:
        std::shared_ptr<UniformCollection> uniforms;
        std::string model_view;
        std::string projection;
    };
}

#endif
