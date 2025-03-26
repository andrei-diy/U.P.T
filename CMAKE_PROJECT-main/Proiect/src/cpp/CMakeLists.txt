add_library(
    header
    Device.cpp
    User.cpp
    Laptop.cpp
    Label.cpp
)
target_include_directories(header PUBLIC "${PROJECT_SOURCE_DIR}/hpp")
#target_include_directories(header PUBLIC "${CMAKE_CURENT_SOURCE_DIR}/cpp")
