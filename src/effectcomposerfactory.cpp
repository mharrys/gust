#include "effectcomposerfactory.hpp"

#include "framebuffer.hpp"
#include "effect.hpp"
#include "effectcomposer.hpp"
#include "effectnode.hpp"
#include "logger.hpp"
#include "mesh.hpp"
#include "meshfactory.hpp"
#include "modelnode.hpp"
#include "orthocamera.hpp"
#include "renderbuffer.hpp"
#include "resolution.hpp"
#include "scene.hpp"
#include "texture.hpp"

gst::EffectComposerFactory::EffectComposerFactory(
    std::shared_ptr<Logger> logger,
    ProgramPool & programs,
    Renderer & renderer)
    : logger(logger),
      render_state(renderer.get_render_state()),
      programs(programs),
      renderer(renderer)
{
}

gst::EffectComposer gst::EffectComposerFactory::create(
    std::string const & vs_path,
    std::string const & fs_path,
    Resolution size)
{
    RenderTargets targets = {
        create_target(size),
        create_target(size)
    };

    MeshFactory mesh_factory(logger, render_state);
    auto quad = mesh_factory.create_quad(1.0f, 1.0f);

    auto program = programs.create(vs_path, fs_path);
    auto screen = std::make_shared<Effect>(quad, targets[0], program);

    Scene scene(std::make_shared<OrthoCamera>());
    scene.add(std::make_shared<EffectNode>(screen));
    scene.update();

    return EffectComposer(renderer, std::move(targets), screen, scene);
}

gst::RenderTarget gst::EffectComposerFactory::create_target(Resolution size)
{
    auto color = create_texture(size);
    auto depth = create_renderbuffer(size);
    auto framebuffer = Framebuffer(render_state, color, depth);
    for (auto & error : framebuffer.check_status()) {
        logger->log(error);
    }
    return RenderTarget(framebuffer, size);
}

gst::Texture gst::EffectComposerFactory::create_texture(Resolution size)
{
    TextureParam param;
    param.target = TextureTarget::TEXTURE_2D;
    param.internal_format = TextureFormat::RGB;
    param.source_format = PixelFormat::RGB;
    param.min_filter = FilterMode::LINEAR;
    param.mag_filter = FilterMode::LINEAR;
    param.wrap_s = WrapMode::CLAMP_TO_EDGE;
    param.wrap_t = WrapMode::CLAMP_TO_EDGE;
    return Texture(render_state, size, {}, param);
}

gst::Renderbuffer gst::EffectComposerFactory::create_renderbuffer(Resolution size)
{
    return Renderbuffer(render_state, size, RenderbufferFormat::DEPTH_COMPONENT16);
}
