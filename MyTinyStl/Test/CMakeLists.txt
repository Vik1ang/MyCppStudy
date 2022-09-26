include_directories(${PROJECT_SOURCE_DIR}/MyTinySTL)
set(APP_SRC test.cpp)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/cmake-build-debug)
add_executable(stltest ${APP_SRC})