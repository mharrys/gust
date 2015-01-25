#include "programfactory.hpp"

#include "logger.hpp"
#include "shader.hpp"

#include <fstream>
#include <sstream>

gst::ProgramFactory::ProgramFactory(std::shared_ptr<Logger> logger)
    : logger(logger)
{
}

gst::Program gst::ProgramFactory::create_from_file(
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

gst::Program gst::ProgramFactory::create_from_source(
    std::string const & vs_source,
    std::string const & fs_source,
    std::vector<AttributeLocation> const & locations)
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
        return Program(logger, { vs, fs }, locations);
    }
}
