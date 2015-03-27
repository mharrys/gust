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
#include "shaderimpl.hpp"
#include "texture2d.hpp"
#include "uniformmapimpl.hpp"

gst::EffectComposerFactory::EffectComposerFactory(std::shared_ptr<Logger> logger)
    : logger(logger)
{
}

gst::EffectComposer gst::EffectComposerFactory::create()
{
    auto renderer = Renderer::create(logger);

    auto copy_filter = create_copy_filter();
    auto render_targets = create_render_targets();

    MeshFactory mesh_factory(logger);

    auto quad = mesh_factory.create_quad(1.0f, 1.0f);
    auto model = std::make_shared<Model>(quad, copy_filter);
    auto model_node = std::make_shared<ModelNode>(model);

    auto camera = std::unique_ptr<Camera>(new OrthoCamera());
    auto eye = std::make_shared<CameraNode>(std::move(camera));

    auto screen = Scene(eye);
    screen.add(model_node);
    screen.update();

    return EffectComposer(renderer, render_targets, copy_filter, screen);
}

gst::Material gst::EffectComposerFactory::create_copy_filter()
{
    auto copy_pass = std::make_shared<BasicPass>(create_copy_program());
    copy_pass->set_cull_face(CullFace::BACK);
    return Material::create_free(copy_pass);
}

std::shared_ptr<gst::Program> gst::EffectComposerFactory::create_copy_program()
{
    ProgramFactory factory(logger);

    auto vs = std::unique_ptr<Shader>(new ShaderImpl(ShaderImpl::create_copy_vs()));
    auto fs = std::unique_ptr<Shader>(new ShaderImpl(ShaderImpl::create_copy_fs()));

    return factory.create_from_shader(std::move(vs), std::move(fs));
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
