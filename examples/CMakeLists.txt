# Pong ---------------------------------------------------------------------------------
add_executable(TermOx.examples.pong EXCLUDE_FROM_ALL
    pong.cpp
)
target_compile_options(
    TermOx.examples.pong
    PRIVATE
        -Wall
        -Wextra
        -Wpedantic
)
target_link_libraries(
    TermOx.examples.pong
    PRIVATE
        TermOx
)

# Pinbox -------------------------------------------------------------------------------
add_executable(TermOx.examples.pinbox EXCLUDE_FROM_ALL
    pinbox.cpp
)
target_compile_options(
    TermOx.examples.pinbox
    PRIVATE
        -Wall
        -Wextra
        -Wpedantic
)
target_link_libraries(
    TermOx.examples.pinbox
    PRIVATE
        TermOx
)

# Snake --------------------------------------------------------------------------------
add_executable(TermOx.examples.snake EXCLUDE_FROM_ALL
    snake.cpp
)
target_compile_options(
    TermOx.examples.snake
    PRIVATE
        -Wall
        -Wextra
        -Wpedantic
)
target_link_libraries(
    TermOx.examples.snake
    PRIVATE
        TermOx
)

# Accumulator --------------------------------------------------------------------------
add_executable(TermOx.examples.accumulator EXCLUDE_FROM_ALL
    accumulator.cpp
)
target_compile_options(
    TermOx.examples.accumulator
    PRIVATE
        -Wall
        -Wextra
        -Wpedantic
)
target_link_libraries(
    TermOx.examples.accumulator
    PRIVATE
        TermOx
)

# BMP Viewer ---------------------------------------------------------------------------
add_executable(TermOx.examples.bmp_view EXCLUDE_FROM_ALL
    bmp_view.cpp
)
target_compile_options(
    TermOx.examples.bmp_view
    PRIVATE
        -Wall
        -Wextra
        -Wpedantic
)
target_link_libraries(
    TermOx.examples.bmp_view
    PRIVATE
        TermOx
)

# Scratch ------------------------------------------------------------------------------
add_executable(TermOx.examples.scratch EXCLUDE_FROM_ALL
    scratch.cpp
)
target_compile_options(
    TermOx.examples.scratch
    PRIVATE
        -Wall
        -Wextra
        -Wpedantic
)
target_link_libraries(
    TermOx.examples.scratch
    PRIVATE
        TermOx
)

# Hello -------------------------------------------------------------------------------
add_executable(TermOx.examples.hello EXCLUDE_FROM_ALL
    hello.cpp
)
target_compile_options(
    TermOx.examples.hello
    PRIVATE
        -Wall
        -Wextra
        -Wpedantic
)
target_link_libraries(
    TermOx.examples.hello
    PRIVATE
        TermOx
)

# Form --------------------------------------------------------------------------------
add_executable(TermOx.examples.form EXCLUDE_FROM_ALL
    form.cpp
)
target_compile_options(
    TermOx.examples.form
    PRIVATE
        -Wall
        -Wextra
        -Wpedantic
)
target_link_libraries(
    TermOx.examples.form
    PRIVATE
        TermOx
)

# Progress ----------------------------------------------------------------------------
add_executable(TermOx.examples.progress EXCLUDE_FROM_ALL
    progress.cpp
)
target_compile_options(
    TermOx.examples.progress
    PRIVATE
        -Wall
        -Wextra
        -Wpedantic
)
target_link_libraries(
    TermOx.examples.progress
    PRIVATE
        TermOx
)

# Panels ------------------------------------------------------------------------------
add_executable(TermOx.examples.panels EXCLUDE_FROM_ALL
    panels.cpp
)
target_compile_options(
    TermOx.examples.panels
    PRIVATE
        -Wall
        -Wextra
        -Wpedantic
)
target_link_libraries(
    TermOx.examples.panels
    PRIVATE
        TermOx
)

#Tabs
add_executable(TermOx.examples.tabs EXCLUDE_FROM_ALL
    tabs.cpp
)
target_compile_options(
    TermOx.examples.tabs
    PRIVATE
        -Wall
        -Wextra
        -Wpedantic
)
target_link_libraries(
    TermOx.examples.tabs
    PRIVATE
        TermOx
)