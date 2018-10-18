#pragma once

#include <memory>

class IVisibleMedia;
class IInvisibleMedia;
class IMedia;

class IFixedLayoutAdaptor;

class IMediaContainer
{
public:
    virtual ~IMediaContainer() = default;

    virtual int width() const = 0;
    virtual int height() const = 0;
    virtual void scale(double scaleX, double scaleY) = 0;

    virtual int zorder() const = 0;
    virtual void show() = 0;

    virtual void addMedia(std::unique_ptr<IMedia>&& media, int x, int y) = 0;
    virtual void addMedia(std::unique_ptr<IMedia>&& media) = 0;
    virtual void removeAllMedia() = 0;
    virtual IFixedLayoutAdaptor& handler() = 0;

};
