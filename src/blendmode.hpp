#ifndef BLENDMODE_HPP_INCLUDED
#define BLENDMODE_HPP_INCLUDED

namespace gst
{
    // Supported blending techniques.
    enum class BlendMode {
        NONE,           // Blending disabled.
        ADDITIVE,       // Additive blending: out = src_frag + dst_frag.
        MULTIPLICATIVE, // Multiplicative blending: out = src_frag * dst_frag.
        INTERPOLATIVE   // Interpolative blending: out = (src_alpha * src_frag) + ((1 - src_alpha) * dst_frag).
    };
}

#endif
