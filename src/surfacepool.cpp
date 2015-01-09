#include "surfacepool.hpp"

#include "basicshading.hpp"
#include "blinnphongshading.hpp"
#include "logger.hpp"
#include "material.hpp"

gst::SurfacePool::SurfacePool(ProgramPool & programs)
    : programs(programs)
{
}

gst::Surface gst::SurfacePool::create_basic(
    std::string const & vs_path,
    std::string const & fs_path)
{
    auto program = programs.create(vs_path, fs_path);

    if (!basic_shading) {
        BasicUniform uniforms;
        uniforms.diffuse = program->uniform("material.diffuse");
        basic_shading = std::make_shared<BasicShading>(uniforms);
    }

    auto material = Material(basic_shading);

    return Surface(material, program);
}

gst::Surface gst::SurfacePool::create_blinn_phong(
    std::string const & vs_path,
    std::string const & fs_path)
{
    auto program = programs.create(vs_path, fs_path);

    if (!blinn_phong_shading) {
        BlinnPhongUniform uniforms;
        uniforms.ambient = program->uniform("material.ambient");
        uniforms.diffuse = program->uniform("material.diffuse");
        uniforms.specular = program->uniform("material.specular");
        uniforms.emission = program->uniform("material.emission");
        uniforms.shininess = program->uniform("material.shininess");
        blinn_phong_shading = std::make_shared<BlinnPhongShading>(uniforms);
    }

    auto material = Material(blinn_phong_shading);

    return Surface(material, program);
}
