#include "programfactory.hpp"

#include "logger.hpp"
#include "programimpl.hpp"
#include "shaderimpl.hpp"
#include "vertexattribute.hpp"

#include <fstream>
#include <sstream>

gst::ProgramFactory::ProgramFactory(std::shared_ptr<Logger> logger)
    : logger(logger)
{
}

std::unique_ptr<gst::Program> gst::ProgramFactory::create_from_file(
    std::string const & vs_path,
    std::string const & fs_path)
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

    return create_from_source(vs_source, fs_source);
}

std::unique_ptr<gst::Program> gst::ProgramFactory::create_from_source(
    std::string const & vs_source,
    std::string const & fs_source)
{
    auto vs = std::unique_ptr<Shader>(new ShaderImpl(ShaderType::VERTEX, vs_source));
    auto fs = std::unique_ptr<Shader>(new ShaderImpl(ShaderType::FRAGMENT, fs_source));

    return create_from_shader(std::move(vs), std::move(fs));
}

std::unique_ptr<gst::Program> gst::ProgramFactory::create_from_shader(
    std::unique_ptr<Shader> vs,
    std::unique_ptr<Shader> fs)
{
    auto program = std::unique_ptr<Program>(new ProgramImpl());

    program->set_vertex_shader(std::move(vs));
    program->set_fragment_shader(std::move(fs));

    // default attributes
    program->set_attributes({
        { AttributeIndex::POSITION,  "vertex_position"  },
        { AttributeIndex::NORMAL,    "vertex_normal"    },
        { AttributeIndex::COLOR,     "vertex_color"     },
        { AttributeIndex::TEX_COORD, "vertex_tex_coord" },
    });

    return program;
}
