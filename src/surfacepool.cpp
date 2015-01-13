#include "surfacepool.hpp"

#include "basicshading.hpp"
#include "blinnphongshading.hpp"

gst::SurfacePool::SurfacePool(ProgramPool & programs)
    : programs(programs)
{
}

gst::Surface gst::SurfacePool::create_basic(
    std::string const & vs_path,
    std::string const & fs_path)
{
    return create<BasicShading>(vs_path, fs_path);
}

gst::Surface gst::SurfacePool::create_blinn_phong(
    std::string const & vs_path,
    std::string const & fs_path)
{
    return create<BlinnPhongShading>(vs_path, fs_path);
}
