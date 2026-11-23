# web

地圖網頁放這裡（A 負責，A6）。

- `map.html`：樣板，用 Leaflet 畫地圖。這個要進 Git。
- `places.js`、`trip_data.js`：C++ 的 `WebExporter` 每次跑都會重寫，不進 Git。

用 `.js` 不用 `.json` 是因為瀏覽器用 `file://` 直接打開本機網頁時讀不到 `.json`，但 `<script src>` 載得到 `.js`。
打開網頁要有網路，地圖圖磚是從網路上抓的。
