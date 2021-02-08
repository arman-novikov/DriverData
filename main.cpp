#include <iostream>
#include <algorithm>
#include <iomanip>

#include "DriverData.hpp"

std::initializer_list<online_t> d1 {
    //0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1
    //0, 1, 1, 1, 1, 1, 1
    0, 0, 1, 1, 1, 1, 1, 1, 0
};

size_t get_work_start(const online_data_t& data,
                                       size_t sleep_sequence_size)
{
    // todo: assert data.size() > SLEEP
    size_t res = 0; // todo: fix differences between start and it
    auto start = data.rbegin();
    auto end = data.rend();
    while(start != end) {
        size_t occurency_count = std::count(start,
                                            start + sleep_sequence_size,
                                            OFFLINE);
        if (occurency_count == sleep_sequence_size) {
            return res;
        }
        ++start;
        ++res;
    }
    for (res = 0; res < data.size(); ++res) {
        if(data[res] == ONLINE) {
            break;
        }
    }

    return data.size() - res - 1; // -1 since we need a reverse index (from end)
}

void test_get_work_start() {
    online_data_t d(d1.size());
    for (const auto& i: d1)
        d.push_back(i);
    std::cout << get_work_start(d, SLEEP) << std::endl;
}

//timestamp_t floor(const std::chrono::high_resolution_clock::time_point& tp, size_t rounding_seconds)
timestamp_t floor(const std::chrono::time_point<std::chrono::system_clock>& tp, size_t rounding_seconds)
{
    timestamp_t res = std::chrono::system_clock::to_time_t(tp);
    res -= res % rounding_seconds;
    return res;

}

void print(const timestamp_t& tp) {
    std::cout << std::put_time(std::localtime(&tp), "%F %T") << '\n';
}

int main(int, char*[])
{
    auto now = std::chrono::system_clock::now();
    print( floor(now, 15 * 60) );

    return 0;
}
