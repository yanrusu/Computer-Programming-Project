#include "transit/fake_travel.h"
using namespace std;

FakeTravel::FakeTravel(const DataStore& data) : data_(data) {}

TravelInfo FakeTravel::travel(int fromPlace, int toPlace, int departMin) {
    // TODO(B3) 用 haversine 算兩點直線距離（公里），程式在教學 03 有一份可以直接抄：
    // - 同一個地點：0 分鐘、0 元。
    // - 1 公里內當作走路：每公里 15 分鐘，0 元。
    // - 再遠就當作搭車：等車 10 分鐘＋每公里 4 分鐘，20 元。
    // 分鐘數用 ceil 進位。departMin 用不到，假的版本不看時間。
    (void)fromPlace; (void)toPlace; (void)departMin;
    return {};
}

Leg FakeTravel::travelDetail(int fromPlace, int toPlace, int departMin) {
    // TODO(B3) 用上面的 travel 算出時間和車資，包成一個只有一小段的 Leg：
    // 走路就是 mode = "walk"，搭車就隨便叫 "bus"。path 放起點、終點兩個座標就好，
    // 地圖上會畫成一條直線，看得出是假的也沒關係。
    (void)fromPlace; (void)toPlace; (void)departMin;
    return {};
}
