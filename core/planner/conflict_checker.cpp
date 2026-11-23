#include "planner/conflict_checker.h"
using namespace std;

ConflictChecker::ConflictChecker(const DataStore& data, TimelineChecker& checker,
                                 const MealPlanner& meals)
    : data_(data), checker_(checker), meals_(meals) {}

MustGoCheck ConflictChecker::check(const TripRequest& req, const Settings& s) {
    // TODO 教學 10 第 12 節。用遞迴（回溯）試所有順序：
    // 每一層選「下一站放誰」，放進去、遞迴下去、回來 pop_back、再試下一個。
    //
    // 誰要排：req.mustGo 裡的景點＋meals_.mealSlots 給的吃飯站。
    // - 共 s.maxMustGo（8）個以內：全部一起窮舉，上一輪留下的也可以換順序。
    // - 超過 8 個：req.keptOrder 的順序不動，只窮舉新指定的放在哪裡、誰先誰後。
    //   每一層的選擇變成「放 keptOrder 的下一個」或「放一個還沒用過的新景點」。
    //
    // 先不管結束時間（複製一份 req，把 endMin 設成 1440 再丟給 D1），
    // 只檢查開放時間，找出最早幾點能結束：
    //   最早結束 <= req.endMin → ok，bestOrder 就是那個順序。
    //   最早結束 >  req.endMin → 不 ok，加一個 TimeShort，amount = 差幾分鐘。
    //   一種都排不出來        → 開放時段撞在一起（OpeningClash），
    //                           用「一次拿掉一個再試」找出是哪幾個景點。
    //   超過 8 個又排不下     → 直接回傳衝突，讓 D5 給建議。
    //
    // 剪枝：
    //   1. 放進去這站就不行了（待不滿就關門）→ 後面怎麼排都救不回來，跳過。
    //   2. 這站的離開時間已經不比目前最好的結束時間早 → 跳過（分支定界）。
    //
    // 好用的測試：把剪枝關掉，答案也要一模一樣。剪枝只能讓它變快，不能改答案。
    (void)req; (void)s;
    return {};
}
