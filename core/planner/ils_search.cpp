#include "planner/ils_search.h"
using namespace std;

// 把 GreedySearch 記起來，search 要用
IlsSearch::IlsSearch(GreedySearch& greedy) : greedy_(greedy) {}

Itinerary IlsSearch::search(const vector<ItineraryStop>& mustGoOrder,
                            const vector<int>& candidates) {
    // 貪婪也要知道這一輪的輸入和設定，先轉交給它
    greedy_.setRequest(req_, settings_);

    // TODO ILS（教學 10 第 11 節）。
    //
    // 這裡要做的事：
    // 1. 先跑一次 greedy_.search(mustGoOrder, candidates)，當作目前最好的 best。
    // 2. R = 1（從第幾站開始拿）、S = 1（一次拿幾站）、沒進步的次數 = 0。
    // 3. 重複：
    //    a. 從 best 的第 R 站開始，拿掉連續 S 站。
    //       起點、終點、一定要去的、吃飯站都不能拿，遇到就跳過。
    //       （踩過的 bug：R + S 超過長度時會把終點也拿掉，要擋掉）
    //    b. 剩下的順序丟給 greedy_.search 補回去。
    //    c. 總分比 best 高 → best 換成新的，S 回到 1，沒進步的次數歸零。
    //       沒有比較高 → 沒進步的次數 + 1。
    //    d. R 往後移 S 站，S 加 1（超過長度就回到 1）。
    //    e. 沒進步的次數到 settings_.ilsNoImprove，或跑超過 settings_.ilsMaxSec 秒，就停。
    //       （計時可以用 <ctime> 的 clock()。停止條件還在研究，先這樣）
    // 4. 回傳 best。
    //
    // 對答案：教學 10 例子二，貪婪 22 分，ILS 要進步到 29 分；同樣的輸入跑兩次結果要一樣。
    //
    // 還沒寫之前，先直接回傳貪婪的結果，這樣整個程式還是跑得動。
    return greedy_.search(mustGoOrder, candidates);
}
