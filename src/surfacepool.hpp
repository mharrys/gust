#ifndef SURFACEPOOL_HPP_INCLUDED
#define SURFACEPOOL_HPP_INCLUDED

#include "programpool.hpp"
#include "surface.hpp"

namespace gst
{
    class BlinnPhongShading;

    class SurfacePool {
    public:
        SurfacePool(ProgramPool & programs);
        Surface create_blinn_phong(
            std::string const & vs_path,
            std::string const & fs_path);
    private:
        ProgramPool programs;
        std::shared_ptr<BlinnPhongShading> blinn_phong_shading;
    };
}

#endif
