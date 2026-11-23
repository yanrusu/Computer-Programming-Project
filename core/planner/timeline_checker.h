#pragma once
// D1 TimelineChecker：給一個順序，從出發時間一站一站算下去，回答「走得完嗎？每站幾點？」
// 貪婪、ILS、D4、建議、就近替換全部都靠它，所以一定要對、要快。
// 它不決定去哪裡、不改順序，只負責算。

#include <vector>
#include "data/data_store.h"
#include "data/types.h"
#include "transit/travel_oracle.h"

class TimelineChecker {
public:
    // 計劃書沒寫建構函式。要知道景點的開放時間（DataStore），還要問車程（TravelOracle）
    TimelineChecker(const DataStore& data, TravelOracle& travel);

    // 檢查 order 這個順序走不走得完，順便把每站的時間填好放在 timed。
    // 吃飯也是一站（kind == Meal、placeId == -1）
    CheckResult check(const std::vector<ItineraryStop>& order,
                      const TripRequest& req, const Settings& s);

private:
    const DataStore& data_;
    TravelOracle& travel_;
};
