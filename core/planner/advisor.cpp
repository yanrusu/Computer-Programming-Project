#include "planner/advisor.h"
using namespace std;

Advisor::Advisor(const DataStore& data, ConflictChecker& conflict, const Recommender& rec)
    : data_(data), conflict_(conflict), rec_(rec) {}

vector<Suggestion> Advisor::suggest(const TripRequest& req, const Settings& s,
                                    const vector<Conflict>& conflicts,
                                    const set<int>& justAdded) {
    // TODO 照下面的順序一個一個試。每一個都先改一份 req／s 的複本，
    // 丟給 conflict_.check 看排不排得下，排得下才收進來，收滿 3 個就停：
    //
    //   1. DropNew：不加入這一輪剛新增的（justAdded）。
    //   2. RemoveExisting：拿掉一個原本的一定要去的，分數低的先試。
    //   3. ExtendEnd：結束時間延後到 D4 算出的最早結束時間。
    //   4. FastPace：改成緊湊步調（paceFactor = 0.75）。
    //   5. IgnoreBudget、IgnoreMeal：只有衝突是預算或用餐時才給。
    //
    // 時間不夠、開放時段撞在一起是不能忽略的，所以不會有「忽略時間」這種建議。
    // message 寫給一般人看，例如「拿掉審計新村就排得下」。
    (void)req; (void)s; (void)conflicts; (void)justAdded;
    return {};
}
