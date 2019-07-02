#pragma once

#include <memory>
#include <sigc++/signal.h>

using SignalRegionExpired = sigc::signal<void(int)>;

class IRegionView;
class IMedia;

class IRegion
{
public:
    virtual ~IRegion() = default;

    virtual void addMedia(std::unique_ptr<IMedia>&& media, int x, int y) = 0;
    virtual void start() = 0;
    virtual SignalRegionExpired expired() = 0;

    virtual std::shared_ptr<IRegionView> view() = 0;
};
