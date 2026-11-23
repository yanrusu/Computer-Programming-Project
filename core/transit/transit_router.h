#pragma once
// TransitRouter：真的交通。
// 用路線節點圖＋看時刻表的 Dijkstra，算出「幾點從 A 出發，最早幾點到 B、怎麼搭」。
// 只有走路、YouBike、公車，沒有捷運和台鐵；路線一律選最早到的。
// 走路和騎車的時間跟 StreetRouter 要，車資跟 CostCalculator 要，自己不讀票價。

#include <string>
#include "data/data_store.h"
#include "data/types.h"
#include "street/street_router.h"
#include "transit/travel_oracle.h"

class TransitRouter : public TravelOracle {
public:
    // 讀公車、YouBike 的 CSV 建路線節點圖。程式一開始呼叫一次
    bool build(const DataStore& data, const StreetRouter& street, const std::string& csvDir);

    // 設定星期幾、是不是假日，決定用哪一套班表
    void setDay(int weekday, bool isHoliday);

    // 設定可以搭哪些交通。會把記住的車程清掉，因為答案可能不一樣了
    void setOptions(const TripRequest& req, const Settings& s);

    // 把記住的車程全部清掉
    void clearCache();

    TravelInfo travel(int fromPlace, int toPlace, int departMin) override;
    Leg travelDetail(int fromPlace, int toPlace, int departMin) override;
};
