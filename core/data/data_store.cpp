#include "data/data_store.h"
using namespace std;

bool DataStore::loadAll(const string& csvDir) {
    // TODO(C6) 讀 csvDir 底下的 places.csv（之後還有公車、YouBike、票價那幾個檔）。
    // - 欄位照 docs/data_schema.md。
    // - CSV 裡的編號（像 P001）不要直接用，讀的時候用 map<string, int> 換成 0、1、2……
    //   其他檔案提到 P001 時也用同一個 map 換。
    // - 開放時間「09:00」換成 540，公休寫 -1。
    // - 某一行格式不對就回傳 false。之後想把「哪個檔第幾行」帶出去的話，可以跟大家討論加個欄位。
    (void)csvDir;
    return false;
}

const vector<Place>& DataStore::places() const {
    return places_;
}

const Place& DataStore::place(int id) const {
    // 編號就是陣列位置，直接拿。傳進來的 id 超出範圍是呼叫的人的 bug
    return places_[id];
}

vector<int> DataStore::searchByName(const string& keyword) const {
    // TODO(C6) 每個地點的名字掃一遍，name.find(keyword) != string::npos 的都放進去回傳。
    // 地點才幾百個，掃一遍就夠快了，不用想更厲害的方法。
    (void)keyword;
    return {};
}

void DataStore::setPlaces(const vector<Place>& places) {
    places_ = places;
    for (int i = 0; i < (int)places_.size(); i++) places_[i].id = i;
}
