#ifndef __ENERGY_H__
#define __ENERGY_H__

#include <ESP8266HTTPClient.h>

#define ENERGY_OAUTH_HOST         "digital.iservices.rte-france.com"
#define ENERGY_OAUTH_PORT         443
#define ENERGY_OAUTH_URL          "/token/oauth/"
#define ENERGY_OAUTH_CERT_FP      "7A 06 5A FF 89 4D 90 DF DC 15 C1 44 F7 B3 CC B4 ED A7 98 76"

#define ENERGY_API_HOST           "digital.iservices.rte-france.com"
#define ENERGY_API_PORT           443
#define ENERGY_API_URL_ACTUAL     "/open_api/actual_generation/v1/actual_generations_per_production_type"
#define ENERGY_API_URL_FORECASTS  "/open_api/generation_forecast/v2/forecasts"
#define ENERGY_API_CERT_FP        "7A 06 5A FF 89 4D 90 DF DC 15 C1 44 F7 B3 CC B4 ED A7 98 76"

bool energyUpdate();
bool energyParseActualGen(String& payload);
bool energyFetchActualGen(HTTPClient* httpClient);
bool energyParseAuthToken(String& payload);
bool energyFetchAuthToken(HTTPClient* httpClient);

#endif /*__ENERGY_H__*/