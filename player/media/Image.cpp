#include "Image.hpp"
#include "control/Region.hpp"

#include <spdlog/spdlog.h>

Image::Image(int id, const Size& size, int duration, const std::string& uri,
             ScaleType scale_type, Align align, Valign valign) :
    Media(id, duration, Render::Native, uri),
    m_scale_type(scale_type), m_align(align), m_valign(valign)
{
    try
    {
        auto pixbuf = Gdk::Pixbuf::create_from_file(m_uri, size.width, size.height, is_scaled());
        m_size.width = pixbuf->get_width();
        m_size.height = pixbuf->get_height();
        m_handler.set(pixbuf);
    }
    catch(const Gdk::PixbufError& error)
    {
        spdlog::get(LOGGER)->error("Could create media image: {}", std::string{error.what()});
    }
}

void Image::stop()
{
    m_handler.hide();
    Media::stop();
}

void Image::start()
{
    m_handler.show();
    Media::start();
}

void Image::set_size(int width, int height)
{
    auto new_pixbuf = m_handler.get_pixbuf()->scale_simple(width, height, Gdk::InterpType::INTERP_BILINEAR);
    m_handler.set(new_pixbuf);
}

void Image::set_region(Region* region)
{
    Media::set_region(region);

    Point pos{get_left_pos(), get_top_pos()};
    region->request_handler().connect([=]{
        handler_requested().emit(m_handler, pos);
    });
}

bool Image::is_scaled() const
{
    if(m_scale_type == ScaleType::Scaled)
        return true;
    return false;
}

int Image::get_left_pos() const
{
    switch(m_align)
    {
        case Align::Center:
            return (region().size().width - m_size.width) / 2;
        case Align::Left:
            return DEFAULT_LEFT_POS;
        case Align::Right:
            return region().size().width - m_size.width;
        default:
            break;
    }
    return INVALID_POS;
}

int Image::get_top_pos() const
{
    switch(m_valign)
    {
        case Valign::Middle:
            return (region().size().height - m_size.height) / 2;
        case Valign::Top:
            return DEFAULT_TOP_POS;
        case Valign::Bottom:
            return region().size().height - m_size.height;
        default:
            break;
    }
    return INVALID_POS;
}
