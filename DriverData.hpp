#pragma once
#include <boost/circular_buffer.hpp>
#include <chrono>
#include <optional>
#include <utility>
// assuming second is the min quanting unit

static constexpr size_t SMALL_INTERIM {15U * 60U};
static constexpr size_t BIG_INTERIM {60U * 60U};
static constexpr size_t INTERIM_RATIO {BIG_INTERIM / SMALL_INTERIM};

// measured with SMALL_INTERIMs
static constexpr size_t SLEEP {7U * INTERIM_RATIO};
static constexpr size_t MAX_ON_ORDER {7U * INTERIM_RATIO};
static constexpr size_t MAX_ONLINE {17U * INTERIM_RATIO};
static constexpr size_t ONLINE_WINDOW_SIZE {
        2*SLEEP + std::max(MAX_ON_ORDER, MAX_ONLINE)
};

typedef uint8_t status_t;
static constexpr status_t ONLINE {1U};
static constexpr status_t OFFLINE {0U};
typedef boost::circular_buffer<status_t> online_data_t;
typedef std::time_t timestamp_t;

//std::chrono::time_point<std::chrono::system_clock>

class DriverData
{
    // online interims, interims count to request from
    typedef std::pair<size_t, size_t> online_review_t;

    //on order time, from
    typedef std::pair<size_t, std::optional<timestamp_t>> on_order_review_t;
public:
    DriverData();
    void Update(const online_data_t& online_data,                
                const timestamp_t& ts);

    std::vector<timestamp_t>
        ProcessWindow(std::vector<status_t>& data, timestamp_t ts);

    void SetOnOrder(size_t on_order);
    on_order_review_t GetOnOrder() const;
    std::optional<timestamp_t> GetWorkStart() const;
    online_review_t GetOnline() const;
public:
    static timestamp_t
        Interim2Timestamp(timestamp_t ts, size_t reverse_offset);
    online_data_t onlineData_;
    size_t onOrder_;

    /* data update timestamp
    *  expected to be rounded to the earliest BIG_INTERIM
    */
    timestamp_t timestamp_;
};
