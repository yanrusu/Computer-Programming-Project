#include "planner/replacer.h"
using namespace std;

// 把傳進來的四個模組記起來，nearby 要用
Replacer::Replacer(const DataStore& data, TimelineChecker& checker, TravelOracle& travel,
                   const Recommender& rec)
    : data_(data), checker_(checker), travel_(travel), rec_(rec) {}

vector<int> Replacer::nearby(const Itinerary& it, int stopIndex,
                             const TripRequest& req, const Settings& s) {
    // TODO 列出可以替換第 stopIndex 站的景點。
    //
    // 這裡要做的事：
    // 1. 第 stopIndex 站不是景點（是起點、終點、吃飯）就直接回傳空的。
    // 2. 用 for 迴圈看每個景點 c，以下跳過：
    //    - 已經在行程裡的（it.stops 裡有它）
    //    - 在 req.dontGo 裡的
    //    - 從原本那站過去要超過 s.nearbyMin（15）分鐘的
    //      （用 travel_.travel(原本那站的 placeId, c, 那站的 arriveMin) 看分鐘數）
    // 3. 剩下的，一個一個試：複製一份 it.stops，把第 stopIndex 站的 placeId 換成 c，
    //    丟給 checker_.check(新的順序, req, s)，ok 是 true 的留下。
    // 4. 留下的照分數由高到低排（分數問 rec_.score），回傳。
    vector<int> answer;
    return answer;
}
