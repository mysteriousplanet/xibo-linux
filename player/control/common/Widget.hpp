#pragma once

#include "IWidget.hpp"
#include "IGtkWidget.hpp"

template<typename Interface>
class Widget : public Interface, public IGtkWidget

{
public:
    static_assert(std::is_base_of_v<IWidget, Interface>, "Should implement IWidget");

    Widget(Gtk::Widget& widget) :
        m_widget(widget)
    {
    }

    void show() override
    {
        m_widget.show();
        m_shown.emit();
    }

    void showAll() override
    {
        m_widget.show();
        m_shown.emit();
    }

    void hide() override
    {
        m_widget.hide();
    }

    bool isShown() const override
    {
        return m_widget.is_visible();
    }

    void scale(double scaleX, double scaleY) override
    {
        setSize(static_cast<int>(width() * scaleX),
                static_cast<int>(height() * scaleY));
    }

    void setSize(int width, int height) override
    {
        m_widget.set_size_request(width, height);
    }

    int width() const override
    {
        int width, _;
        m_widget.get_size_request(width, _);
        return width;
    }

    int height() const override
    {
        int _, height;
        m_widget.get_size_request(_, height);
        return height;
    }

    SignalShown shown() override
    {
        return m_shown;
    }

protected:
    Gtk::Widget& getHandler(IWidget& widget)
    {
        return dynamic_cast<IGtkWidget&>(widget).get();
    }

private:
    Gtk::Widget& m_widget;
    SignalShown m_shown;

};
