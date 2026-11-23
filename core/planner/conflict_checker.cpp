#include "planner/conflict_checker.h"
using namespace std;

// 把傳進來的三個模組記起來，check 要用
ConflictChecker::ConflictChecker(const DataStore& data, TimelineChecker& checker,
                                 const MealPlanner& meals)
    : data_(data), checker_(checker), meals_(meals) {}

MustGoCheck ConflictChecker::check(const TripRequest& req, const Settings& s) {
    // TODO 試所有順序，找出最早結束的那一個（教學 10 第 12 節）。
    //
    // 1. 要排的站：
    //    - req.mustGo 裡的每個景點（kind = Spot）
    //    - meals_.mealSlots(req, s) 給的吃飯站（使用者選不吃飯時它會回傳空的）
    //    固定的站：第一站是起點（kind = Start、placeId = req.startPlace）；
    //             有終點（req.endPlace 不是 -1）的話，最後一站是終點（kind = End）。
    //
    // 2. 先不管結束時間：複製一份 req，把 endMin 改成 1440（24:00）再丟給 D1。
    //    這樣才算得出「最早幾點能結束」，進而知道差幾分鐘。
    //
    // 3. 用遞迴試所有順序：
    //    寫一個遞迴函式，每一層決定「下一站放誰」：
    //      對每一個還沒用過的站：放進順序、標記用過 → 呼叫自己排下一站
    //                           → 回來後拿出來（pop_back）、取消標記，再試下一個。
    //    全部放完就是一種完整的順序，丟給 D1，結束時間比目前最好的早就記下來。
    //
    // 4. 提早放棄，不用每種都排完（這叫「剪枝」）：
    //    a. 放進這一站之後 D1 就說不行（例如待不滿就關門）→ 後面怎麼排都救不回來，不用再往下。
    //    b. 這一站的離開時間已經不比目前最好的結束時間早 → 後面只會更晚，不用再往下。
    //
    // 5. 一定要去的太多時（全部要排的超過 s.maxMustGo 個）：
    //    上一輪留下的照 req.keptOrder 的順序不動，只試「新指定的景點放在哪裡」。
    //    也就是每一層的選擇只有兩種：放 keptOrder 的下一個，或放一個還沒用過的新景點。
    //
    // 6. 結果：
    //    最早結束 <= req.endMin → ok = true，bestOrder、earliestEnd、minCost 填好。
    //    最早結束 >  req.endMin → ok = false，加一個 Conflict：
    //                              type = TimeShort，amount = 差幾分鐘。
    //    一種順序都排不出來    → ok = false，type = OpeningClash（開放時間撞在一起）。
    //                              一次拿掉一個景點再試，找出是哪幾個造成的，放進 places。
    //
    // 好用的測試：把剪枝拿掉，答案也要一模一樣。剪枝只能讓它變快，不能改答案。
    MustGoCheck result;
    return result;
}
