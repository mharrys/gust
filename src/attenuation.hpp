#ifndef ATTENUATION_HPP_INCLUDED
#define ATTENUATION_HPP_INCLUDED

namespace gst
{
    class Attenuation {
    public:
        Attenuation();
        Attenuation(float constant, float linear, float quadratic);
        float get_constant() const;
        float get_linear() const;
        float get_quadratic() const;
    private:
        float constant;
        float linear;
        float quadratic;
    };
}

#endif
