# 離線工具（C 負責）：抓 TDX、抓 OpenStreetMap 街道、整理站到站票價表、算步行時間。
# 每個工具是獨立的小程式，只有整理資料的人需要跑，主程式只讀它們產生的 CSV。
#
# 抓 TDX 會用到 Qt Network 和 QJsonDocument，所以放在 BUILD_QT 底下。
# 金鑰放在專案最外層的 .env，不要寫死在程式裡，也不要 commit。
#
# 還沒開始寫，先跳過。加第一個工具時大概像這樣：
#
#   find_package(Qt6 REQUIRED COMPONENTS Core Network)
#   add_executable(fetch_tdx fetch_tdx.cpp)
#   target_link_libraries(fetch_tdx PRIVATE core Qt6::Core Qt6::Network)
message(STATUS "抓資料工具還沒開始寫，先跳過")
