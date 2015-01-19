#ifndef TECHNIQUE_HPP_INCLUDED
#define TECHNIQUE_HPP_INCLUDED

#include <memory>
#include <vector>

namespace gst
{
    class Pass;

    class Technique {
    public:
        std::vector<std::shared_ptr<Pass>> passes;
    };
}

#endif
