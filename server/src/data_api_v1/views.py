# -*- coding: utf-8 -*-
from __future__ import unicode_literals

from datetime import datetime, date, timedelta

from django.db.models import Min, Max
from django.shortcuts import render
from django.utils import timezone

from rest_framework import generics
from rest_framework.decorators import api_view
from rest_framework.response import Response
from rest_framework.reverse import reverse

from .models import EnergyMeasure, WeatherMeasure
from .serializers import EnergyMeasureSerializer, WeatherMeasureSerializer
from .providers.openweather import fetchWeatherCurrent, fetchWeatherForecast
from .providers.rte import fetchEnergyCurrent, fetchEnergyForecast


@api_view(['GET'])
def index(request, format = None):
    return Response({
        'combined/today': reverse('combined-today', request = request, format = format),
        'combined/tomorrow': reverse('combined-tomorrow', request = request, format = format),
        'combined/yesterday': reverse('combined-yesterday', request = request, format = format),
        'proxy/energy/current': reverse('proxy-energy-current', request = request, format = format),
        'proxy/energy/forecast': reverse('proxy-energy-forecast', request = request, format = format),
        'proxy/weather/current': reverse('proxy-weather-current', request = request, format = format),
        'proxy/weather/forecast': reverse('proxy-weather-forecast', request = request, format = format),
        'energy': reverse('energy-list', request = request, format = format),
        'weather': reverse('weather-list', request = request, format = format)
    })


class EnergyMeasureList(generics.ListAPIView):
    queryset = EnergyMeasure.objects.all()
    serializer_class = EnergyMeasureSerializer


class EnergyMeasureDetail(generics.RetrieveUpdateDestroyAPIView):
    queryset = EnergyMeasure.objects.all()
    serializer_class = EnergyMeasureSerializer


class WeatherMeasureList(generics.ListAPIView):
    queryset = WeatherMeasure.objects.all()
    serializer_class = WeatherMeasureSerializer


class WeatherMeasureDetail(generics.RetrieveUpdateDestroyAPIView):
    queryset = WeatherMeasure.objects.all()
    serializer_class = WeatherMeasureSerializer


def updateWeather(jo):
    dt = datetime.fromtimestamp(jo['dt'], timezone.utc)
    d = dt.date()
    try:
        wm = WeatherMeasure.objects.get(dt = dt)
    except WeatherMeasure.DoesNotExist:
        wm = WeatherMeasure(d = d, dt = dt)
    wm.temp = jo['main']['temp']
    wm.cond_id = jo['weather'][0]['id']
    wm.cond_text = jo['weather'][0]['main']
    wm.description = jo['weather'][0]['description']
    wm.save()
    return wm


def getCurrentWeather():
    jo = fetchWeatherForecast()
    if 'list' in jo:
        for je in jo['list']:
            updateWeather(je)
    jo = fetchWeatherCurrent()
    dt = datetime.fromtimestamp(jo['dt'], timezone.utc)
    d = dt.date()
    wm = updateWeather(jo)
    ws = WeatherMeasureSerializer(wm)
    jd = ws.data
    jd['temp_min'] = WeatherMeasure.objects.filter(d__exact = d).aggregate(Min('temp'))['temp__min']
    jd['temp_max'] = WeatherMeasure.objects.filter(d__exact = d).aggregate(Max('temp'))['temp__max']
    return jd


def getTomorrowWeather():
    dt = timezone.now() + timedelta(days = 1)
    d = dt.date()
    jo = fetchWeatherForecast()
    if 'list' in jo:
        for je in jo['list']:
            updateWeather(je)
    try:
        wm = WeatherMeasure.objects.filter(d__exact = d, dt__lte = dt).order_by('-dt')[0]
    except IndexError:
        jd = {}
        jd['error'] = {}
        jd['error']['code'] = 1
        jd['error']['message'] = 'no data'
        return jd
    ws = WeatherMeasureSerializer(wm)
    jd = ws.data
    jd['temp_min'] = WeatherMeasure.objects.filter(d__exact = d).aggregate(Min('temp'))['temp__min']
    jd['temp_max'] = WeatherMeasure.objects.filter(d__exact = d).aggregate(Max('temp'))['temp__max']
    return jd


def getYesterdayWeather():
    dt = timezone.now() - timedelta(days = 1)
    d = dt.date()
    try:
        wm = WeatherMeasure.objects.filter(d__exact = d, dt__lte = dt).order_by('-dt')[0]
    except IndexError:
        jd = {}
        jd['error'] = {}
        jd['error']['code'] = 1
        jd['error']['message'] = 'no data'
        return jd
    ws = WeatherMeasureSerializer(wm)
    jd = ws.data
    jd['temp_min'] = WeatherMeasure.objects.filter(d__exact = d).aggregate(Min('temp'))['temp__min']
    jd['temp_max'] = WeatherMeasure.objects.filter(d__exact = d).aggregate(Max('temp'))['temp__max']
    return jd


@api_view(['GET'])
def get_combined_today(request, format = None):
    jr = {}
    jr['data'] = {}
    jr['data']['weather'] = getCurrentWeather()
    jr['data']['energy'] = {}
    return Response(jr)


@api_view(['GET'])
def get_combined_tomorrow(request, format = None):
    jr = {}
    jr['data'] = {}
    jr['data']['weather'] = getTomorrowWeather()
    jr['data']['energy'] = {}
    return Response(jr)


@api_view(['GET'])
def get_combined_yesterday(request, format = None):
    jr = {}
    jr['data'] = {}
    jr['data']['weather'] = getYesterdayWeather()
    jr['data']['energy'] = {}
    return Response(jr)


@api_view(['GET'])
def proxy_energy_current(request, format = None):
    jr = fetchEnergyCurrent()
    return Response(jr)


@api_view(['GET'])
def proxy_energy_forecast(request, format = None):
    jr = fetchEnergyForecast()
    return Response(jr)


@api_view(['GET'])
def proxy_weather_current(request, format = None):
    jr = fetchWeatherCurrent()
    return Response(jr)


@api_view(['GET'])
def proxy_weather_forecast(request, format = None):
    jr = fetchWeatherForecast()
    return Response(jr)


