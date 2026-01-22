#include <ox/ox.hpp>

using namespace ox;

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

        void add_page(Page x) {
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
            Connection{
                .signal = buttons.children.back().child.on_press,
                .slot = [index](Notebook& notebook) { notebook.select(index); },
            }(*this);
            this->resize(this->size);
        }

        void select(std::size_t i) {
            if(i >= pages.size()) {
                return;
            }
            active = i;
            for(uint32_t index = 0 ; index < pages.size(); index++) {
                pages[index].content->active = index == i ? true : false;
            }
            this->resize(this->size);
        }

        auto get_children() -> zzz::Generator<Widget&> override
        {
            // First child: the button row.
            co_yield buttons;
            // Remaining children: each page's content widget.
            for (auto& page : pages) {
                co_yield *page.content;
            }
        }

        void resize(Area) override {
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
};

template <typename T>
auto make_widget(T&& widget) -> std::unique_ptr<Widget>
{
    using WidgetType = std::decay_t<T>;
    return std::make_unique<WidgetType>(std::forward<T>(widget));
}

int main()
{
    auto upper_label = Label{{.text = "Upper label on first tab", .align = Align::Center}};

    auto lower_button = Button{{
        .label = {
            .text = "Lower Button on first tab",
            .brush = {
                .background = XColor::Blue,
                .traits = Trait::Bold,
            },
        },
        .size_policy = SizePolicy::fixed(1)
    }};

    auto notebook = Notebook{};
    auto first_tab_column = Column(std::move(upper_label), std::move(lower_button))
        | Border{.box = shape::Box::round(), .label = "First Tab Column with border"}
        | SizePolicy::fixed(16);
    auto& tab_1_button = get_child<1>(first_tab_column);

    uint32_t clickCounter = 6;
    Connection{
        .signal = tab_1_button.on_press,
        .slot = [&clickCounter] (auto& notebook) {
            std::string tabNameText = "Tab " + std::to_string(clickCounter);
            std::string tabContentLabelText = "Tab Content " + std::to_string(clickCounter);
            notebook.add_page({
                .label = tabNameText,
                .content = make_widget(Label{{.text = tabContentLabelText, .align = Align::Left }})
            });

            clickCounter++;
        }
    }(notebook);


    notebook.add_page({
        .label = "Tab 1",
        .background = XColor::BrightGreen,
        .content = make_widget(std::move(first_tab_column)),
    });
    notebook.add_page({
        .label = "Tab 2",
        .background = XColor::Yellow,
        .content = make_widget(Label{{.text = "Tab Content 2", .align = Align::Center}}),
    });

    notebook.add_page({
        .label = "Tab 3",
        .background = XColor::Red,
        .content = make_widget(Label{{.text = "Tab Content 3", .align = Align::Center}}),
    });

    notebook.add_page({
        .label = "Tab 4",
        .content = make_widget(Label{{.text = "Tab Content 4", .align = Align::Center}}),
    });

    notebook.add_page({
        .label = "Tab 5",
        .background = XColor::BrightMagenta,
        .content = make_widget(Label{{.text = "Tab Content 5", .align = Align::Center}}),
    });

    auto ui = std::move(notebook) | Border{.box = shape::Box::round(), .label = "Tabs"};

    return Application{ui}.run();
}
