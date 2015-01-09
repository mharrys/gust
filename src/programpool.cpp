#include "programpool.hpp"

gst::ProgramPool::ProgramPool(ProgramFactory factory)
    : factory(factory)
{
}

std::shared_ptr<gst::Program> gst::ProgramPool::create(std::string const & vs_path, std::string const & fs_path)
{
    const std::string key = vs_path + fs_path;
    if (cache.count(key) == 0) {
        cache[key] = std::make_shared<Program>(factory.create_from_file(vs_path, fs_path));
    }
    return cache.at(key);
}
