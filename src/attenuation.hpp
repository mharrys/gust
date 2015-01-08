#ifndef ATTENUATION_HPP_INCLUDED
#define ATTENUATION_HPP_INCLUDED

namespace gst
{
    class Attenuation {
    public:
        Attenuation();
        Attenuation(float constant, float linear, float quadratic);
        float get_constant();
        float get_linear();
        float get_quadratic();
    private:
        float constant;
        float linear;
        float quadratic;
    };
}

#endif
