// console 版。
// 這裡只負責讀使用者輸入、把結果印出來，所有計算都交給 TripSession。
// 現在只印標題，確認整個專案編得起來、連得起來。

#include <iostream>
#include "session/trip_session.h"

#ifdef _WIN32
#define NOMINMAX   // 不然 windows.h 的 min、max 會跟 std::min、std::max 打架
#include <windows.h>
#endif

using namespace std;

int main() {
#ifdef _WIN32
    // Windows 的命令列預設不是 UTF-8，不設的話中文會變亂碼
    SetConsoleOutputCP(CP_UTF8);
#endif

    cout << "台中大眾運輸行程規劃\n";

    TripSession session;    // 所有模組都在裡面建好了

    // TODO 接下來要做的事：
    // 1. session.init("data/csv")，回傳 false 就印「讀不到資料」然後結束。
    // 2. 問使用者：
    //    必填：起點、日期、出發時間、結束時間
    //    可以不填：興趣、終點、預算、可搭的交通、一定要去／不想去
    //    時間讓使用者打「9:30」，進程式前換成分鐘：9 * 60 + 30 = 570。
    //    全部填進一個 TripRequest 和一個 Settings。
    // 3. PlanResult r = session.start(req, s)
    //    印行程摘要：每站幾點到幾點、每段交通一行、總費用，還有推薦清單。
    //    r.ok 是 false 的話，印衝突和建議。
    // 4. 用 while 迴圈一直讀指令，例如「d 3」刪掉第 3 站、「r」重新排、「b」回到上一輪、
    //    「f」完成（教學 08 第 2 節有指令表和範例）。
    //    排行程還沒做好之前，先用手寫的假行程把畫面做出來。

    return 0;
}
