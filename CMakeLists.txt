cmake_minimum_required(VERSION 3.16)
project(TaichungTransitPlanner LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Windows 的 MSVC 不加這個會把中文原始碼讀成亂碼
if(MSVC)
    add_compile_options(/utf-8)
endif()

# Qt 版和抓資料工具要裝 Qt 才編得起來，所以預設關掉。
# 要編的時候：cmake -S . -B build -DBUILD_QT=ON
option(BUILD_QT "編 Qt 版和抓資料工具" OFF)

# ---------------------------------------------------------------
# core：所有計算的程式都在這裡，編成一個靜態程式庫。
# console、Qt、測試、工具都連結同一個 core，計算只寫一次。
# 新增 .cpp 記得加進這個清單（.h 不用加），不然會看到 undefined reference。
# ---------------------------------------------------------------
add_library(core STATIC
    # 資料
    core/data/data_store.cpp

    # 交通
    core/street/street_router.cpp
    core/transit/fake_travel.cpp
    core/transit/transit_router.cpp

    # 費用
    core/cost/cost_calculator.cpp

    # 推薦
    core/recommend/recommender.cpp

    # 排行程（D1～D7）
    core/planner/timeline_checker.cpp
    core/planner/meal_planner.cpp
    core/planner/greedy_search.cpp
    core/planner/ils_search.cpp
    core/planner/conflict_checker.cpp
    core/planner/advisor.cpp
    core/planner/replacer.cpp
    core/planner/time_bar.cpp

    # 服務層和網頁輸出
    core/session/trip_session.cpp
    core/session/web_exporter.cpp
)
# #include "transit/fake_travel.h" 這種寫法，從 core/ 開始找
target_include_directories(core PUBLIC core)

# ---------------------------------------------------------------
# console 版，執行檔叫 ttp
# ---------------------------------------------------------------
add_executable(ttp apps/console/main.cpp)
target_link_libraries(ttp PRIVATE core)

# ---------------------------------------------------------------
# 測試：每個模組一個 tests/test_模組.cpp。
# 加新的測試就照下面三行抄一組，改名字就好。
# ---------------------------------------------------------------
enable_testing()

add_executable(test_smoke tests/test_smoke.cpp)
target_link_libraries(test_smoke PRIVATE core)
add_test(NAME smoke COMMAND test_smoke)

# ---------------------------------------------------------------
# Qt 版和抓資料工具（需要 Qt）
# ---------------------------------------------------------------
if(BUILD_QT)
    add_subdirectory(apps/qt)
    add_subdirectory(tools)
endif()
