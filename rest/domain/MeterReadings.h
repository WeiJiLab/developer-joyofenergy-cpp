#ifndef DEVELOPER_JOYOFENERGY_CPP_BEAST_METERREADINGS_H
#define DEVELOPER_JOYOFENERGY_CPP_BEAST_METERREADINGS_H

#include <domain/ElectricityReading.h>

#include <list>
#include <string>

class MeterReadings {
 public:

  MeterReadings(std::string smartMeterId, std::list<ElectricityReading> electricityReadings)
      : smartMeterId_(std::move(smartMeterId)), electricityReadings_(std::move(electricityReadings)) {}

  MeterReadings(const MeterReadings&) = default;
  MeterReadings& operator=(const MeterReadings&) = default;

  MeterReadings(MeterReadings&&) noexcept = default;
  MeterReadings& operator=(MeterReadings&&) noexcept = default;

  ~MeterReadings() = default;

  std::list<ElectricityReading> getElectricityReadings() const { return electricityReadings_; }

  std::string getSmartMeterId() const { return smartMeterId_; }

 private:
  std::list<ElectricityReading> electricityReadings_;
  std::string smartMeterId_;
};

#endif  // DEVELOPER_JOYOFENERGY_CPP_BEAST_METERREADINGS_H
