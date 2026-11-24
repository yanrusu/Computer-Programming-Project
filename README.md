# Taichung Transit Planner｜台中大眾運輸行程規劃

計算機程式設計期末專題的程式碼（C++17、CMake）。

「不開車也能玩台中」：使用者給起點、時間和興趣，程式只用公車、YouBike 和步行，推薦景點、排出順序，並算出每一段的時間和費用。

## 編譯和測試

```bash
cmake -S . -B build
cmake --build build
ctest --test-dir build
```

- 第一行只有第一次、或改了 `CMakeLists.txt` 之後才需要。
- console 版的執行檔是 `build/ttp`（Windows 是 `build\Debug\ttp.exe`）。
- 想看哪一行測試沒過，直接跑那個測試檔，例如 `./build/test_smoke`。
- 編譯出怪問題時，把 `build/` 整個刪掉重來。
- Qt 版預設不編，要編加 `-DBUILD_QT=ON`。

## 資料夾

| 資料夾 | 放什麼 |
| --- | --- |
| `core/data/` | `types.h`（全組共用的 struct）、`DataStore` |
| `core/street/`、`core/transit/` | 走路、YouBike、公車怎麼搭 |
| `core/planner/` | `Planner`（D1～D4 排行程）、`Advisor`（D5～D7 建議、替換、時間條） |
| `core/recommend/` | 打分數、推薦清單 |
| `core/cost/` | 車資、門票、餐費 |
| `core/session/` | `TripSession`（畫面只呼叫它）、`WebExporter` |
| `apps/console/`、`apps/qt/` | 畫面 |
| `tools/` | 抓 TDX、OpenStreetMap 的小程式 |
| `web/` | `map.html` 地圖網頁 |
| `data/csv/` | 整理好的 CSV（`data/raw/` 不進 Git） |
| `tests/` | doctest 測試，每個模組一個檔 |
