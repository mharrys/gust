#include "programpool.hpp"

#include "programimpl.hpp"
#include "shader.hpp"

gst::ProgramPool::ProgramPool(std::shared_ptr<Logger> logger)
    : logger(logger)
{
}

std::shared_ptr<gst::Program> gst::ProgramPool::create(std::string const & vs_path, std::string const & fs_path)
{
    const std::string key = vs_path + fs_path;
    if (cache.count(key) == 0) {
        cache[key] = std::make_shared<ProgramImpl>(ProgramImpl::create_from_file(*logger, vs_path, fs_path));
    }
    return cache.at(key);
}
