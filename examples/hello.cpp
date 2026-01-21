#include <ox/ox.hpp>

using namespace ox;

int main()
{
    auto head =
        Label{{
            .text = "Hello TermOx",
            .align = Align::Center,
            .brush = {.foreground = XColor::BrightBlue, .traits = Trait::Bold},
        }} |
        Border{
            .box = shape::Box::round(),
            .label = "Example: Hello",
        };

    return Application{head}.run();
}
