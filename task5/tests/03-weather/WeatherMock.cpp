//
// Created by Pavel Akhtyamov on 02.05.2020.
//

#include "WeatherMock.h"

using ::testing::Return;

const std::string LONDON_CITY = "London";
const std::string LA_CITY = "Los Angeles";

TEST(WeatherTestCase, CheckGetResponseForCity) {
  WeatherMock weather;

  const auto response = cpr::Get(
    cpr::Url{"https://klabertants.ml/weather"},
    cpr::Parameters{
        {"city", LONDON_CITY}
    }
  );

  EXPECT_CALL(weather, Get(LONDON_CITY))
  .Times(1)
  .WillOnce(Return(response));

  auto result = weather.GetResponseForCity(LONDON_CITY);
  ASSERT_EQ(json::parse("{\"list\":[{\"main\":{\"temp\":12}}]}"), result);
}
