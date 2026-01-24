#include <ox/ox.hpp>

#include <ox/notebook.hpp>

using namespace ox;


auto make_right_panel()
{
    auto upper_label = Label{{.text = "Upper label on first tab", .align = Align::Center}};

    auto notebook = Notebook{};
    auto first_tab_column = Column(std::move(upper_label))
        | Border{.box = shape::Box::round(), .label = "First Tab Column with border"}
        | SizePolicy::fixed(16);

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
    return notebook;
}

auto make_left_panel()
{

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


    auto right_label = Label{{.text = "Right panel (fixed 60)", .align = Align::Center}};
    return Column{std::move(right_label), std::move(lower_button)}
        | Border{.box = shape::Box::round(), .label = "Right"}
        | SizePolicy::fixed(32);
}

auto make_divider()
{
    return Divider{{.lines = Lines::bold(), .brush = {.foreground = XColor::BrightBlack}}};
}

int main()
{
    auto left_panel = make_left_panel();
    auto& lower_button = get_child<1>(left_panel);
    auto notebook = make_right_panel();

    uint32_t clickCounter = 6;
    Connection{
        .signal = lower_button.on_press,
        .slot = [&clickCounter](auto& notebook) {
            std::string tabNameText = "Tab " + std::to_string(clickCounter);
            std::string tabContentLabelText = "Tab Content " + std::to_string(clickCounter);
            notebook.add_page({
                .label = tabNameText,
                .content = make_widget(Label{{.text = tabContentLabelText, .align = Align::Left }})
            });

            clickCounter++;
        }
    }(notebook);

    auto main_screen = Row{std::move(left_panel), make_divider(), std::move(notebook)}
        | Border{.box = shape::Box::round(), .label = "Main Box"};

    auto ui = std::move(main_screen) | Border{.box = shape::Box::round(), .label = "Tabs"};

    return Application{ui}.run();
}
