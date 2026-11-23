#include "data/data_store.h"
using namespace std;

bool DataStore::loadAll(const string& csvDir) {
    // TODO 讀 csvDir 資料夾裡的 places.csv，之後還會有公車、YouBike、票價的檔案。
    //
    // 這裡要做的事：
    // 1. 用 ifstream 打開 csvDir + "/places.csv"，打不開就 return false。
    // 2. 第一行是欄位名稱，先用 getline 讀掉不要。
    // 3. 之後用 getline 一行一行讀，每一行用逗號切開，變成一格一格的字串。
    //    （欄位的順序照 docs/data_schema.md）
    // 4. 每一行做成一個 Place，push_back 到 places_：
    //    - 名稱、座標、停留時間、門票、評分直接填。
    //      字串轉數字可以用 stoi（整數）和 stod（小數）。
    //    - 開放時間「09:00」換成分鐘：9 * 60 + 0 = 540。公休寫 -1。
    //    - id 就是它在 places_ 裡的位置，第一筆是 0、第二筆是 1……
    // 5. CSV 裡的編號（像 P001）程式裡不用。讀的時候用一個 map<string, int>
    //    記下「P001 → 0」，其他檔案提到 P001 時再用這個 map 換成 0。
    // 6. 某一行的格數不對、數字轉不過去，就 return false。
    // 7. 全部讀完 return true。
    return false;
}

const vector<Place>& DataStore::places() const {
    return places_;
}

const Place& DataStore::place(int id) const {
    // 編號就是陣列位置，直接拿出來。
    // 傳進來的 id 超出範圍的話，是呼叫的人寫錯了
    return places_[id];
}

vector<int> DataStore::searchByName(const string& keyword) const {
    // TODO 用名字找地點。
    //
    // 這裡要做的事：
    // 1. 準備一個空的 vector<int> answer。
    // 2. 用 for 迴圈看每一個地點（i 從 0 到 places_.size() - 1）：
    //    如果 places_[i].name.find(keyword) != string::npos（名字裡找得到 keyword），
    //    就 answer.push_back(i)。
    // 3. 回傳 answer。
    //
    // 地點才幾百個，這樣一個一個看就夠快了。
    vector<int> answer;
    return answer;
}

void DataStore::setPlaces(const vector<Place>& places) {
    places_ = places;
    // 每個地點的 id 改成它在陣列裡的位置
    for (int i = 0; i < (int)places_.size(); i++) {
        places_[i].id = i;
    }
}
