#include "session/web_exporter.h"
using namespace std;

// 為什麼是 .js 不是 .json：瀏覽器用 file:// 直接打開本機網頁時讀不到 .json，
// 但 <script src="places.js"> 載得到。所以檔案內容就是一個 JavaScript 變數，
// 例如 const PLACES = [ {...}, {...} ];，用 ofstream 一行一行寫出去就好（教學 08 第 4 節）。
// 名字裡有引號或反斜線記得跳脫，不然網頁會壞掉。

void WebExporter::writePlaces(const DataStore& data, const string& folder) const {
    // TODO 每個地點寫：名字、座標、類別（地圖依類別上色）、開放時間。
    (void)data; (void)folder;
}

void WebExporter::writeTrip(const Itinerary& it, const DataStore& data, const string& folder) const {
    // TODO 每一站：名字、座標、到達和離開時間；每一段交通：每一小段的方式、路線名稱、path。
    // 再加上費用小計和 warnings，網頁上的行程表要用。
    (void)it; (void)data; (void)folder;
}
