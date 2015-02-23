#include "lightnodecollector.hpp"

void gst::LightNodeCollector::visit(LightNode & node)
{
    lights.push_back(node);
}

std::vector<gst::LightNode> gst::LightNodeCollector::get_lights() const
{
    return lights;
}
