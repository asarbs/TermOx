#include <string>

#include <ox/ox.hpp>

using namespace ox;

int main()
{
    auto head =
        Column{
            Label{{
                .text = "Profile Setup",
                .align = Align::Center,
                .brush = {.traits = Trait::Bold},
                .size_policy = SizePolicy::fixed(1),
            }},
            LineEdit{{
                .ghost_text = "Display name",
                .size_policy = SizePolicy::fixed(1),
            }},
            Row{
                CheckBox{} | SizePolicy::fixed(3),
                Label{{
                    .text = "Accept terms",
                    .align = Align::Left,
                }},
            } | SizePolicy::fixed(1),
            Button{{
                .label = {.text = "Submit", .align = Align::Center},
                .size_policy = SizePolicy::fixed(1),
            }},
            Label{{
                .text = "Status: waiting",
                .align = Align::Left,
                .size_policy = SizePolicy::fixed(1),
            }},
        } |
        Border{
            .box = shape::Box::round(),
            .label = "Form",
        };

    auto& [title, name_edit, options_row, submit_btn, status] = head.child.children;
    auto& [accept_box, accept_label] = options_row.children;

    Connection{
        .signal = name_edit.on_enter,
        .slot = [](std::string const& text, auto& status) {
            status.text = "Entered: " + text;
        },
    }(status);

    Connection{
        .signal = submit_btn.on_press,
        .slot = [](auto& name_edit, auto& status) {
            status.text = "Submitted: " + name_edit.text;
        },
    }(name_edit, status);

    Connection{
        .signal = accept_box.on_check,
        .slot = [](auto& status) { status.text = "Accepted terms"; },
    }(status);

    Connection{
        .signal = accept_box.on_uncheck,
        .slot = [](auto& status) { status.text = "Declined terms"; },
    }(status);

    return Application{head}.run();
}
