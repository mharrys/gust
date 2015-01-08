#include "lightnodecollector.hpp"

void gst::LightNodeCollector::visit(LightNode & node)
{
    lights.push_back(node);
}
