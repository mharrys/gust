
#ifndef SHADEDPASS_HPP_INCLUDED
#define SHADEDPASS_HPP_INCLUDED

#include "pass.hpp"

namespace gst
{
    class UniformMap;

    // The responsibility of this class is to setup a program object for a
    // shaded shader pass.
    class ShadedPass : public Pass {
    public:
        ShadedPass(std::shared_ptr<Program> program);
        void apply(ModelState & state) final;
        // Set model view matrix annotation.
        void set_model_view_annotation(std::string const & model_view);
        // Set projection matrix annotation.
        void set_projection_annotation(std::string const & projection);
        // Set normal matrix annotation.
        void set_normal_annotation(std::string const & normal);
        // Set eye position annotation.
        void set_eye_position_annotation(std::string const & eye);
        // Set light enabled annotation.
        void set_light_enabled_annotation(std::string const & enabled);
        // Set light position annotation.
        void set_light_position_annotation(std::string const & position);
    private:
        std::shared_ptr<UniformMap> uniforms;
        std::string model_view;
        std::string projection;
        std::string normal;
        std::string eye_position;
        std::string light_enabled;
        std::string light_position;
    };
}

#endif
