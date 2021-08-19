#include <nlohmann/json.hpp>

#include "test/EndpointTest.h"

#include "domain/ElectricityReading.h"
#include "generator.h"

using nlohmann::json;
using ::testing::Eq;
using ::testing::SizeIs;

class ReadingsTest : public EndpointTest {
};

TEST_F(ReadingsTest, ReadReadingShouldRespondWithAllReadingsGivenValidMeter) {
    auto res = client.Get("/readings/read/smart-meter-1");

    ASSERT_THAT(res.result(), Eq(http::status::ok));
    auto body = json::parse(res.body());
    auto readings = body["readings"];
    EXPECT_THAT(readings, SizeIs(20));
}

TEST_F(ReadingsTest, ReadReadingShouldRespondNotFoundGivenInvalidMeter) {
    auto res = client.Get("/readings/read/smart-meter-not-existed");

    ASSERT_THAT(res.result(), Eq(http::status::not_found));
}

TEST_F(ReadingsTest, StoreShouldRespondWithMultipelValidBatchesOfMeter) {
    static int READING_SIZE = 3;
    json request_body = R"({
            "smartMeterId": "smart-meter-0",
            "electricityReadings": [
                    {
                            "time": "2021-08-18T06:42:15.725202Z",
                            "reading": 1
                    },
                    {
                            "time": "2021-08-18T06:44:15.725202Z",
                            "reading": 2
                    }
            ]
    })"_json;
    auto res = client.Post("/readings/store", request_body);

    ASSERT_THAT(res.result(), Eq(http::status::ok));
}