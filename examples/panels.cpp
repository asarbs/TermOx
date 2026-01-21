#include <ox/ox.hpp>

#include <utility>

using namespace ox;

auto make_left_panel()
{
    auto left_label = Label{{.text = "Left up panel (fixed 20)", .align = Align::Center}};
    auto left_button = Button{{
        .label = {
            .text = "Button",
            .brush = {
                .background = XColor::BrightBlue,
                .foreground = XColor::BrightMagenta,
                .traits     = Trait::Bold
            },
        },
        .size_policy = SizePolicy::fixed(2),
    }};

    return Column{std::move(left_label), std::move(left_button)}
        | Border{.box = shape::Box::round(), .label = "Left"}
        | SizePolicy::fixed(16);
}

auto make_right_panel()
{
    auto right_label = Label{{.text = "Right panel (fixed 60)", .align = Align::Center}};
    return Column{std::move(right_label)}
        | Border{.box = shape::Box::round(), .label = "Right"}
        | SizePolicy::flex();
}

auto make_divider()
{
    return Divider{{.lines = Lines::bold(), .brush = {.foreground = XColor::BrightBlack}}};
}

int main()
{
    auto head =
        Row{make_left_panel(), make_divider(), make_right_panel()}
        | Border{.box = shape::Box::round(), .label = "Main Box"};


        auto& [leftColumn, div, rightColumn] =  head.child.children;
        auto& left_top_label = get_child<0>(leftColumn);
        auto& button = get_child<1>(leftColumn);

        auto& rightLabel = get_child<0>(rightColumn);
        uint32_t clickCounter = 0;
        Connection{
            .signal = button.on_press,
            .slot = [&clickCounter] (auto& rightLabel) {
                clickCounter++;
                rightLabel.text = "Button pressed " + std::to_string(clickCounter);
            }
        }(rightLabel);

    return Application{head}.run();
}
