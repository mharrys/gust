#ifndef TEXTURE2D_HPP_INCLUDED
#define TEXTURE2D_HPP_INCLUDED

#include "resolution.hpp"
#include "texture.hpp"

#include <memory>

namespace gst
{
    class Texture2d : public Texture {
    public:
        Texture2d(
            std::shared_ptr<GraphicsDevice> device,
            Resolution size,
            std::vector<unsigned char> const & data,
            TextureParam const & param);
        Texture2d(
            std::shared_ptr<GraphicsDevice> device,
            Image const & image,
            TextureParam const & param);
        ~Texture2d();
        void set_size(Resolution size);
        void set_data(std::vector<unsigned char> const & data);
        void set_image(Image const & image);
        void set_param(TextureParam const & param);
        TextureHandle get_handle() const;
    private:
        void bind(int unit);
        void sync();

        TextureHandle handle;
        std::shared_ptr<GraphicsDevice> device;

        TextureTarget target;
        Resolution size;
        std::vector<unsigned char> data;
        TextureParam param;
        bool image_dirty;
        bool param_dirty;
    };
}

#endif
