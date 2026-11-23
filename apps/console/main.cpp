// console 版（A 負責，A4）。
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

    TripSession session;

    // TODO(A4) 接下來大概是：
    // 1. session.init("data/csv")，讀不到就告訴使用者然後結束。
    // 2. 問起點、日期、出發和結束時間（必填），興趣、終點、預算、可搭的交通、
    //    一定要去／不想去（可以不填）。時間讓使用者打「9:30」，進程式前換成 570。
    // 3. session.start(...)，印行程摘要：每站幾點到幾點、每段交通一行、總費用。
    //    還有推薦清單。
    // 4. 進入每一輪的迴圈：重排／微調／確認／回到上一輪，例如打「d 3」刪掉第 3 站。
    //    B 的排行程好之前，先用手寫的假行程把畫面做出來。
    (void)session;

    return 0;
}
