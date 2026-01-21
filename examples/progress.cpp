#include <algorithm>
#include <chrono>
#include <string>

#include <ox/ox.hpp>

using namespace ox;

class ProgressBar : public Widget {
   public:
    ProgressBar()
        : Widget{FocusPolicy::None, SizePolicy::flex()},
          timer_{*this, std::chrono::milliseconds{80}, true}
    {}

   public:
    void toggle_running()
    {
        if (timer_.is_running()) {
            timer_.stop();
        }
        else {
            timer_.start();
        }
    }

    [[nodiscard]] auto is_running() const -> bool { return timer_.is_running(); }

   public:
    void timer() override
    {
        percent_ = std::clamp(percent_ + direction_ * step_, 0, 100);
        if (percent_ == 0 || percent_ == 100) { direction_ *= -1; }
    }

    void paint(Canvas c) override
    {
        if (c.size.width <= 0 || c.size.height <= 0) { return; }

        fill(c, ' ');

        auto const bar_width = std::max(0, c.size.width - 2);
        auto const filled = (bar_width * percent_) / 100;

        auto bar = std::string{};
        bar.reserve((std::size_t)bar_width);
        bar.append((std::size_t)filled, '=');
        bar.append((std::size_t)(bar_width - filled), '.');

        put(c, {.x = 0, .y = 0}, "[" + bar + "]");

        auto const text = std::to_string(percent_) + "%";
        if (bar_width >= (int)text.size()) {
            auto const start = 1 + (bar_width - (int)text.size()) / 2;
            put(c, {.x = start, .y = 0}, text);
        }
    }

   private:
    int percent_ = 0;
    int direction_ = 1;
    int step_ = 2;
    Timer timer_;
};

int main()
{
    auto head =
        Column{
            Label{{
                .text = "Timed Progress",
                .align = Align::Center,
                .brush = {.traits = Trait::Bold},
                .size_policy = SizePolicy::fixed(1),
            }},
            ProgressBar{} | SizePolicy::fixed(1),
            Button{{
                .label = {.text = "Pause/Resume", .align = Align::Center},
                .size_policy = SizePolicy::fixed(1),
            }},
            Label{{
                .text = "Status: running",
                .align = Align::Left,
                .size_policy = SizePolicy::fixed(1),
            }},
        } |
        Border{
            .box = shape::Box::round(),
            .label = "Progress",
        };

    auto& [title, bar, toggle_btn, status] = head.child.children;

    Connection{
        .signal = toggle_btn.on_press,
        .slot = [](auto& bar, auto& status) {
            bar.toggle_running();
            status.text = bar.is_running() ? "Status: running" : "Status: paused";
        },
    }(bar, status);

    return Application{head}.run();
}
