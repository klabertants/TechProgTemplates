//
// Created by Pavel Akhtyamov on 02.05.2020.
//

#include "WeatherTestCase.h"
#include "WeatherMock.h"

using ::testing::Return;

const std::string LONDON_CITY = "London";
const std::string LA_CITY = "Los Angeles";
const std::string CHELYABINSK_CITY = "Chelyabinsk";

TEST(WeatherTestCase, CheckGetResponseForCityException) {
  WeatherMock weather;

  const auto response = cpr::Get(
    cpr::Url{"https://klabertants.ml/weather"},
    cpr::Parameters{
        {"city", CHELYABINSK_CITY}
    }
  );

  EXPECT_CALL(weather, Get(CHELYABINSK_CITY))
  .Times(1)
  .WillOnce(Return(response));

  ASSERT_THROW(weather.GetResponseForCity("Chelyabinsk"), std::invalid_argument);
}

TEST(WeatherTestCase, CheckGetTemperature) {
  WeatherMock weather;

  const auto response = cpr::Get(
    cpr::Url{"https://klabertants.ml/weather"},
    cpr::Parameters{
        {"city", LA_CITY}
    }
  );

  EXPECT_CALL(weather, Get(LA_CITY))
  .Times(1)
  .WillOnce(Return(response));

  auto result = weather.GetTemperature(LA_CITY);
  ASSERT_EQ(26.0f, result);
}

TEST(WeatherTestCase, CheckFindDiffBetweenTwoCities) {
  WeatherMock weather;

  const auto responseLondon = cpr::Get(
    cpr::Url{"https://klabertants.ml/weather"},
    cpr::Parameters{
        {"city", LONDON_CITY}
    }
  );

  const auto responseLA = cpr::Get(
    cpr::Url{"https://klabertants.ml/weather"},
    cpr::Parameters{
        {"city", LA_CITY}
    }
  );

  EXPECT_CALL(weather, Get(LA_CITY))
  .Times(1)
  .WillOnce(Return(responseLA));

  EXPECT_CALL(weather, Get(LONDON_CITY))
  .Times(1)
  .WillOnce(Return(responseLondon));

  auto result = weather.FindDiffBetweenTwoCities(LA_CITY, LONDON_CITY);
  ASSERT_EQ(14.0f, result);
}

TEST(WeatherTestCase, CheckGetDifferenceStringWarmer) {
  WeatherMock weather;

  const auto responseLondon = cpr::Get(
    cpr::Url{"https://klabertants.ml/weather"},
    cpr::Parameters{
        {"city", LONDON_CITY}
    }
  );

  const auto responseLA = cpr::Get(
    cpr::Url{"https://klabertants.ml/weather"},
    cpr::Parameters{
        {"city", LA_CITY}
    }
  );

  EXPECT_CALL(weather, Get(LA_CITY))
  .Times(1)
  .WillOnce(Return(responseLA));

  EXPECT_CALL(weather, Get(LONDON_CITY))
  .Times(1)
  .WillOnce(Return(responseLondon));

  auto result = weather.GetDifferenceString(LA_CITY, LONDON_CITY);
  ASSERT_EQ("Weather in " + LA_CITY + " is warmer than in " + LONDON_CITY + " by 14 degrees", result);
}

TEST(WeatherTestCase, CheckGetDifferenceStringColder) {
  WeatherMock weather;

  const auto responseLondon = cpr::Get(
    cpr::Url{"https://klabertants.ml/weather"},
    cpr::Parameters{
        {"city", LONDON_CITY}
    }
  );

  const auto responseLA = cpr::Get(
    cpr::Url{"https://klabertants.ml/weather"},
    cpr::Parameters{
        {"city", LA_CITY}
    }
  );

  EXPECT_CALL(weather, Get(LA_CITY))
  .Times(1)
  .WillOnce(Return(responseLA));

  EXPECT_CALL(weather, Get(LONDON_CITY))
  .Times(1)
  .WillOnce(Return(responseLondon));

  auto result = weather.GetDifferenceString(LONDON_CITY, LA_CITY);
  ASSERT_EQ("Weather in " + LONDON_CITY + " is colder than in " + LA_CITY + " by 14 degrees", result);
}

TEST(WeatherTestCase, CheckSetApiKey) {
  Weather weather;

  weather.SetApiKey("Pasha Krutoy");
}
