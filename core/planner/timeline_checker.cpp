#include "planner/timeline_checker.h"
using namespace std;

// 把傳進來的東西記在 data_ 和 travel_，check 要用
TimelineChecker::TimelineChecker(const DataStore& data, TravelOracle& travel)
    : data_(data), travel_(travel) {}

CheckResult TimelineChecker::check(const vector<ItineraryStop>& order,
                                   const TripRequest& req, const Settings& s) {
    // TODO 從出發時間開始，照順序一站一站算（教學 10 第 7 節）。
    //
    // 準備：
    //   result.timed 先複製一份 order，等一下把時間填進去。
    //   現在時間 now = req.startMin，現在位置 here = 第一站（起點）的 placeId，花費 cost = 0。
    //   起點那一站：到達 = 開始 = 離開 = req.startMin。
    //
    // 從第二站開始，用 for 迴圈一站一站看：
    //
    // ■ 如果這站是景點（kind == Spot）或終點（kind == End）：
    //   1. 問車程：info = travel_.travel(here, 這站的 placeId, now)
    //      到不了（info.reachable 是 false）→ 走不完。
    //   2. 到達 = now + info.minutes，cost 加上 info.fare。
    //   3. 終點的話：到達就結束了，開始 = 離開 = 到達。
    //   4. 景點的話：
    //      開門 = 這個景點的 openMin[req.weekday]，關門 = closeMin[req.weekday]
    //      開門是 -1（公休）→ 走不完。
    //      開始 = 到達和開門比較大的那個（早到就等開門，等多久都可以）
    //      離開 = 開始 + 停留時間 × s.paceFactor（四捨五入成整數）
    //      離開 > 關門 → 走不完（待不滿就關門了）
    //      cost 加上門票。
    //   5. 填進 result.timed[i]，now = 離開，here = 這站的 placeId。
    //
    // ■ 如果這站是吃飯（kind == Meal）：
    //   1. 在上一站附近吃，不用車程，到達 = now，here 不變。
    //   2. 用 isDinner 看是午餐還是晚餐，拿對應的時段（s.lunchFrom～s.lunchTo，或晚餐那組）。
    //   3. 開始 = 到達和時段開始比較大的那個（太早就等）。
    //      開始 > 時段結束 → 走不完（錯過吃飯時間）。
    //   4. 離開 = 開始 + s.mealMin + s.mealBuffer，cost 加上 s.lunchCost。
    //   5. 填進 result.timed[i]，now = 離開。
    //
    // 全部算完：
    //   結束時間 endMin = 最後一站的離開時間（如果最後一站是終點，就是到達終點的時間）。
    //   endMin > req.endMin → 走不完（超過結束時間）。
    //   沒有選忽略預算（s.ignoreBudget 是 false）、有填預算（req.budget 不是 -1），
    //   而且 cost > req.budget → 走不完（超過預算）。
    //   都沒問題就 ok = true，填好 endMin、cost。
    //
    // 走不完的時候，reason 寫一句人看得懂的話，例如「台中州廳 17:00 關門，待不滿」。
    //
    // 建議的寫法順序：先做景點的到達、等開門、停留、關門，寫測試；
    // 過了再一項一項加：終點、結束時間、吃飯站、預算。每加一項就加一個測試。
    CheckResult result;
    return result;
}
