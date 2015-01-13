#ifndef SURFACEPOOL_HPP_INCLUDED
#define SURFACEPOOL_HPP_INCLUDED

#include "programpool.hpp"
#include "surface.hpp"

namespace gst
{
    typedef std::unordered_map<std::string, std::shared_ptr<MaterialShading>> MaterialCache;

    class SurfacePool {
    public:
        SurfacePool(ProgramPool & programs);
        template<typename T>
        Surface create(
            std::string const & vs_path,
            std::string const & fs_path);
        Surface create_basic(
            std::string const & vs_path,
            std::string const & fs_path);
        Surface create_blinn_phong(
            std::string const & vs_path,
            std::string const & fs_path);
    private:
        ProgramPool programs;
        MaterialCache cache;
    };
}

template<typename T>
gst::Surface gst::SurfacePool::create(
    std::string const & vs_path,
    std::string const & fs_path)
{
    auto program = programs.create(vs_path, fs_path);

    const std::string key = vs_path + fs_path;
    if (cache.count(key) == 0) {
        cache[key] = std::make_shared<T>(program);
    }
    auto material = Material(cache.at(key));

    return Surface(material, program);
}

#endif
