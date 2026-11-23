#include "session/web_exporter.h"
using namespace std;

// 為什麼是 .js 不是 .json：瀏覽器直接打開電腦裡的網頁（file://）時讀不到 .json，
// 但用 <script src="places.js"> 載得到 .js。
// 所以檔案內容就是一個 JavaScript 變數，例如：
//     const PLACES = [
//       {"name": "台中州廳", "lat": 24.1385, "lon": 120.6766},
//       ...
//     ];
// 用 ofstream 一行一行寫出去就好（教學 08 第 4 節）。
// 名字裡如果有 " 或 \ 要在前面多加一個 \，不然網頁會壞掉。

void WebExporter::writePlaces(const DataStore& data, const string& folder) const {
    // TODO 寫出 places.js。
    //
    // 這裡要做的事：
    // 1. ofstream 打開 folder + "/places.js"。
    // 2. 先寫 "const PLACES = [\n"。
    // 3. 每個地點寫一行 {...}，內容有：名字、緯度、經度、類別（地圖依類別上色）、開放時間。
    //    每一行最後加逗號。
    // 4. 最後寫 "];\n"。
}

void WebExporter::writeTrip(const Itinerary& it, const DataStore& data, const string& folder) const {
    // TODO 寫出 trip_data.js，寫法跟上面一樣，變數叫 TRIP。
    //
    // 內容：
    // 1. 每一站：名字（吃飯站寫「午餐」或「晚餐」）、座標、到達和離開時間。
    // 2. 每一段交通：每一小段的方式、路線名稱、上下車站、時間、path 座標。
    // 3. 車資、門票、餐費小計，還有 warnings。
}
