#include "programfactory.hpp"

#include "buffer.hpp"
#include "logger.hpp"
#include "program.hpp"
#include "programimpl.hpp"
#include "shader.hpp"
#include "shaderimpl.hpp"

#include <fstream>
#include <sstream>

gst::ProgramFactory::ProgramFactory(std::shared_ptr<Logger> logger)
    : logger(logger)
{
}

gst::Program gst::ProgramFactory::create_from_file(
    std::string const & vs_path,
    std::string const & fs_path,
    std::vector<AttribLocation> const & locations)
{
    auto read_source = [this](std::string const & path)
    {
        std::ifstream file(path.c_str(), std::ifstream::in | std::ifstream::binary);
        if (file.is_open()) {
            std::stringstream buffer;
            buffer << file.rdbuf();
            return buffer.str();
        } else {
            logger->log(TRACE("could not read from file \"" + path + "\""));
            return std::string();
        }
    };

    auto vs_source = read_source(vs_path);
    auto fs_source = read_source(fs_path);

    return create_from_source(vs_source, fs_source, locations);
}

gst::Program gst::ProgramFactory::create_from_source(
    std::string const & vs_source,
    std::string const & fs_source,
    std::vector<AttribLocation> const & locations)
{
    auto create_shader = [this](ShaderType type, std::string const & source)
    {
        auto shader = Shader(type, source);
        if (!shader) {
            logger->log(TRACE("could not compile shader: " + shader.get_compile_error()));
        }
        return shader;
    };

    auto vs = create_shader(ShaderType::VERTEX, vs_source);
    auto fs = create_shader(ShaderType::FRAGMENT, fs_source);

    if (!vs || !fs) {
        return Program();
    } else {
        return create_from_shader(vs, fs, locations);
    }
}

gst::Program gst::ProgramFactory::create_from_shader(
    Shader & vs,
    Shader & fs,
    std::vector<AttribLocation> const & locations)
{
    auto impl = std::make_shared<ProgramImpl>();

    impl->attach(*vs.impl.get());
    impl->attach(*fs.impl.get());

    if (locations.empty()) {
        // default
        impl->bind_attrib_location(AttribIndex::POSITION,  "vertex_position");
        impl->bind_attrib_location(AttribIndex::NORMAL,    "vertex_normal");
        impl->bind_attrib_location(AttribIndex::COLOR,     "vertex_color");
        impl->bind_attrib_location(AttribIndex::TEX_COORD, "vertex_tex_coord");
    } else {
        // custom
        for (auto location : locations) {
            impl->bind_attrib_location(location.first, location.second);
        }
    }

    if (!impl->link()) {
        logger->log(TRACE("could not link program: " + impl->get_error_log()));
        return Program();
    }

    impl->detach(*vs.impl.get());
    impl->detach(*fs.impl.get());

    // shaders may be deleted now, attached shaders will remain unaffected

    return Program(impl, logger);
}
