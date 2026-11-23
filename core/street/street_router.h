#pragma once
// StreetRouter：沿著真的街道算走路、騎 YouBike 要多久，還有地圖上要畫的線。
// 街道來自 OpenStreetMap（先轉成 CSV）。公車怎麼搭不歸它管，那是 TransitRouter 的事。

#include <string>
#include <utility>
#include <vector>

class StreetRouter {
public:
    // 讀街道 CSV 和步行時間快取。快取不存在就算一次、存起來，下次直接讀
    bool load(const std::string& csvDir);

    // 兩個座標之間沿街道走路要幾分鐘
    int walkMinutes(double lat1, double lon1, double lat2, double lon2) const;

    // 兩個座標之間沿街道騎 YouBike 要幾分鐘，借車、還車的時間也算進去
    int bikeMinutes(double lat1, double lon1, double lat2, double lon2) const;

    // 兩點之間沿街道的路線座標，畫地圖用
    std::vector<std::pair<double, double>> path(double lat1, double lon1,
                                                double lat2, double lon2) const;
};
