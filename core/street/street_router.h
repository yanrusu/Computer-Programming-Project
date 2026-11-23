#pragma once
// StreetRouter：沿著真的街道算走路、騎 YouBike 要多久，還有地圖上要畫的線。
// 街道來自 OpenStreetMap（先轉成 CSV）。公車怎麼搭不歸它管，那是 TransitRouter 的事。
//
// 誰會用它：TransitRouter（建圖時要知道站牌之間走路多久）、畫地圖的時候。

#include <string>
#include <utility>
#include <vector>

class StreetRouter {
public:
    // 讀街道資料，建成一張圖。
    // 回傳：讀成功是 true
    bool load(const std::string& csvDir);

    // 兩個座標之間沿街道走路要幾分鐘。
    // 輸入：起點的緯度、經度，終點的緯度、經度
    // 回傳：分鐘數（整數，無條件進位）
    int walkMinutes(double lat1, double lon1, double lat2, double lon2) const;

    // 兩個座標之間沿街道騎 YouBike 要幾分鐘，借車、還車的時間也算進去
    int bikeMinutes(double lat1, double lon1, double lat2, double lon2) const;

    // 兩點之間沿街道要經過的座標，畫地圖用。
    // 回傳：一串（緯度, 經度），從起點排到終點
    std::vector<std::pair<double, double>> path(double lat1, double lon1,
                                                double lat2, double lon2) const;
};
