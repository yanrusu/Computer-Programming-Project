#pragma once
// WebExporter：寫出地圖網頁要用的資料檔（A 負責，A6）。
// 只寫 places.js 和 trip_data.js 兩個資料檔，網頁本身是 web/map.html，不用 C++ 產生。

#include <string>
#include "data/data_store.h"
#include "data/types.h"

class WebExporter {
public:
    // 寫出 places.js：所有景點，總覽地圖用
    void writePlaces(const DataStore& data, const std::string& folder) const;

    // 寫出 trip_data.js：排好的行程，行程表和地圖用
    void writeTrip(const Itinerary& it, const DataStore& data, const std::string& folder) const;
};
