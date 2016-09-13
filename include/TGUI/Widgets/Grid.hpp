/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// TGUI - Texus' Graphical User Interface
// Copyright (C) 2012-2016 Bruno Van de Velde (vdv_b@tgui.eu)
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


#ifndef TGUI_GRID_HPP
#define TGUI_GRID_HPP


#include <TGUI/Container.hpp>

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace tgui
{
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    class TGUI_API Grid : public Container
    {
    public:

        typedef std::shared_ptr<Grid> Ptr; ///< Shared widget pointer
        typedef std::shared_ptr<const Grid> ConstPtr; ///< Shared constant widget pointer


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief The alignment of the widget in its cell
        ///
        /// Where in the cell is the widget located?
        /// The widget is centered by default.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        enum class Alignment
        {
            UpperLeft,   ///< Draw the widget in the upper left corner of the cell
            Up,          ///< Draw the widget at the upper side of the cell (horizontally centered)
            UpperRight,  ///< Draw the widget in the upper right corner of the cell
            Right,       ///< Draw the widget at the right side of the cell (vertically centered)
            BottomRight, ///< Draw the widget in the bottom right corner of the cell
            Bottom,      ///< Draw the widget at the bottom of the cell (horizontally centered)
            BottomLeft,  ///< Draw the widget in the bottom left corner of the cell
            Left,        ///< Draw the widget at the left side of the cell (vertically centered)
            Center       ///< Center the widget in the cell
        };


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Default constructor
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        Grid();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Copy constructor
        ///
        /// @param copy  Instance to copy
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        Grid(const Grid& copy);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Overload of assignment operator
        ///
        /// @param right  Instance to assign
        ///
        /// @return Reference to itself
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        Grid& operator= (const Grid& right);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Makes a copy of another grid
        ///
        /// @param grid  The other grid
        ///
        /// @return The new grid
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        static Grid::Ptr copy(Grid::ConstPtr grid);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Changes the size of the grid
        ///
        /// @param size   New size of the grid
        ///
        /// Widgets in the grid will be repositionned to fill in the best way the available space of the grid.
        /// If the size is too small to have all Widgets correctly placed, the size will be ignored and the grid auto-sized until
        /// some Widgets are removed of the grid and the size was become valid again.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void setSize(const Layout2d& size) override;
        using Transformable::setSize;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns the size of the grid
        ///
        /// @return Size of the grid
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual sf::Vector2f getSize() const override;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Removes a single widget that was added to the container
        ///
        /// @param widget  Pointer to the widget to remove
        ///
        /// @see remove(sf::String)
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual bool remove(const Widget::Ptr& widget) override;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Removes all widgets that were added to the container
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void removeAllWidgets() override;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Adds a widget to the grid
        ///
        /// @param widget    Pointer to a fully created widget that will be added to the grid
        /// @param row       The row in which the widget should be placed
        /// @param column    The column in which the widget should be placed
        /// @param borders   Distance from the grid cell to the widget (left, top, right, bottom)
        /// @param alignment Where the widget is located in the cell
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void addWidget(const Widget::Ptr& widget,
                       std::size_t        row,
                       std::size_t        column,
                       const Borders&     borders   = Borders{0},
                       Alignment          alignment = Alignment::Center);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns the widget in a specific cell of the grid
        ///
        /// @param row     The row that the widget is in
        /// @param column  The column that the widget is in
        ///
        /// @return The widget inside the given cell, or nullptr when the cell doesn't contain a widget
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        Widget::Ptr getWidget(std::size_t row, std::size_t column) const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Changes borders of a given widget
        ///
        /// @param widget  The widget to which borders should be added
        /// @param borders The new borders around the widget
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setWidgetBorders(const Widget::Ptr& widget, const Borders& borders = Borders(0, 0, 0, 0));


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Changes borders of a widget in a certain cell
        ///
        /// @param row     The row that the widget is in
        /// @param column  The column that the widget is in
        /// @param borders The new borders around the widget
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setWidgetBorders(std::size_t row, std::size_t column, const Borders& borders = Borders(0, 0, 0, 0));


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns the borders around a widget in a specific cell of the grid
        ///
        /// @param row     The row that the widget is in
        /// @param column  The column that the widget is in
        ///
        /// @return The borders inside the given cell, or Borders{0} when the cell doesn't contain a widget
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        Borders getWidgetBorders(std::size_t row, std::size_t column) const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Changes the alignment of a given widget in its cell
        ///
        /// @param widget    The widget for which the alignment should be changed
        /// @param alignment The new alignment
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setWidgetAlignment(const Widget::Ptr& widget, Alignment alignment = Alignment::Center);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Changes the alignment of a given widget in its cell
        ///
        /// @param row       The row that the widget is in
        /// @param column    The column that the widget is in
        /// @param alignment The new alignment
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setWidgetAlignment(std::size_t row, std::size_t column, Alignment alignment = Alignment::Center);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns the alignment of a given widget in its cell
        ///
        /// @param row     The row that the widget is in
        /// @param column  The column that the widget is in
        ///
        /// @return The alignment inside the given cell, or Grid::Alignment::Center when the cell doesn't contain a widget
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        Alignment getWidgetAlignment(std::size_t row, std::size_t column) const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns the widgets and their positions in the grid
        ///
        /// @return grid of widgets
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        const std::vector<std::vector<Widget::Ptr>>& getGridWidgets() const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @internal
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual bool mouseOnWidget(sf::Vector2f pos) const override;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    protected:


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Returns the minimum size required by the grid to display correctly all widgets.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        sf::Vector2f getMinSize();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Reposition all the widgets.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void updatePositionsOfAllWidgets();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Updates the position and size of the widget
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void updateWidgets();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Draws the widget on the render target.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Makes a copy of the widget
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual Widget::Ptr clone() const override
        {
            return std::make_shared<Grid>(*this);
        }


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    protected:

        std::vector<std::vector<Widget::Ptr>> m_gridWidgets;
        std::vector<std::vector<Borders>>     m_objBorders;
        std::vector<std::vector<Alignment>>   m_objAlignment;

        std::vector<float> m_rowHeight;
        std::vector<float> m_columnWidth;

        std::map<Widget::Ptr, unsigned int> m_connectedCallbacks;

        sf::Vector2f m_realSize; // Actual size of the grid, while m_size contains the intended size

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    };

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif // TGUI_GRID_HPP
