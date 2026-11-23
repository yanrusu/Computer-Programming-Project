#include "transit/fake_travel.h"
using namespace std;

// 把傳進來的 DataStore 記在 data_，之後的函式要用
FakeTravel::FakeTravel(const DataStore& data) : data_(data) {}

TravelInfo FakeTravel::travel(int fromPlace, int toPlace, int departMin) {
    // TODO 用直線距離假裝車程。departMin 用不到，假的版本不看時間。
    //
    // 這裡要做的事：
    // 1. 同一個地點（fromPlace == toPlace）：0 分鐘、0 元。
    // 2. 用 data_.place(fromPlace) 和 data_.place(toPlace) 拿到兩邊的緯度、經度。
    // 3. 用 haversine 公式算直線距離幾公里（教學 03 有一份可以直接抄）。
    // 4. 1 公里內當作走路：分鐘 = 公里 × 15，車資 0。
    //    超過 1 公里當作搭車：分鐘 = 10（等車）+ 公里 × 4，車資 20。
    //    分鐘用 ceil 無條件進位，再轉成 int。
    // 5. 填進 TravelInfo：reachable = true、minutes、fare，然後回傳。
    TravelInfo info;
    return info;
}

Leg FakeTravel::travelDetail(int fromPlace, int toPlace, int departMin) {
    // TODO 把上面的結果包成一個 Leg。
    //
    // 這裡要做的事：
    // 1. 先呼叫 travel(fromPlace, toPlace, departMin) 拿到分鐘和車資。
    // 2. 做一個 Segment：
    //    - mode：1 公里內是 "walk"，不然是 "bus"
    //    - departMin = departMin，arriveMin = departMin + 分鐘
    //    - fare = 車資
    //    - path 放兩個點：起點的（緯度, 經度）和終點的（緯度, 經度）
    // 3. 做一個 Leg，把這個 Segment push_back 進 segments，
    //    出發、到達時間和車資也照抄，然後回傳。
    Leg leg;
    return leg;
}
