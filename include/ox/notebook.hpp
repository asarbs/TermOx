#pragma once

#include <memory>
#include <string>
#include <type_traits>
#include <utility>
#include <vector>


#include <ox/widget.hpp>
#include <ox/layout.hpp>
#include <ox/bordered.hpp>
#include <ox/button.hpp>



namespace ox {

class Notebook : public Widget {
    public:
        struct Page
        {
            std::string label;
            XColor background = XColor::Black;
            std::unique_ptr<Widget> content;
        };

        Row<std::vector<Bordered<Button>>> buttons;
        std::vector<Page> pages;
        std::size_t active = 0;
        static constexpr int button_row_height = 3;

        Notebook();

        void add_page(Page x);
        void select(std::size_t i);
        auto get_children() -> zzz::Generator<Widget&> override;
        void resize(Area) override;
        void close_active_page();
        void rebind_tab_buttons();
};

template <typename T>
auto make_widget(T&& widget) -> std::unique_ptr<Widget>
{
    using WidgetType = std::decay_t<T>;
    return std::make_unique<WidgetType>(std::forward<T>(widget));
}


} // namespace ox
