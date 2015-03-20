#include "lightnodecollector.hpp"

void gst::LightNodeCollector::visit(LightNode & node)
{
    light_nodes.push_back(node);
}

std::vector<gst::LightNode> gst::LightNodeCollector::get_light_nodes() const
{
    return light_nodes;
}
