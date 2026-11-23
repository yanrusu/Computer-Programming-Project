#include "planner/timeline_checker.h"
using namespace std;

TimelineChecker::TimelineChecker(const DataStore& data, TravelOracle& travel)
    : data_(data), travel_(travel) {}

CheckResult TimelineChecker::check(const vector<ItineraryStop>& order,
                                   const TripRequest& req, const Settings& s) {
    // TODO 從 req.startMin 出發，照順序一站一站算（教學 10 第 7 節）：
    //
    //   到達 = 上一站離開 + 車程（travel_.travel(上一站, 這一站, 上一站離開時間)）
    //   開始 = max(到達, 開門)              早到就等開門，等多久都可以
    //   離開 = 開始 + 停留 × s.paceFactor
    //   離開 > 關門        → 走不完，reason 寫「待不滿就關門了」之類的
    //   公休（開門是 -1）  → 走不完
    //
    // 吃飯站（kind == Meal）：
    //   不算車程，當作在上一站附近吃。開始吃的時間要落在用餐時段內，太早就等。
    //   佔 s.mealMin + s.mealBuffer 分鐘，花 s.lunchCost 元。
    //
    // 最後：
    //   有終點（req.endPlace != -1）：結束時間 = 到達終點的時間
    //   沒終點：結束時間 = 最後一站的離開時間
    //   結束時間 > req.endMin → 走不完
    //   車資＋門票＋餐費 > req.budget（不是 -1 的話）→ 走不完
    //
    // 先寫最基本的（到達、等開門、停留、關門），測試過了再一項一項加。
    // 六種測試：早到等開門、待不滿就關門、超過結束時間、有終點、吃飯站、超過預算。
    (void)order; (void)req; (void)s;
    return {};
}
