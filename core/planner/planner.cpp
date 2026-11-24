#include "planner/planner.h"
using namespace std;

// 這個檔案的函式互相怎麼叫（由上往下）：
//
//   mustGoCheck（D4）── 呼叫 mealSlots（D2）拿吃飯站
//        │            └ 每試一種順序就呼叫 check（D1）
//        ▼
//   ils（D3）── 一直呼叫 greedy（D3）
//                 └ 每試一個位置就呼叫 check（D1）
//                       └ check 問 travel_.travel：兩站之間要多久
//
// 建議的寫法順序：check → mealSlots → greedy → mustGoCheck → ils，
// 每寫完一個就寫測試，過了再寫下一個。

// 把傳進來的三樣東西記在 data_、travel_、rec_，下面的函式都會用到
Planner::Planner(const DataStore& data, TravelOracle& travel, const Recommender& rec)
    : data_(data), travel_(travel), rec_(rec) {}

// ===============================================================
// D1：檢查一個順序走不走得完
// ===============================================================
CheckResult Planner::check(const vector<ItineraryStop>& order,
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

// ===============================================================
// D2：這趟要吃哪幾餐
// ===============================================================
vector<ItineraryStop> Planner::mealSlots(const TripRequest& req, const Settings& s) const {
    // TODO 決定要吃哪幾餐。
    //
    // 規則：行程時間跟用餐時段「重疊至少 60 分鐘」才吃。
    // 兩段時間 [a1, a2] 和 [b1, b2] 重疊幾分鐘：
    //     重疊 = min(a2, b2) - max(a1, b1)，算出來小於 0 就當 0
    //
    // 這裡要做的事：
    // 1. 使用者選了不吃飯（s.ignoreMeal 是 true）就直接回傳空的。
    // 2. 算 [req.startMin, req.endMin] 跟午餐 [s.lunchFrom, s.lunchTo] 重疊多久。
    //    >= 60 的話，做一個 ItineraryStop：kind = ItineraryStop::Meal、placeId = -1、
    //    isDinner = false，push_back 進去。
    // 3. 晚餐 [s.dinnerFrom, s.dinnerTo] 一樣，isDinner = true。
    //
    // 拿來寫測試的三個例子：
    //   9:00～17:00  → 午餐重疊 120 分鐘，要吃；晚餐 0，不吃
    //   9:00～12:00  → 午餐只重疊 30 分鐘，不吃
    //   13:00～20:00 → 午餐 30，不吃；晚餐 120，要吃
    vector<ItineraryStop> meals;
    return meals;
}

// ===============================================================
// D3：貪婪插入
// ===============================================================
Itinerary Planner::greedy(const vector<ItineraryStop>& mustGoOrder,
                          const vector<int>& candidates,
                          const TripRequest& req, const Settings& s) {
    // TODO 貪婪插入（教學 10 第 10 節）。
    //
    // 準備：
    //   route = mustGoOrder（目前的順序）
    //   先 check 一次 route，記下目前的結束時間 nowEnd。
    //
    // 重複做下面的事，直到這一輪什麼都插不進去：
    //   bestRatio = -1（目前找到最好的比例），記下最好的是哪個候選、插在哪個位置
    //   對每個還沒在 route 裡的候選 c：
    //     對每個可以插的位置 pos（從 1 到 route.size() - 1，也就是起點後面到最後一站前面）：
    //       1. 複製一份 route，在 pos 插入候選 c（kind = Spot、placeId = c）。
    //       2. r = check(新的順序, req, s)
    //       3. r.ok 是 false 就跳過。
    //       4. 多花的時間 = r.endMin - nowEnd，小於 1 就當 1（不能除以 0）。
    //       5. 分數 = rec_.score(data_.place(c), req, s)
    //       6. 比例 = 分數 × 分數 ÷ 多花的時間。比 bestRatio 大就記下來。
    //   都試完了：
    //     bestRatio 還是 -1 → 插不進去了，結束。
    //     不然把最好的那個真的插進 route，更新 nowEnd，再重複一輪。
    //
    // 最後：
    //   用最後一次 check 的 timed 當作行程的 stops，
    //   totalScore = 所有景點的分數加起來，回傳。
    //
    // 對答案：教學 10 第 10 節的例子，每一輪插進去的景點要一樣，最後總分 26.5。
    Itinerary it;
    return it;
}

// ===============================================================
// D3：ILS，讓貪婪有機會回頭改
// ===============================================================
Itinerary Planner::ils(const vector<ItineraryStop>& mustGoOrder,
                       const vector<int>& candidates,
                       const TripRequest& req, const Settings& s) {
    // TODO ILS（教學 10 第 11 節）。不用亂數，同樣的輸入每次結果都一樣。
    //
    // 這裡要做的事：
    // 1. 先跑一次 greedy(mustGoOrder, candidates, req, s)，當作目前最好的 best。
    // 2. R = 1（從第幾站開始拿）、S = 1（一次拿幾站）、沒進步的次數 = 0。
    // 3. 重複：
    //    a. 從 best 的第 R 站開始，拿掉連續 S 站。
    //       起點、終點、一定要去的、吃飯站都不能拿，遇到就跳過。
    //       （踩過的 bug：R + S 超過長度時會把終點也拿掉，要擋掉）
    //    b. 剩下的順序丟給 greedy 補回去。
    //    c. 總分比 best 高 → best 換成新的，S 回到 1，沒進步的次數歸零。
    //       沒有比較高 → 沒進步的次數 + 1。
    //    d. R 往後移 S 站，S 加 1（超過長度就回到 1）。
    //    e. 沒進步的次數到 s.ilsNoImprove，或跑超過 s.ilsMaxSec 秒，就停。
    //       （計時可以用 <ctime> 的 clock()。停止條件還在研究，先這樣）
    // 4. 回傳 best。
    //
    // 對答案：教學 10 例子二，貪婪 22 分，ILS 要進步到 29 分；同樣的輸入跑兩次結果要一樣。
    //
    // 還沒寫之前，先直接回傳貪婪的結果，這樣整個程式還是跑得動。
    return greedy(mustGoOrder, candidates, req, s);
}

// ===============================================================
// D4：一定要去的排不排得下
// ===============================================================
MustGoCheck Planner::mustGoCheck(const TripRequest& req, const Settings& s) {
    // TODO 試所有順序，找出最早結束的那一個（教學 10 第 12 節）。
    //
    // 1. 要排的站：
    //    - req.mustGo 裡的每個景點（kind = Spot）
    //    - mealSlots(req, s) 給的吃飯站（使用者選不吃飯時它會回傳空的）
    //    固定的站：第一站是起點（kind = Start、placeId = req.startPlace）；
    //             有終點（req.endPlace 不是 -1）的話，最後一站是終點（kind = End）。
    //
    // 2. 先不管結束時間：複製一份 req，把 endMin 改成 1440（24:00）再丟給 check。
    //    這樣才算得出「最早幾點能結束」，進而知道差幾分鐘。
    //
    // 3. 用遞迴試所有順序：
    //    另外寫一個遞迴函式（可以加在 private），每一層決定「下一站放誰」：
    //      對每一個還沒用過的站：放進順序、標記用過 → 呼叫自己排下一站
    //                           → 回來後拿出來（pop_back）、取消標記，再試下一個。
    //    全部放完就是一種完整的順序，丟給 check，結束時間比目前最好的早就記下來。
    //
    // 4. 提早放棄，不用每種都排完（這叫「剪枝」）：
    //    a. 放進這一站之後 check 就說不行（例如待不滿就關門）→ 後面怎麼排都救不回來，不用再往下。
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
