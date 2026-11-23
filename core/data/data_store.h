#pragma once
// DataStore：把 data/csv/ 裡的 CSV 讀進來，之後大家都跟它拿資料。
// 只負責讀檔和存放，不做任何計算，也不 cout（讀檔出錯就回傳 false）。

#include <string>
#include <vector>
#include "data/types.h"

class DataStore {
public:
    // 讀所有 CSV。程式一開始呼叫一次，有任何一個檔讀不了就回傳 false
    bool loadAll(const std::string& csvDir);

    // 所有地點，編號就是在這個 vector 裡的位置
    const std::vector<Place>& places() const;

    // 用編號拿一個地點
    const Place& place(int id) const;

    // 用名字找地點，回傳名字裡有 keyword 的那些編號。
    // 起點、終點、一定要去的地點都靠它找
    std::vector<int> searchByName(const std::string& keyword) const;

    // 計劃書沒有這個，是給測試用的：測試不讀 CSV，直接把手寫的地點塞進來。
    // 會順便把每個地點的 id 設成它在陣列裡的位置
    void setPlaces(const std::vector<Place>& places);

private:
    std::vector<Place> places_;
};
