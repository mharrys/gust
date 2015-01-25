#ifndef MESHFACTORY_HPP_INCLUDED
#define MESHFACTORY_HPP_INCLUDED

#include <memory>
#include <string>
#include <vector>

namespace gst
{
    class Logger;
    class Mesh;

    class MeshFactory {
    public:
        MeshFactory(std::shared_ptr<Logger> logger);
        Mesh create_quad(float width, float height);
        std::vector<Mesh> create_from_file(std::string const & path);
    private:
        std::shared_ptr<Logger> logger;
    };
}

#endif
