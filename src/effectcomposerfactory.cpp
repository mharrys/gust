#include "effectcomposerfactory.hpp"

#include "basicpass.hpp"
#include "cameranode.hpp"
#include "framebufferimpl.hpp"
#include "logger.hpp"
#include "model.hpp"
#include "modelnode.hpp"
#include "meshfactory.hpp"
#include "orthocamera.hpp"
#include "programfactory.hpp"
#include "program.hpp"
#include "renderbufferimpl.hpp"
#include "texture2d.hpp"
#include "uniformmapimpl.hpp"

gst::EffectComposerFactory::EffectComposerFactory(std::shared_ptr<Logger> logger)
    : logger(logger)
{
}

gst::EffectComposer gst::EffectComposerFactory::create()
{
    auto renderer = Renderer::create(logger);

    auto copy_effect = create_copy_effect();
    auto render_targets = create_render_targets();

    MeshFactory mesh_factory(logger);

    auto quad = mesh_factory.create_quad(1.0f, 1.0f);
    auto model = std::make_shared<Model>(quad, copy_effect);
    auto model_node = std::make_shared<ModelNode>(model);

    auto camera = std::make_shared<gst::OrthoCamera>();
    auto eye = std::make_shared<gst::CameraNode>(camera);

    auto scene = gst::Scene(eye);
    scene.add(model_node);
    scene.update();

    return EffectComposer(renderer, render_targets, copy_effect, scene);
}

gst::Effect gst::EffectComposerFactory::create_copy_effect()
{
    auto copy_pass = std::make_shared<BasicPass>(
        Resolution(1, 1),
        create_copy_program()
    );
    copy_pass->cull_face = CullFace::BACK;

    return Effect::create_free(copy_pass);
}

std::shared_ptr<gst::Program> gst::EffectComposerFactory::create_copy_program()
{
    std::string vs_src = ""
    "#version 130\n"
    "uniform mat4 model_view;\n"
    "uniform mat4 projection;\n"
    "in vec4 vertex_position;\n"
    "void main() { gl_Position = projection * model_view * vertex_position; }\n";

    std::string fs_src = ""
    "#version 130\n"
    "uniform vec2 resolution;\n"
    "uniform sampler2D read;\n"
    "out vec4 frag_color;\n"
    "void main() { vec2 uv = gl_FragCoord.xy / resolution.xy; frag_color = texture(read, uv); }\n";

    ProgramFactory factory(logger);
    return factory.create_from_source(vs_src, fs_src);
}

gst::RenderTargets gst::EffectComposerFactory::create_render_targets()
{
    auto create_framebuffer = []()
    {
        const auto size = Resolution(1, 1);

        auto color = std::make_shared<Texture2D>(size);
        color->set_wrap_s(WrapMode::CLAMP_TO_EDGE);
        color->set_wrap_t(WrapMode::CLAMP_TO_EDGE);

        auto format = RenderbufferFormat::DEPTH_COMPONENT24;
        auto depth = std::make_shared<RenderbufferImpl>(size, format);

        auto target = std::make_shared<FramebufferImpl>();
        target->set_color({ color });
        target->set_depth({ depth });

        return target;
    };

    return { create_framebuffer(), create_framebuffer() };
}
