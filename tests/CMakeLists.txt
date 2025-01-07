find_package(GTest CONFIG REQUIRED)

add_executable(EventLib.Tests tests_event.cpp)
target_link_libraries(EventLib.Tests GTest::gtest_main)
target_link_options(EventLib.Tests PRIVATE -fsanitize=address)