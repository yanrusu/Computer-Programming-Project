#pragma once
// 全組共用的資料結構，照計劃書 5-2 抄過來。
// 要加欄位或改名字，先在群組講一聲再改，
// 不然三個人的程式會一起編譯不過。
//
// 幾個共同的規則：
//   時間：int，從 0:00 起算的分鐘，9:30 就是 570。只有輸入輸出時才換成「9:30」。
//   編號：int，就是在 vector 裡的位置。CSV 的原始編號讀檔時就換掉。
//   錢：int，單位是元。
//   興趣類別：固定 7 格，順序是
//     0 歷史古蹟、1 藝文展覽、2 自然公園、3 美食小吃、4 文創街區、5 購物商圈、6 宗教廟宇
//
// 每個欄位都有給一開始的值（例如沒填是 -1），
// 這樣忘了設定也不會拿到亂七八糟的數字。

#include <array>
#include <set>
#include <string>
#include <utility>
#include <vector>

// ---------------------------------------------------------------
// Place：一個地點，景點、起點、終點都用它
// ---------------------------------------------------------------
struct Place {
    int id = -1;                    // 編號，等於在 DataStore 陣列裡的位置
    std::string name;               // 名稱
    double lat = 0;                 // 緯度
    double lon = 0;                 // 經度
    std::array<bool, 7> category = {};   // 7 個類別各是不是，可以不只一類。一開始全部是 false
    int openMin[7] = {-1, -1, -1, -1, -1, -1, -1};   // 星期日～六幾點開門，公休是 -1
    int closeMin[7] = {-1, -1, -1, -1, -1, -1, -1};  // 星期日～六幾點關門，公休是 -1
    int stayMin = 0;                // 建議待幾分鐘
    int ticket = 0;                 // 門票，免費是 0
    int rating = 3;                 // 組員評分 1～5，還沒評就當 3
};

// ---------------------------------------------------------------
// TripRequest：使用者這一輪輸入的東西
// ---------------------------------------------------------------
struct TripRequest {
    int startPlace = -1;            // 起點的地點編號
    int endPlace = -1;              // 終點，沒填是 -1（結束在最後一站）
    int weekday = 0;                // 星期幾，0 是星期日
    bool isHoliday = false;         // 假日要用另一套公車班表
    int startMin = 0;               // 出發時間
    int endMin = 0;                 // 結束時間
    std::array<int, 7> interest = {};    // 每類興趣強度 0～3，全部 0 就是沒填
    int budget = -1;                // 預算，沒填是 -1（不限）
    bool allowBus = true;           // 可以搭公車
    bool allowBike = true;          // 可以騎 YouBike（走路一律可以）
    std::set<int> mustGo;           // 一定要去的地點編號
    std::set<int> dontGo;           // 不想去的（被刪掉的也放這裡）
    std::vector<int> keptOrder;     // 上一輪留下的景點，照上一輪的順序。第一輪是空的
};

// ---------------------------------------------------------------
// Settings：所有可以調的數字都放這裡，不要寫死在程式裡
// ---------------------------------------------------------------
struct Settings {
    double paceFactor = 1.0;        // 步調：停留時間乘上 0.75（緊湊）／1（普通）／1.25（悠閒）
    int lunchFrom = 690;            // 午餐時段 11:30 開始
    int lunchTo = 810;              //          13:30 結束
    int dinnerFrom = 1050;          // 晚餐時段 17:30 開始
    int dinnerTo = 1170;            //          19:30 結束
    int mealMin = 60;               // 吃飯 60 分鐘
    int mealBuffer = 15;            // 再留 15 分鐘找地方吃
    int lunchCost = 250;            // 一餐估 250 元（午餐晚餐都用這個）
    int transferBuffer = 3;         // 轉乘多留 3 分鐘
    int slotMin = 10;               // 記住車程時，出發時間往後對齊到 10 分鐘
    double eta = 0.7;               // 打分數時興趣佔的比重
    int perStopPenalty = 0;         // 每多一站扣幾分，先不扣
    int candidateCount = 30;        // 候選景點取推薦前幾名
    int maxMustGo = 8;              // 每一輪新指定的一定要去最多幾個；D4 全部窮舉的上限也是它
    int ilsNoImprove = 150;         // ILS 連續幾次沒進步就停（還在研究）
    int ilsMaxSec = 5;              // ILS 最多跑幾秒（還在研究）
    int nearbyMin = 15;             // 就近替換：交通幾分鐘內算「附近」
    int timeBarTravelMin = 20;      // 時間條每多一站估幾分鐘交通
    bool ignoreBudget = false;      // 使用者選了「忽略預算」：D1 就不檢查預算
    bool ignoreMeal = false;        // 使用者選了「不吃飯」：不放吃飯站
};

// ---------------------------------------------------------------
// ItineraryStop：行程裡的一站
// ---------------------------------------------------------------
struct ItineraryStop {
    enum Kind { Start, Spot, Meal, End };   // 起點、景點、吃飯、終點
    Kind kind = Spot;               // 這一站是哪一種
    int placeId = -1;               // 地點編號。吃飯不排餐廳，一律是 -1
    bool isDinner = false;          // 只有吃飯站用得到：false 是午餐，true 是晚餐
    int arriveMin = 0;              // 幾點到
    int startMin = 0;               // 幾點開始（早到的話是等開門之後）
    int departMin = 0;              // 幾點離開
};

