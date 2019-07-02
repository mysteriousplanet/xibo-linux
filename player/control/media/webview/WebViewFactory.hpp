#pragma once

#include "control/media/creators/MediaFactory.hpp"
#include "WebViewOptions.hpp"

class IWebView;

class WebViewFactory : public MediaFactory
{
protected:
    std::unique_ptr<IMedia> createImpl(const MediaOptions& baseOptions, const ExtraOptions& options) override;

private:
    std::shared_ptr<IWebView> createView(const Uri& uri, int width, int height, WebViewOptions::Transparency transparency);
//    void updateFileWidth(const Uri& uri, int width);
};
