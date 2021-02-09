#pragma once
#include <boost/circular_buffer.hpp>
#include <chrono>

// assuming second is the min quanting unit

static constexpr size_t SMALL_INTERIM {15U * 60U};
static constexpr size_t BIG_INTERIM {60U * 60U};
static constexpr size_t INTERIM_RATIO {BIG_INTERIM / SMALL_INTERIM};

// measured with SMALL_INTERIMs
static constexpr size_t SLEEP {7U * INTERIM_RATIO};
static constexpr size_t MAX_ON_ORDER {17U * INTERIM_RATIO};
static constexpr size_t MAX_ONLINE {7U * INTERIM_RATIO};
static constexpr size_t ONLINE_WINDOW_SIZE {
        2*SLEEP + std::min(MAX_ON_ORDER, MAX_ONLINE)
};

typedef uint8_t online_t;
static constexpr online_t ONLINE {1U};
static constexpr online_t OFFLINE {0U};
typedef boost::circular_buffer<online_t> online_data_t;
typedef std::time_t timestamp_t;

//std::chrono::time_point<std::chrono::system_clock>

class DriverData
{
public:
    DriverData();
    void Update(const online_data_t& online_data,                
                const timestamp_t& ts);

    void SetOnOrder(size_t on_order);
    size_t GetOnOrder() const;
public:
    online_data_t onlineData_;
    size_t onOrder_;

    /* data update timestamp
    *  expected to be rouneded to the earliest BIG_INTERIM
    */
    timestamp_t timestamp_;
};
