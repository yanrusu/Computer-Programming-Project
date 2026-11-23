#include "planner/ils_search.h"
using namespace std;

IlsSearch::IlsSearch(GreedySearch& greedy) : greedy_(greedy) {}

Itinerary IlsSearch::search(const vector<ItineraryStop>& mustGoOrder,
                            const vector<int>& candidates) {
    // 貪婪也要知道這一輪的輸入，先轉交給它
    greedy_.setRequest(req_, settings_);

    // TODO(B11) 教學 10 第 11 節：
    // 1. 先跑一次貪婪，當作目前最好的。
    // 2. 從第 R 站開始，拿掉連續 S 站。一定要去的、吃飯站、起點、終點都不能拿。
    //    （踩過的 bug：R + S 超過長度時會把終點也拿掉，要擋掉。）
    // 3. 剩下的丟回貪婪補。
    // 4. 比目前最好的高分就記下來，S 回到 1；沒有就算一次「沒進步」。
    // 5. R 往後移 S 站，S 加 1（超過長度就回到 1），回到第 2 步。
    // 6. 連續 settings_.ilsNoImprove 次沒進步，或跑超過 settings_.ilsMaxSec 秒就停。
    //    （停止條件還在研究，先這樣。）
    //
    // 測試：教學 10 例子二，貪婪 22 分，ILS 要進步到 29 分；同樣的輸入跑兩次結果要一樣。
    // 還沒寫之前先直接回傳貪婪的結果，這樣 TripSession 換成 ILS 也能跑。
    return greedy_.search(mustGoOrder, candidates);
}
