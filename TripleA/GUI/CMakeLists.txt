cmake_minimum_required(VERSION "3.13.4")
add_compile_options(-Wall)

include_directories(../../external/json/single_include)

find_package(Threads REQUIRED)

set(Sources
    main.cpp
    Application.cpp
    Visualization.cpp
    MenuState.cpp
    Widgets/IWidget.cpp
    Widgets/Button.cpp
    Widgets/Listener.cpp
    Widgets/Slider.cpp
)

set(Headers
    Visualization.hpp
    Application.h
    ApplicationState.h
    MenuState.h
    Widgets/IWidget.h
    Widgets/Button.h
    Widgets/Listener.h
    Widgets/Slider.h
)


set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
add_executable(simulation ${Sources} ${Headers})
target_link_libraries(simulation sfml-graphics sfml-audio)
target_link_libraries(simulation ${CMAKE_THREAD_LIBS_INIT})
target_link_libraries(simulation stdc++fs)
message(STATUS ${CMAKE_THREAD_LIBS_INIT})
