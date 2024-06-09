# Получаем имя текущего каталога
get_filename_component(CURRENT_DIR_NAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)
# glob all cpp and hpp files in the current directory
file(GLOB_RECURSE SOURCES "*.cpp" "*.hpp" "*.h")
message(STATUS "SOURCES: ${SOURCES}")
add_executable(${CURRENT_DIR_NAME} ${SOURCES})
gtest_discover_tests(${CURRENT_DIR_NAME})
target_link_libraries(${CURRENT_DIR_NAME} gtest_main)
