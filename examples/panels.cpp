#include <ox/ox.hpp>

using namespace ox;

int main()
{
    auto head =
        Row{
            Column{
                Label{{.text = "Left up panel (fixed 20)", .align = Align::Center}},
                Button{{
                    .label = {
                        .text = "Button",
                        .brush = {
                            .background = XColor::BrightBlue,
                            .foreground = XColor::BrightMagenta,
                            .traits     = Trait::Bold
                        },
                    },
                    .size_policy = SizePolicy::fixed(2),
                }},
            } | Border{.box = shape::Box::round(), .label = "Left"} | SizePolicy::fixed(16) ,

            Divider{{.lines = Lines::bold(), .brush = {.foreground = XColor::BrightBlack}}},

            Column{
                Label{{.text = "Right panel (fixed 60)", .align = Align::Center}},
            } | Border{.box = shape::Box::round(), .label = "Right"} | SizePolicy::flex() ,
        } | Border {.box = shape::Box::round(), .label="Main Box"};


        auto& [leftColumn, div, rightColumn] =  head.child.children;
        auto& left_top_label = get_child<0>(leftColumn);
        auto& button = get_child<1>(leftColumn);

        auto& rightLabel = get_child<0>(rightColumn);
        uint32_t clickCounter = 0;
        Connection{
            .signal = button.on_press,
            .slot = [&clickCounter] (auto& rightLabel) {
                clickCounter++;
                rightLabel.text = "Button pressed" + std::to_string(clickCounter);
            }
        }(rightLabel);

    return Application{head}.run();
}
