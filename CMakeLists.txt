cmake_minimum_required(VERSION 3.8)

enable_testing()

project(spelunky_tools VERSION 1.0.0)


add_executable(SpelunkyHD_Save_Editor WIN32
    src/main.cpp
    src/editor.cpp
    src/element_editor.cpp
    src/input_element.cpp
    src/save.cpp
)

target_compile_features(SpelunkyHD_Save_Editor PUBLIC cxx_std_17)


target_include_directories(SpelunkyHD_Save_Editor PRIVATE
    include
)

target_link_libraries(SpelunkyHD_Save_Editor)

find_package(Threads)
find_package(wxWidgets REQUIRED core base adv richtext)

include(${wxWidgets_USE_FILE})

target_include_directories(SpelunkyHD_Save_Editor PRIVATE
    ${wxWidgets_INCLUDE_DIRS}
)

target_link_libraries(SpelunkyHD_Save_Editor PRIVATE
    Threads::Threads
    ${wxWidgets_LIBRARIES}
)


install(TARGETS SpelunkyHD_Save_Editor DESTINATION .)
install(FILES default_save.sav DESTINATION .)
