#pragma once
// D1 TimelineChecker：給一個順序，從出發時間一站一站算下去，回答「走得完嗎？每站幾點？」
// 它不決定去哪裡、不改順序，只負責算。
//
// 誰會用它：幾乎所有排行程的程式。貪婪、ILS、D4、建議、就近替換，
// 做法都是「改一下順序，丟給 D1 問行不行」，所以它一定要對、要快。

#include <vector>
#include "data/data_store.h"
#include "data/types.h"
#include "transit/travel_oracle.h"

class TimelineChecker {
public:
    // 建立的時候交給它兩樣東西：
    // DataStore 查開放時間、停留時間、門票；TravelOracle 問兩站之間要多久
    TimelineChecker(const DataStore& data, TravelOracle& travel);

    // 檢查一個順序走不走得完。
    // 輸入：order 是照順序排好的每一站（第一站是起點；有終點的話最後一站是終點；
    //       吃飯也是一站，kind 是 Meal）；req 是使用者的輸入；s 是設定
    // 回傳：CheckResult
    //       ok 走不走得完、reason 走不完的原因、
    //       timed 每站算好的到達／開始／離開時間、endMin 幾點結束、cost 總共花多少
    CheckResult check(const std::vector<ItineraryStop>& order,
                      const TripRequest& req, const Settings& s);

private:
    const DataStore& data_;         // 查景點資料
    TravelOracle& travel_;          // 問車程
};
