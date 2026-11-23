#pragma once
// TripSession：服務層。畫面（console、Qt）只呼叫它，不直接碰下面的模組。
// 它記住每一輪的狀態、執行使用者的操作、決定什麼時候呼叫哪個模組。
// 自己不做計算，算東西都交給下面的模組；也不 cout，結果回傳給畫面去印。
//
// 所有模組都在這裡建一次，整個程式只有一份。

#include <string>
#include <vector>
#include "cost/cost_calculator.h"
#include "data/data_store.h"
#include "data/types.h"
#include "planner/advisor.h"
#include "planner/conflict_checker.h"
#include "planner/greedy_search.h"
#include "planner/ils_search.h"
#include "planner/meal_planner.h"
#include "planner/replacer.h"
#include "planner/time_bar.h"
#include "planner/timeline_checker.h"
#include "recommend/recommender.h"
#include "session/web_exporter.h"
#include "street/street_router.h"
#include "transit/fake_travel.h"
#include "transit/transit_router.h"

class TripSession {
public:
    TripSession();

    // 裡面的模組互相拿著參照，複製一份會出事，所以不准複製
    TripSession(const TripSession&) = delete;
    TripSession& operator=(const TripSession&) = delete;

    // 計劃書沒有這個。程式一開始呼叫一次：讀 CSV、建街道和交通圖。失敗回傳 false
    bool init(const std::string& csvDir);

    // ---- 開始 ----
    PlanResult start(const TripRequest& req, const Settings& s);   // 開始第一輪

    // ---- 重排模式：下面這些都先改草稿，按「執行」（replan）才真的排 ----
    void deletePlaces(const std::vector<int>& ids);   // 刪除
    void keepOnly(const std::vector<int>& ids);       // 只留這些
    void add(const std::vector<int>& ids);            // 從推薦清單新增
    void replace(int stopIndex, int newPlaceId);      // 替換某一站
    void restore(int placeId);                        // 取消刪除
    void changeSettings(const TripRequest& req, const Settings& s);  // 改時間或微調設定，不能改日期

    PlanResult replan();      // 執行：套用草稿，跑 D4 → D3，存成新的一輪
    void discardDraft();      // 取消：草稿丟掉，回到原本的行程

    // ---- 微調模式 ----
    PlanResult trim(const std::vector<int>& removeIds);   // 刪除、只留這些，馬上套用

    // ---- 衝突時 ----
    PlanResult applySuggestion(const Suggestion& sug);    // 套用一個建議
    void backToEdit();                                    // 返回修改，草稿保留

    // ---- 回到上一輪 ----
    bool undo();              // 已經是第一輪就回傳 false

    // ---- 給畫面顯示的資料 ----
    const Itinerary& itinerary() const;               // 目前這一輪的行程
    std::vector<int> recommendations() const;          // 推薦清單
    std::vector<int> deletedPlaces() const;            // 已刪除清單（可以取消刪除的）
    std::vector<int> replaceOptions(int stopIndex) const;  // 就近替換的選項
    int timeBarMinutes(const std::vector<int>& selected) const;  // 時間條要顯示的分鐘數

    // ---- 輸出 ----
    void exportWeb(const std::string& folder) const;  // 寫出網頁檔

private:
    // 宣告的順序就是建立的順序，後面的會用到前面的，不要隨便換位置
    DataStore data_;
    StreetRouter street_;
    FakeTravel fake_;           // 真的交通好之前先用這個
    TransitRouter transit_;     // 真的交通，做好後把下面幾行的 fake_ 換成 transit_
    CostCalculator cost_;
    Recommender rec_;
    TimelineChecker checker_;
    MealPlanner meals_;
    GreedySearch greedy_;
    IlsSearch ils_;
    ConflictChecker conflict_;
    Advisor advisor_;
    mutable Replacer replacer_; // replaceOptions 是 const，但 Replacer 會問車程（會記住算過的），所以要 mutable
    TimeBar timeBar_;
    WebExporter web_;

    std::vector<RoundState> history_;   // 每一輪疊起來，回到上一輪就是 pop_back
    RoundState draft_;                  // 重排模式裡改到一半的東西
    bool hasDraft_ = false;             // 現在是不是在重排模式
    Itinerary empty_;                   // 還沒開始排的時候，itinerary() 回傳這個
};
