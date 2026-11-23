// 最基本的測試：確認骨架編得起來、doctest 接好了、預設值沒抄錯。
// 每個人寫自己的模組時，另外開一個 tests/test_模組.cpp，不要都塞在這裡。

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN   // 讓 doctest 幫我們寫 main()
#include "doctest.h"

#include <vector>
#include "data/data_store.h"
#include "data/types.h"
#include "session/trip_session.h"

TEST_CASE("Settings 的預設值跟計劃書一樣") {
    Settings s;
    CHECK(s.lunchFrom == 690);     // 11:30
    CHECK(s.lunchTo == 810);       // 13:30
    CHECK(s.dinnerFrom == 1050);   // 17:30
    CHECK(s.dinnerTo == 1170);     // 19:30
    CHECK(s.mealMin == 60);
    CHECK(s.mealBuffer == 15);
    CHECK(s.lunchCost == 250);
    CHECK(s.candidateCount == 30);
    CHECK(s.maxMustGo == 8);
    CHECK(s.ignoreBudget == false);
    CHECK(s.ignoreMeal == false);
}

TEST_CASE("沒填的欄位是 -1") {
    TripRequest req;
    CHECK(req.endPlace == -1);     // 沒有終點
    CHECK(req.budget == -1);       // 預算不限

    Place p;
    CHECK(p.openMin[0] == -1);     // 還沒填開放時間就當公休
    CHECK(p.rating == 3);          // 還沒評分就當 3 分

    ItineraryStop stop;
    CHECK(stop.placeId == -1);
    CHECK(stop.isDinner == false);
}

TEST_CASE("測試可以直接放手寫的地點進 DataStore，編號就是位置") {
    std::vector<Place> places(2);
    places[0].name = "台中車站";
    places[1].name = "台中州廳";

    DataStore data;
    data.setPlaces(places);

    REQUIRE(data.places().size() == 2);
    CHECK(data.place(1).name == "台中州廳");
    CHECK(data.place(1).id == 1);
}

TEST_CASE("TripSession 建得起來，還沒開始時行程是空的") {
    TripSession session;
    CHECK(session.itinerary().stops.empty());
    CHECK(session.undo() == false);
}
