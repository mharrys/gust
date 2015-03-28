#include "shaderimpl.hpp"

#include "logger.hpp"

#include <fstream>
#include <sstream>

gst::ShaderImpl gst::ShaderImpl::create_from_file(
    Logger & logger,
    ShaderType type,
    std::string const & path)
{
    std::ifstream file(path.c_str(), std::ifstream::in | std::ifstream::binary);
    if (file.is_open()) {
        std::stringstream buffer;
        buffer << file.rdbuf();
        return ShaderImpl(type, buffer.str());
    } else {
        logger.log(TRACE("could not read from file \"" + path + "\""));
        return ShaderImpl(type, "");
    }
}

gst::ShaderImpl gst::ShaderImpl::create_copy_vs()
{
    std::string src =
        "#version 130\n"
        "uniform mat4 model_view;\n"
        "uniform mat4 projection;\n"
        "in vec4 vertex_position;\n"
        "void main() {\n"
        "   gl_Position = projection * model_view * vertex_position;\n"
        "}\n";
    return ShaderImpl(ShaderType::VERTEX, src);
}

gst::ShaderImpl gst::ShaderImpl::create_copy_fs()
{
    std::string src =
        "#version 130\n"
        "uniform vec2 resolution;\n"
        "uniform sampler2D read;\n"
        "out vec4 frag_color;\n"
        "void main() {\n"
        "   vec2 uv = gl_FragCoord.xy / resolution.xy; frag_color = texture(read, uv);\n"
        "}\n";
    return ShaderImpl(ShaderType::FRAGMENT, src);
}

gst::ShaderImpl::ShaderImpl(ShaderType type, std::string source)
    : type(type),
      source(source)
{
    needs_update();
}

gst::ShaderType gst::ShaderImpl::get_type() const
{
    return type;
}

std::string gst::ShaderImpl::get_source() const
{
    return source;
}
