#include <gmock/gmock.h>
#include <rest/controller/MeterReadingController.h>

#include <boost/beast/http.hpp>
#include <nlohmann/json.hpp>

using nlohmann::json;
using ::testing::Eq;

namespace http = boost::beast::http;

class MeterReadingControllerTest : public ::testing::Test {
 protected:
  std::unordered_map<std::string, std::vector<ElectricityReading>> meterAssociatedReadings_;
  ElectricityReadingService electricityReadingService_{meterAssociatedReadings_};
  MeterReadingService meterReadingService_{meterAssociatedReadings_};
  MeterReadingController controller_{electricityReadingService_, meterReadingService_};

  http::request<http::string_body> BuildRequest(http::verb verb, boost::string_view target, const json &request_body) {
    http::request<http::string_body> req{verb, target, 11};
    req.set(http::field::content_type, "application/json");
    req.body() = request_body.dump();
    req.prepare_payload();
    return req;
  }
};

TEST_F(MeterReadingControllerTest, StoreShouldResponseWithErrorGivenNoMeterIdIsSupplied) {
  auto req = BuildRequest(http::verb::post, "/readings/store", R"({})"_json);
  std::vector<std::string> queries;

  auto response = controller_.Store(req, queries);

  EXPECT_THAT(response.result(), Eq(http::status::internal_server_error));
}

TEST_F(MeterReadingControllerTest, StoreShouldResponseWithErrorGivenEmptyMeterReading) {
  json body = R"({
            "smartMeterId": "smart-meter-0",
            "electricityReadings": []
    })"_json;
  auto req = BuildRequest(http::verb::post, "/readings/store", body);
  std::vector<std::string> queries;

  auto response = controller_.Store(req, queries);

  EXPECT_THAT(response.result(), Eq(http::status::internal_server_error));
}

TEST_F(MeterReadingControllerTest, StoreShouldResponseWithErrorGivenNoMeterReadingIsSupplied) {
  json body = R"({
            "smartMeterId": "smart-meter-0"
    })"_json;
  auto req = BuildRequest(http::verb::post, "/readings/store", body);
  std::vector<std::string> queries;

  auto response = controller_.Store(req, queries);

  EXPECT_THAT(response.result(), Eq(http::status::internal_server_error));
}

TEST_F(MeterReadingControllerTest, StoreShouldStoreGivenMultipleBatchesOfMeterReadings) {
  json body1 = R"({
            "smartMeterId": "smart-meter-0",
            "electricityReadings": [
                    {
                            "time": "2021-08-18T06:42:15.725202Z",
                            "reading": 0.001
                    }
            ]
    })"_json;
  json body2 = R"({
            "smartMeterId": "smart-meter-0",
            "electricityReadings": [
                    {
                            "time": "2021-08-18T06:44:15.725202Z",
                            "reading": 0.002
                    }
            ]
    })"_json;
  auto req1 = BuildRequest(http::verb::post, "/readings/store", body1);
  auto req2 = BuildRequest(http::verb::post, "/readings/store", body2);
  std::vector<std::string> queries;

  controller_.Store(req1, queries);
  controller_.Store(req2, queries);

  std::vector<ElectricityReading> expectedElectricityReadings = {
      {detail::fromRfc3339("2021-08-18T06:42:15.725202Z"), 10},
      {detail::fromRfc3339("2021-08-18T06:44:15.725202Z"), 20}
  };

  EXPECT_THAT(meterReadingService_.getReadings("smart-meter-0"), Eq(expectedElectricityReadings));
}

TEST_F(MeterReadingControllerTest, StoreShouldStoreAssociatedWithUserGivenMeterReadingsAssociatedWithTheUser) {
  json body1 = R"({
            "smartMeterId": "smart-meter-0",
            "electricityReadings": [
                    {
                            "time": "2021-08-18T06:42:15.725202Z",
                            "reading": 0.001
                    }
            ]
    })"_json;
  json body2 = R"({
            "smartMeterId": "smart-meter-1",
            "electricityReadings": [
                    {
                            "time": "2021-08-18T06:44:15.725202Z",
                            "reading": 0.002
                    }
            ]
    })"_json;
  auto req1 = BuildRequest(http::verb::post, "/readings/store", body1);
  auto req2 = BuildRequest(http::verb::post, "/readings/store", body2);
  std::vector<std::string> queries;

  controller_.Store(req1, queries);
  controller_.Store(req2, queries);

  std::vector<ElectricityReading> expectedElectricityReadings = {
      {detail::fromRfc3339("2021-08-18T06:42:15.725202Z"), 10},
  };

  EXPECT_THAT(meterReadingService_.getReadings("smart-meter-0"), Eq(expectedElectricityReadings));
}

TEST_F(MeterReadingControllerTest, ReadShouldReturnNotFoundGivenMeterIdThatIsNotRecognised) {
  http::request<http::string_body> req;
  std::vector<std::string> queries = {"smart-meter-0"};

  auto response = controller_.Read(req, queries);

  EXPECT_THAT(response.result(), Eq(http::status::not_found));
}