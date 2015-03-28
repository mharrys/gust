#ifndef FILTER_HPP_INCLUDED
#define FILTER_HPP_INCLUDED

#include "material.hpp"

namespace gst
{
    class Pass;

    // The responsibility of this class is to describe a image filter
    // technique for a single pass.
    class Filter {
    public:
        // Construct empty filter.
        Filter() = default;
        // Construct filter from a material and pass.
        Filter(Material material, std::shared_ptr<Pass> pass);
        // Return material uniform.
        ShadowedData & get_uniform(std::string const & annotation);
        // Return material textures.
        Textures & get_textures();
        // Return material.
        Material & get_material();
        // Return pass.
        Pass & get_pass();
    private:
        Material material;
        std::shared_ptr<Pass> pass;
    };
}

#endif
