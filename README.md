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

| 資料夾 | 放什麼 | 誰 |
| --- | --- | --- |
| `core/data/` | `types.h`（全組共用的 struct）、`DataStore` | B（`types.h`）、C |
| `core/street/`、`core/transit/` | 走路、YouBike、公車怎麼搭 | B |
| `core/planner/` | D1～D4 排行程、D5～D7 建議和替換 | B（D1～D4）、A（D5～D7） |
| `core/recommend/` | 打分數、推薦清單 | A |
| `core/cost/` | 車資、門票、餐費 | C |
| `core/session/` | `TripSession`（畫面只呼叫它）、`WebExporter` | A |
| `apps/console/`、`apps/qt/` | 畫面 | A |
| `tools/` | 抓 TDX、OpenStreetMap 的小程式 | C |
| `web/` | `map.html` 地圖網頁 | A |
| `data/csv/` | 整理好的 CSV（`data/raw/` 不進 Git） | C |
| `tests/` | doctest 測試，每個模組一個檔 | 各自 |

每個函式裡面都有 `TODO(任務編號)` 寫這裡要做什麼，任務編號對應分工表。
計劃書、分工、教學都在討論用的 repo，寫之前先看那邊。

## 規則（重點）

- 不要直接推到 `main`，開分支、開 Pull Request，另一個人看過再合併。
- `.h` 裡不寫 `using namespace std;`，`.cpp` 裡可以。
- `core/` 裡不 `cout`，結果回傳出去，只有 `apps/` 可以印東西。
- 時間是從 0:00 起算的分鐘（9:30 = 570），錢是元，都用 `int`。
- `.env`（TDX 金鑰）絕對不能 commit。
