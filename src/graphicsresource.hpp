#ifndef GRAPHICSRESOURCE_HPP_INCLUDED
#define GRAPHICSRESOURCE_HPP_INCLUDED

#include <functional>

namespace gst
{
    class GraphicsSynchronizer;

    typedef unsigned int ResourceName;

    // The responsibility of this class is to identify a resource on the
    // graphics card.
    class GraphicsResource {
        friend GraphicsSynchronizer;
    public:
        GraphicsResource();
        virtual ~GraphicsResource();
    protected:
        // Flag this resource for synchronization with the graphics card.
        virtual void needs_update();
    private:
        ResourceName name;
        bool dirty;
        std::function<void()> cleanup;
    };
}

#endif
