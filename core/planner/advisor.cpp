#include "planner/advisor.h"
using namespace std;

// 把傳進來的四樣東西記起來，下面的函式都會用到
Advisor::Advisor(const DataStore& data, TravelOracle& travel, const Recommender& rec,
                 Planner& planner)
    : data_(data), travel_(travel), rec_(rec), planner_(planner) {}

// ===============================================================
// D5：排不下時給建議
// ===============================================================
vector<Suggestion> Advisor::suggest(const TripRequest& req, const Settings& s,
                                    const vector<Conflict>& conflicts,
                                    const set<int>& justAdded) {
    // TODO 產生建議（教學 10 第 13 節）。
    //
    // 每一種建議都照這三步：
    //   1. 複製一份 req 和 s，照建議改。
    //   2. 丟給 planner_.mustGoCheck(改過的 req, 改過的 s)。
    //   3. 回傳的 ok 是 true 才收進 answer。收滿 3 個就停。
    //
    // 照這個順序試：
    //   1. DropNew：不加入這一輪剛新增的（把 justAdded 裡的從 mustGo 拿掉）。
    //   2. RemoveExisting：拿掉一個原本的一定要去的，分數低的先試（分數問 rec_.score）。
    //   3. ExtendEnd：結束時間延後。延後多少看 TimeShort 那個衝突的 amount（差幾分鐘），
    //      newEndMin = req.endMin + amount。
    //   4. FastPace：改成緊湊步調，s.paceFactor = 0.75。
    //   5. IgnoreBudget：s.ignoreBudget = true。只有衝突是 OverBudget 才給。
    //      IgnoreMeal：s.ignoreMeal = true。只有衝突是 NoMealTime 才給。
    //
    // 時間不夠、開放時段撞在一起是不能忽略的，所以不會有「忽略時間」這種建議。
    // message 寫給一般人看，例如「拿掉審計新村就排得下」。
    vector<Suggestion> answer;
    return answer;
}

// ===============================================================
// D6：就近替換
// ===============================================================
vector<int> Advisor::nearby(const Itinerary& it, int stopIndex,
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
    //    丟給 planner_.check(新的順序, req, s)，ok 是 true 的留下。
    // 4. 留下的照分數由高到低排（分數問 rec_.score），回傳。
    vector<int> answer;
    return answer;
}

// ===============================================================
// D7：時間條
// ===============================================================
int Advisor::timeBar(const Itinerary& it, const vector<int>& selected, const Settings& s) const {
    // TODO 粗估時間。勾一下就要更新，所以不問 Planner（太慢），只用加的。
    //
    // 這裡要做的事：
    // 1. 目前行程的時間：
    //    行程是空的（it.stops.size() == 0）就是 0；
    //    不然是「最後一站的離開時間 - 第一站的離開時間」。
    //    （最後一站是終點的話，用它的到達時間）
    // 2. 每個 selected 裡的景點，加上：
    //    data_.place(那個編號).stayMin × s.paceFactor + s.timeBarTravelMin（20）
    // 3. 回傳加起來的分鐘數。
    //
    // 只估時間，沒有預算條。
    return 0;
}
