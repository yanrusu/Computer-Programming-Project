#include "planner/advisor.h"
using namespace std;

// 把傳進來的三個模組記起來，suggest 要用
Advisor::Advisor(const DataStore& data, ConflictChecker& conflict, const Recommender& rec)
    : data_(data), conflict_(conflict), rec_(rec) {}

vector<Suggestion> Advisor::suggest(const TripRequest& req, const Settings& s,
                                    const vector<Conflict>& conflicts,
                                    const set<int>& justAdded) {
    // TODO 產生建議（教學 10 第 13 節）。
    //
    // 每一種建議都照這三步：
    //   1. 複製一份 req 和 s，照建議改。
    //   2. 丟給 conflict_.check(改過的 req, 改過的 s)。
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
