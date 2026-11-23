#pragma once
// TransitRouter：真的交通。
// 用公車時刻表算出「幾點從 A 出發，最早幾點到 B、怎麼搭」。
// 只有走路、YouBike、公車，沒有捷運和台鐵；路線一律選最早到的。
// 走路和騎車的時間問 StreetRouter，車資問 CostCalculator，自己不讀票價。
//
// 誰會用它：做好之後取代 FakeTravel，D1 和 TripSession 透過 TravelOracle 問它。

#include <string>
#include "cost/cost_calculator.h"
#include "data/data_store.h"
#include "data/types.h"
#include "street/street_router.h"
#include "transit/travel_oracle.h"

class TransitRouter : public TravelOracle {
public:
    // 讀公車、YouBike 的 CSV 建交通圖，程式一開始呼叫一次。
    // data、street、cost 會被記起來，之後算車程、車資時要用
    bool build(const DataStore& data, const StreetRouter& street,
               const CostCalculator& cost, const std::string& csvDir);

    // 設定星期幾、是不是假日，決定用平日還是假日的班表
    void setDay(int weekday, bool isHoliday);

    // 設定可以搭哪些交通（公車、YouBike）
    void setOptions(const TripRequest& req, const Settings& s);

    // 把記住的車程全部清掉。換日期、換交通方式之後要呼叫
    void clearCache();

    // fromPlace 在 departMin 出發，最早幾分鐘後到 toPlace、多少錢
    TravelInfo travel(int fromPlace, int toPlace, int departMin) override;

    // 同一段的完整交通：每一小段搭什麼、在哪上下車、幾點、多少錢、地圖上的線
    Leg travelDetail(int fromPlace, int toPlace, int departMin) override;

private:
    // build 的時候才拿得到，所以用指標記起來（一開始是 nullptr，表示還沒 build）
    const DataStore* data_ = nullptr;
    const StreetRouter* street_ = nullptr;
    const CostCalculator* cost_ = nullptr;
};
