# Qt 版。
# 還沒開始寫，所以這裡什麼都不編。開始做的時候大概會長這樣：
#
#   find_package(Qt6 REQUIRED COMPONENTS Widgets WebEngineWidgets)
#   qt_add_executable(ttp_qt main.cpp main_window.cpp)
#   target_link_libraries(ttp_qt PRIVATE core Qt6::Widgets Qt6::WebEngineWidgets)
#
# Windows 要用 MSVC 版的 Qt，MinGW 版沒有 WebEngine。
message(STATUS "Qt 版還沒開始寫，先跳過")