// ---------------------------------------------------------------
// Segment：一段交通裡的一小段
// 例如「走路 → 搭 300 路 → 走路」就是三個 Segment
// ---------------------------------------------------------------
struct Segment {
    std::string mode;               // "walk"、"bus"、"bike"
    int lineId = -1;                // 路線編號，查票價用。走路是 -1
    std::string lineName;           // 給人看的路線名稱，例如「300 路」
    int fromStop = -1;              // 上車站
    int toStop = -1;                // 下車站
    int departMin = 0;              // 這一小段幾點出發
    int arriveMin = 0;              // 這一小段幾點到
    int fare = 0;                   // 這一小段的車資
    std::vector<std::pair<double, double>> path;   // 地圖上要畫的座標，每個是（緯度, 經度）
};

// ---------------------------------------------------------------
// Leg：兩站之間的整段交通
// 只有最後的行程才會算完整的 Leg，搜尋的時候只用 TravelInfo
// ---------------------------------------------------------------
struct Leg {
    std::vector<Segment> segments;  // 這段交通裡的每一小段
    int departMin = 0;              // 整段幾點出發
    int arriveMin = 0;              // 整段幾點到
    int fare = 0;                   // 整段車資
};

// ---------------------------------------------------------------
// Itinerary：一份行程
// ---------------------------------------------------------------
struct Itinerary {
    std::vector<ItineraryStop> stops;   // 每一站
    std::vector<Leg> legs;          // legs[i] 是 stops[i] 到 stops[i+1] 的交通
    double totalScore = 0;          // 景點分數加總
    int fareTotal = 0;              // 車資小計
    int ticketTotal = 0;            // 門票小計
    int mealTotal = 0;              // 餐費小計
    std::vector<std::string> warnings;   // 例如「超過預算 120 元」「沒有安排午餐」
};

// ---------------------------------------------------------------
// RoundState：一輪的狀態，回到上一輪就是拿這個
// （忽略預算、不吃飯這兩個開關放在 Settings 裡）
// ---------------------------------------------------------------
struct RoundState {
    TripRequest request;            // 這一輪的輸入
    Settings settings;              // 這一輪的設定
    Itinerary itinerary;            // 這一輪排出來的行程
};

// ---------------------------------------------------------------
// TravelInfo：問「A 幾點出發到 B」的答案（搜尋時用，要輕）
// ---------------------------------------------------------------
struct TravelInfo {
    bool reachable = false;         // 到不到得了
    int minutes = 0;                // 要幾分鐘
    int fare = 0;                   // 多少錢
};

// ---------------------------------------------------------------
// CheckResult：D1 檢查一個順序的結果
// ---------------------------------------------------------------
struct CheckResult {
    bool ok = false;                // 走不走得完
    std::string reason;             // 走不完的原因，給人看的
    std::vector<ItineraryStop> timed;   // 算好每站時間的順序
    int endMin = 0;                 // 幾點結束
    int cost = 0;                   // 總共花多少
};

// ---------------------------------------------------------------
// Conflict：一個衝突
// ---------------------------------------------------------------
struct Conflict {
    // TimeShort 時間不夠、OpeningClash 開放時段撞在一起、OverBudget 超過預算、NoMealTime 沒時間吃飯
    enum Type { TimeShort, OpeningClash, OverBudget, NoMealTime };
    Type type = TimeShort;          // 是哪一種衝突
    int amount = 0;                 // 差幾分鐘，或超過幾元
    std::vector<int> places;        // 跟哪幾個景點有關
    std::string message;            // 給使用者看的一句話
};

// ---------------------------------------------------------------
// Suggestion：一個建議，使用者可以一鍵套用
// ---------------------------------------------------------------
struct Suggestion {
    // DropNew 不加入剛新增的、RemoveExisting 拿掉原本的、ExtendEnd 延後結束、
    // FastPace 改緊湊步調、IgnoreBudget 忽略預算、IgnoreMeal 不吃飯
    enum Action { DropNew, RemoveExisting, ExtendEnd, FastPace, IgnoreBudget, IgnoreMeal };
    Action action = DropNew;        // 要做哪一種
    std::vector<int> places;        // 要拿掉哪些景點
    int newEndMin = -1;             // 延後到幾點，只有 ExtendEnd 用得到
    std::string message;            // 給使用者看的一句話
};

// ---------------------------------------------------------------
// MustGoCheck：D4 衝突檢查的結果
// ---------------------------------------------------------------
struct MustGoCheck {
    bool ok = false;                // 一定要去的排不排得下
    std::vector<ItineraryStop> bestOrder;   // 最早結束的那個順序（含起點、吃飯站、終點）
    int earliestEnd = 0;            // 最早幾點能結束
    int minCost = 0;                // 最少要花多少錢
    std::vector<Conflict> conflicts;    // 排不下的話，衝突在這裡
};

// ---------------------------------------------------------------
// PlanResult：每一輪丟回給畫面的結果
// ---------------------------------------------------------------
struct PlanResult {
    bool ok = false;                // 有沒有排出行程
    Itinerary itinerary;            // 排出來的行程
    std::vector<Conflict> conflicts;    // 排不下時，衝突在這裡
    std::vector<Suggestion> suggestions;    // 給使用者的建議（最多 3 個）
};
