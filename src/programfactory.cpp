#include "programfactory.hpp"

#include "logger.hpp"
#include "programimpl.hpp"
#include "shaderimpl.hpp"
#include "vertexattribute.hpp"

#include <fstream>
#include <sstream>

gst::ProgramFactory::ProgramFactory(
    std::shared_ptr<GraphicsDevice> device,
    std::shared_ptr<Logger> logger)
    : device(device),
      logger(logger)
{
}

std::unique_ptr<gst::Program> gst::ProgramFactory::create_from_file(
    std::string const & vs_path,
    std::string const & fs_path,
    std::vector<AttributeLocation> const & locations)
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

std::unique_ptr<gst::Program> gst::ProgramFactory::create_from_source(
    std::string const & vs_source,
    std::string const & fs_source,
    std::vector<AttributeLocation> const & locations)
{
    auto create_shader = [this](ShaderType type, std::string const & source)
    {
        auto shader = std::make_shared<ShaderImpl>(device, type);

        shader->compile(source);
        if (!shader->get_compile_status()) {
            logger->log(TRACE("could not compile shader (" + source + "): " + shader->get_compile_error()));
        }

        return shader;
    };

    auto vs = create_shader(ShaderType::VERTEX, vs_source);
    auto fs = create_shader(ShaderType::FRAGMENT, fs_source);

    if (!vs->get_compile_status() || !fs->get_compile_status()) {
        logger->log(TRACE("shader compiler error, skipping program creation"));
        return nullptr;
    }

    auto program = std::unique_ptr<ProgramImpl>(new ProgramImpl(device, logger));

    program->attach(*vs);
    program->attach(*fs);

    if (locations.empty()) {
        // default
        program->bind_attribute(AttributeIndex::POSITION,  "vertex_position");
        program->bind_attribute(AttributeIndex::NORMAL,    "vertex_normal");
        program->bind_attribute(AttributeIndex::COLOR,     "vertex_color");
        program->bind_attribute(AttributeIndex::TEX_COORD, "vertex_tex_coord");
    } else {
        // custom
        for (auto location : locations) {
            program->bind_attribute(location.first, location.second);
        }
    }

    program->link();
    if (!program->get_link_status()) {
        logger->log(TRACE("could not link program: " + program->get_link_error()));
        return nullptr;
    }

    program->detach(*vs);
    program->detach(*fs);

    return std::move(program);
}
