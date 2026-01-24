#include <ox/notebook.hpp>

namespace ox {

Notebook::Notebook() {
    buttons.children.emplace_back(
    Button{
                {
                .label =
                    {
                        .text = "x",
                        .brush =
                            {
                                .background = XColor::Red,
                                .traits     = Trait::Bold
                            },
                    },
                }
            } | Border{.box = shape::Box::round()}
    );
    Connection{
        .signal = buttons.children.back().child.on_press,
        .slot = [](Notebook& notebook) { notebook.close_active_page(); } ,
    }(*this);
}

void Notebook::add_page(Page x) {
    auto index = pages.size();
    buttons.children.emplace_back(
        Button{
            {
            .label =
                {
                    .text = " " + x.label + " ",
                    .brush =
                        {
                            .background = x.background,
                            .traits     = Trait::Bold
                        },
                },
            }
        } | Border{.box = shape::Box::round()}
    );
    pages.push_back({std::move(x.label), std::move(x.background), std::move(x.content)});
    if(active != index) {
        pages.back().content->active = false;
    }
    rebind_tab_buttons();
    this->resize(this->size);
}

void Notebook::select(std::size_t i) {
    if(i >= pages.size()) {
        return;
    }
    active = i;
    for(uint32_t index = 0 ; index < pages.size(); index++) {
        pages[index].content->active = index == i ? true : false;
    }
    this->resize(this->size);
}

auto Notebook::get_children() -> zzz::Generator<Widget&> {
    // First child: the button row.
    co_yield buttons;
    // Remaining children: each page's content widget.
    for (auto& page : pages) {
        co_yield *page.content;
    }
}

void Notebook::resize(Area)  {
    // Store previous size so buttons can react to resize.
    auto const old_buttons_size = buttons.size;
    // Place the button row at the top-left of the notebook.
    buttons.at = {0, 0};
    // Give the button row the full width and a fixed height of 3.
    buttons.size = {this->size.width, button_row_height};
    // Notify the button row about its new size.
    buttons.resize(old_buttons_size);

    // Resize and position each page below the button row.
    for (auto& page : pages) {
        // Access the page's content widget.
        auto& content = *page.content;
        // Store previous size so content can react to resize.
        auto const old_page_size = content.size;
        // Position content directly under the buttons.
        content.at = {0, button_row_height};
        // Give content the remaining space in the notebook.
        content.size = {
            .width = this->size.width,
            .height = std::max(0, this->size.height - button_row_height),
        };
        // Notify the content widget about its new size.
        content.resize(old_page_size);
    }
}

void Notebook::close_active_page() {
    if(pages.size() <= 1) {
        return;
    }
    auto button_to_close = buttons.children.begin() + active + 1;
    buttons.children.erase(button_to_close);

     auto page_to_close = pages.begin() + active;
     pages.erase(page_to_close);
     rebind_tab_buttons();

    active = std::min(active, pages.size()-1);
    select(active == 0 ? 0 : active - 1);

    this->resize(this->size);
}

void Notebook::rebind_tab_buttons() {
    for (std::size_t i = 0; i < pages.size(); ++i) {
        auto& button = buttons.children[i + 1].child; // +1 bo 0 to "x"
        button.on_press = {}; // usuń stare sloty
        Connection{
            .signal = button.on_press,
            .slot = [i](Notebook& notebook) { notebook.select(i); },
        }(*this);
    }
}

}; //namespace ox
