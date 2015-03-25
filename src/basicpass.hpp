#ifndef BASICPASS_HPP_INCLUDED
#define BASICPASS_HPP_INCLUDED

#include "pass.hpp"

namespace gst
{
    // The responsibility of this class is to setup a program object for a
    // basic shader pass.
    class BasicPass : public Pass {
    public:
        BasicPass(std::shared_ptr<Program> program);
        void apply(ModelState const & state) final;
        // Set model view matrix annotation.
        void set_model_view_annotation(std::string const & model_view);
        // Set projection matrix annotation.
        void set_projection_annotation(std::string const & projection);
    private:
        std::shared_ptr<UniformMap> uniforms;
        std::string model_view;
        std::string projection;
    };
}

#endif
