#include "lightprogramupdater.hpp"

#include "distantlight.hpp"
#include "hemispherelight.hpp"
#include "pointlight.hpp"
#include "spotlight.hpp"

gst::LightProgramUpdater::LightProgramUpdater(Program & program, std::string const & prefix)
    : program(program),
      prefix(prefix)
{
}

void gst::LightProgramUpdater::visit(DistantLight & light)
{
    program.uniform(prefix + "ambient", light.ambient);
    program.uniform(prefix + "diffuse", light.diffuse);
    program.uniform(prefix + "specular", light.specular);
    program.uniform(prefix + "direction", glm::vec4(light.direction, 0.0f));
}

void gst::LightProgramUpdater::visit(HemisphereLight & light)
{
    program.uniform(prefix + "upper", light.upper);
    program.uniform(prefix + "lower", light.lower);
    program.uniform(prefix + "direction", glm::vec4(light.direction, 0.0f));
}

void gst::LightProgramUpdater::visit(PointLight & light)
{
    program.uniform(prefix + "ambient", light.ambient);
    program.uniform(prefix + "diffuse", light.diffuse);
    program.uniform(prefix + "specular", light.specular);
    program.uniform(prefix + "attenuation.constant", light.attenuation.get_constant());
    program.uniform(prefix + "attenuation.linear", light.attenuation.get_linear());
    program.uniform(prefix + "attenuation.quadratic", light.attenuation.get_quadratic());
}

void gst::LightProgramUpdater::visit(SpotLight & light)
{
    program.uniform(prefix + "ambient", light.ambient);
    program.uniform(prefix + "diffuse", light.diffuse);
    program.uniform(prefix + "specular", light.specular);
    program.uniform(prefix + "attenuation.constant", light.attenuation.get_constant());
    program.uniform(prefix + "attenuation.linear", light.attenuation.get_linear());
    program.uniform(prefix + "attenuation.quadratic", light.attenuation.get_quadratic());
    program.uniform(prefix + "exponent", light.exponent);
    program.uniform(prefix + "cutoff", light.cutoff);
}
