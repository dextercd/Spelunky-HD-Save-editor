cmake_minimum_required(VERSION 3.8)

enable_testing()

project(spelunky_tools)


add_executable(save_editor
  "src/main.cpp"
  "src/editor.cpp"
  "src/element_editor.cpp"
  "src/input_element.cpp"
  "src/save.cpp"
)

target_compile_features(save_editor PUBLIC cxx_std_17)


target_include_directories(save_editor PRIVATE
  "include"
)

target_link_libraries(save_editor)

find_package(Threads)
find_package(wxWidgets REQUIRED core base adv richtext)

include(${wxWidgets_USE_FILE})

target_include_directories(save_editor PRIVATE
	${wxWidgets_INCLUDE_DIRS}
)

target_link_libraries(save_editor PRIVATE
	${CMAKE_THREAD_LIBS_INIT}
	${wxWidgets_LIBRARIES}
)

