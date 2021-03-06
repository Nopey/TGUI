/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// TGUI - Texus' Graphical User Interface
// Copyright (C) 2012-2017 Bruno Van de Velde (vdv_b@tgui.eu)
//
// This software is provided 'as-is', without any express or implied warranty.
// In no event will the authors be held liable for any damages arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it freely,
// subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented;
//    you must not claim that you wrote the original software.
//    If you use this software in a product, an acknowledgment
//    in the product documentation would be appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such,
//    and must not be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source distribution.
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "Tests.hpp"
#include <TGUI/Widgets/Button.hpp>

TEST_CASE("[Signal]")
{
    tgui::Widget::Ptr widget = tgui::ClickableWidget::create();

    SECTION("connect")
    {
        unsigned int id = widget->connect("PositionChanged", [](){});
        REQUIRE(widget->connect("PositionChanged", [](tgui::Widget::Ptr, std::string){}) == ++id);
        REQUIRE(widget->onPositionChange.connect([](){}) == ++id);
        REQUIRE(widget->onPositionChange.connect([](sf::Vector2f){}) == ++id);
        REQUIRE(widget->onPositionChange.connect([](tgui::Widget::Ptr, std::string){}) == ++id);
        REQUIRE(widget->onPositionChange.connect([](tgui::Widget::Ptr, std::string, sf::Vector2f){}) == ++id);

        REQUIRE(widget->connect("SizeChanged", [](){}) == ++id);
        REQUIRE(widget->connect("SizeChanged", [](tgui::Widget::Ptr, std::string){}) == ++id);
        REQUIRE(widget->onSizeChange.connect([](){}) == ++id);
        REQUIRE(widget->onSizeChange.connect([](sf::Vector2f){}) == ++id);
        REQUIRE(widget->onSizeChange.connect([](tgui::Widget::Ptr, std::string){}) == ++id);
        REQUIRE(widget->onSizeChange.connect([](tgui::Widget::Ptr, std::string, sf::Vector2f){}) == ++id);

        REQUIRE(widget->connect("Focused", [](){}) == ++id);
        REQUIRE(widget->connect("Focused", [](tgui::Widget::Ptr, std::string){}) == ++id);
        REQUIRE(widget->onFocus.connect([](){}) == ++id);
        REQUIRE(widget->onFocus.connect([](tgui::Widget::Ptr, std::string){}) == ++id);

        REQUIRE(widget->connect("Unfocused", [](){}) == ++id);
        REQUIRE(widget->connect("Unfocused", [](tgui::Widget::Ptr, std::string){}) == ++id);
        REQUIRE(widget->onUnfocus.connect([](){}) == ++id);
        REQUIRE(widget->onUnfocus.connect([](tgui::Widget::Ptr, std::string){}) == ++id);

        REQUIRE(widget->connect("MouseEntered", [](){}) == ++id);
        REQUIRE(widget->connect("MouseEntered", [](tgui::Widget::Ptr, std::string){}) == ++id);
        REQUIRE(widget->onMouseEnter.connect([](){}) == ++id);
        REQUIRE(widget->onMouseEnter.connect([](tgui::Widget::Ptr, std::string){}) == ++id);

        REQUIRE(widget->connect("MouseLeft", [](){}) == ++id);
        REQUIRE(widget->connect("MouseLeft", [](tgui::Widget::Ptr, std::string){}) == ++id);
        REQUIRE(widget->onMouseLeave.connect([](){}) == ++id);
        REQUIRE(widget->onMouseLeave.connect([](tgui::Widget::Ptr, std::string){}) == ++id);

        REQUIRE_THROWS_AS(widget->connect("SomeInvalidSignal", [](){}), tgui::Exception);

        tgui::Widget::Ptr widget2 = tgui::Button::create();
        REQUIRE(widget2->connect("Pressed", [](){}) == ++id);
        REQUIRE(widget2->connect("Pressed", [](int){}, 5) == ++id);
        REQUIRE(widget2->connect("Pressed", [](auto){}, 10.f) == ++id);
        REQUIRE(widget2->connect("Pressed", [](tgui::Widget::Ptr, std::string){}) == ++id);
        REQUIRE(widget2->connect("Pressed", [](auto, auto, auto, tgui::Widget::Ptr, std::string){}, "Hey", 15, 3.f) == ++id);

        struct Class
        {
            void signalHandler1() {}
            void signalHandler2(tgui::Widget::Ptr, const std::string&) {}
            void signalHandler3(int, float, tgui::Widget::Ptr, const std::string&) {}
            void signalHandler4(int&, tgui::Widget::Ptr, const std::string&) {}
        } instance;

        int i;
        REQUIRE(widget2->connect("Pressed", &Class::signalHandler1, &instance) == ++id);
        REQUIRE(widget2->connect("Pressed", &Class::signalHandler2, &instance) == ++id);
        REQUIRE(widget2->connect("Pressed", &Class::signalHandler3, &instance, 0, 5.f) == ++id);
        REQUIRE(widget2->connect("Pressed", &Class::signalHandler4, &instance, std::ref(i)) == ++id);
    }

    SECTION("disconnect")
    {
        unsigned int i = 0;
        unsigned int id = widget->onPositionChange.connect([&](){ i++; });

        widget->setPosition(10, 10);
        REQUIRE(i == 1);

        widget->onPositionChange.disconnect(id);
        widget->setPosition(20, 20);
        REQUIRE(i == 1);

        id = widget->connect("PositionChanged", [&](){ i++; });
        widget->setPosition(10, 10);
        REQUIRE(i == 2);

        widget->disconnect("PositionChanged", id);
        widget->setPosition(20, 20);
        REQUIRE(i == 2);

        widget->onPositionChange.connect([&](){ i++; });
        widget->onSizeChange.connect([&](){ i++; });
        widget->onPositionChange.disconnectAll();
        widget->setPosition(30, 30);
        widget->setSize(100, 25);
        REQUIRE(i == 3);

        widget->onPositionChange.connect([&](){ i++; });
        widget->connect("SizeChanged", [&](){ i++; });
        widget->disconnectAll("PositionChanged");
        widget->onSizeChange.disconnectAll();
        widget->setPosition(40, 40);
        widget->setSize(200, 50);
        REQUIRE(i == 3);
    }
}
