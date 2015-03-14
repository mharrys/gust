#ifndef BLENDMODE_HPP_INCLUDED
#define BLENDMODE_HPP_INCLUDED

namespace gst
{
    // Supported blending techniques.
    enum class BlendMode {
        NONE,           // Blending disabled.
        ADDITIVE,       // out = src_frag + dst_frag.
        MULTIPLICATIVE, // out = src_frag * dst_frag.
        INTERPOLATIVE   // out = (src_alpha * src_frag) + ((1 - src_alpha) * dst_frag).
    };
}

#endif
