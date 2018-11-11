# -*- coding: utf-8 -*-
from __future__ import unicode_literals

from datetime import datetime, timedelta
import requests
import json

from django.utils import timezone


OPENWEATHER_LOCATION = 'paris'
OPENWEATHER_COUNTRY = 'fr'
OPENWEATHER_APPID = '2754590248e99a371c9a0f245a6d9d50'

OPENWEATHER_URL_ARGS = 'q=%s,%s&units=metric&appid=%s' % ( OPENWEATHER_LOCATION, OPENWEATHER_COUNTRY, OPENWEATHER_APPID )


def fetchWeatherCurrent():
    url = 'https://api.openweathermap.org/data/2.5/weather?%s' % ( OPENWEATHER_URL_ARGS )
    try:
        r = requests.get(url)
        r.raise_for_status()
    except requests.exceptions.HTTPError as e:
        print(e)
        return []
    return r.json()


def fetchWeatherForecast():
    url = 'https://api.openweathermap.org/data/2.5/forecast?%s' % ( OPENWEATHER_URL_ARGS )
    try:
        r = requests.get(url)
        r.raise_for_status()
    except requests.exceptions.HTTPError as e:
        print(e)
        return []
    return r.json()
