# -*- coding: utf-8 -*-
from __future__ import unicode_literals

from django.utils.timezone import utc

import requests
from datetime import datetime
import json

OPENWEATHER_LOCATION = 'paris'
OPENWEATHER_COUNTRY = 'fr'
OPENWEATHER_APPID = '2754590248e99a371c9a0f245a6d9d50'

OPENWEATHER_URL_ARGS = 'q=%s,%s&units=metric&appid=%s' % ( OPENWEATHER_LOCATION, OPENWEATHER_COUNTRY, OPENWEATHER_APPID )

def fetchWeatherMeasure():
    url = 'https://api.openweathermap.org/data/2.5/weather?%s' % ( OPENWEATHER_URL_ARGS )
    try:
        r = requests.get(url)
        r.raise_for_status()
    except requests.exceptions.HTTPError as e:
        print(e)
        return []

    jo = r.json()
    jr = []
    jd = {}
    jd['dt'] = datetime.fromtimestamp(jo['dt'], utc)
    jd['temp'] = jo['main']['temp']
    jd['temp_min'] = jo['main']['temp_min']
    jd['temp_max'] = jo['main']['temp_max']
    jd['cond_id'] = jo['weather'][0]['id']
    jd['cond_text'] = jo['weather'][0]['main']
    jd['description'] = jo['weather'][0]['description']
    jr.append(jd)

    return jr

