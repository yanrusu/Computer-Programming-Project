#pragma once
// TripSession：服務層。畫面（console、Qt）只呼叫它，不直接碰下面的模組。
// 它記住每一輪的狀態、執行使用者的操作、決定什麼時候呼叫哪個模組。
// 自己不做計算，算東西都交給下面的模組；也不 cout，結果回傳給畫面去印。
//
// 所有模組都在這裡建一次，整個程式只有一份 TripSession，不要複製它。

#include <set>
#include <string>
#include <vector>
#include "cost/cost_calculator.h"
#include "data/data_store.h"
#include "data/types.h"
#include "planner/advisor.h"
#include "planner/planner.h"
#include "recommend/recommender.h"
#include "session/web_exporter.h"
#include "street/street_router.h"
#include "transit/fake_travel.h"
#include "transit/transit_router.h"
#include "transit/travel_oracle.h"

class TripSession {
public:
    // 把所有模組建起來，互相接好
    TripSession();

    // 程式一開始呼叫一次：讀 CSV、建街道和交通圖。
    // 回傳：都成功是 true
    bool init(const std::string& csvDir);

    // ---- 開始 ----
    // 開始第一輪：用使用者的輸入排出第一份行程
    PlanResult start(const TripRequest& req, const Settings& s);

    // ---- 重排模式：下面這些都只改草稿，按「執行」（replan）才真的排 ----
    void deletePlaces(const std::vector<int>& ids);   // 刪除這些景點
    void keepOnly(const std::vector<int>& ids);       // 只留這些，其他的刪除
    void add(const std::vector<int>& ids);            // 從推薦清單新增，變成一定要去
    void replace(int stopIndex, int newPlaceId);      // 第 stopIndex 站換成 newPlaceId
    void restore(int placeId);                        // 取消刪除
    void changeSettings(const TripRequest& req, const Settings& s);  // 改時間或設定，不能改日期

    PlanResult replan();      // 按「執行」：照草稿重新排，存成新的一輪
    void discardDraft();      // 按「取消」：草稿丟掉，回到原本的行程

    // ---- 微調模式 ----
    // 拿掉這幾站，馬上套用、重算時間，不補新景點，存成新的一輪
    PlanResult trim(const std::vector<int>& removeIds);

    // ---- 排不下的時候 ----
    PlanResult applySuggestion(const Suggestion& sug);    // 套用一個建議，再排一次
    void backToEdit();                                    // 「返回修改」，草稿保留

    // ---- 回到上一輪 ----
    bool undo();              // 回到上一輪。已經是第一輪就回傳 false

    // ---- 給畫面顯示的資料 ----
    const Itinerary& itinerary() const;               // 目前這一輪的行程
    std::vector<int> recommendations() const;          // 推薦清單
    std::vector<int> deletedPlaces() const;            // 已刪除的景點（可以取消刪除）
    std::vector<int> replaceOptions(int stopIndex);    // 第 stopIndex 站可以換成哪些景點
    int timeBarMinutes(const std::vector<int>& selected) const;  // 時間條：勾了這些大概要幾分鐘

    // ---- 輸出 ----
    void exportWeb(const std::string& folder) const;  // 寫出網頁要用的資料檔

private:
    // 注意：宣告的順序就是建立的順序，後面的會用到前面的，不要隨便換位置。
    // 由上往下就是依賴的順序：資料 → 交通 → 推薦 → 排行程 → 建議。
    DataStore data_;            // 資料
    StreetRouter street_;
    FakeTravel fake_;           // 假的交通（直線距離）
    TransitRouter transit_;     // 真的交通
    TravelOracle& travel_;      // 排行程時用哪一種交通。現在是 fake_，真的交通做好後在建構函式改成 transit_
    CostCalculator cost_;
    Recommender rec_;           // 推薦
    Planner planner_;           // 排行程 D1～D4
    Advisor advisor_;           // 建議、替換、時間條 D5～D7
    WebExporter web_;

    std::vector<RoundState> history_;   // 每一輪疊起來，最後一個是現在。回到上一輪就是 pop_back
    RoundState draft_;                  // 重排模式裡改到一半的東西
    bool hasDraft_ = false;             // 現在是不是在重排模式
    std::set<int> justAdded_;           // 這一輪剛新增的景點（D5 建議要用）
    Itinerary empty_;                   // 還沒開始排的時候，itinerary() 回傳這個空的
};
