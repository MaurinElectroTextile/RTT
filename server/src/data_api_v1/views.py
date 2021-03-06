# -*- coding: utf-8 -*-
from __future__ import unicode_literals

from datetime import datetime, date, timedelta
from dateutil import parser
import json
import random

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
from .providers.rte import fetchEnergyCurrent, fetchEnergyForecast, getProductionCategory



@api_view(['GET'])
def index(request, format = None):
    return Response({
        'combined/update': reverse('combined-update', request = request, format = format),
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


def formatErrorResponse(code, message):
    jr = {}
    jr['error'] = {}
    jr['error']['code'] = code
    jr['error']['message'] = message
    return jr


def updateEnergy(jo):
    dt = parser.parse(jo['dt'])
    d = dt.date()
    try:
        m = EnergyMeasure.objects.get(dt = dt)
    except EnergyMeasure.DoesNotExist:
        m = EnergyMeasure(d = d, dt = dt)
    total = jo['total']
    m.fossil_ratio = jo['fossil'] / total
    m.nuclear_ratio = jo['nuclear'] / total
    m.renewable_ratio = jo['renewable'] / total
    m.save()
    return m


def fetchEnergy():
    jo = fetchEnergyCurrent()
    jr = []
    if 'actual_generations_per_production_type' not in jo:
        return formatErrorResponse(1, "energy/current: key 'actual_generations_per_production_type' missing")
    ja = jo['actual_generations_per_production_type']
    n_pt = len(ja)
    if n_pt == 0:
        return formatErrorResponse(2, "energy/current: no production type returned")
    n_val = len(ja[0]['values'])
    if n_pt == 0:
        return formatErrorResponse(3, "energy/current: no values returned")
    for i_val in range(0, n_val):
        je = {}
        je['dt'] = ja[0]['values'][i_val]['end_date']
        je['total'] = 0
        for i_pt in range(0, n_pt):
            pt = ja[i_pt]
            if pt['production_type'] == "TOTAL":
                continue
            pc = getProductionCategory(pt['production_type'])
            val = pt['values'][i_val]['value']
            if pc not in je:
                je[pc] = 0
            je[pc] += val
            je['total'] += val
        jr.append(je)
    jo = jr
    jr = {}
    jr['current'] = []
    for je in jo:
        m = updateEnergy(je)
        s = EnergyMeasureSerializer(m)
        jr['current'].append(s.data)
    return jr


def getEnergy(dt):
    d = dt.date()
    try:
        m = EnergyMeasure.objects.filter(d__exact = d, dt__lte = dt).order_by('-dt')[0]
    except IndexError:
        return formatErrorResponse(1, "energy/yesterday: no data found")
    s = EnergyMeasureSerializer(m)
    return s.data


def getCurrentEnergy():
    dt = timezone.now()
    return getEnergy(dt)

def getTomorrowEnergy():
    dt = timezone.now() + timedelta(days = 1)
    d = dt.date()
    try:
        m = EnergyMeasure.objects.filter(d__exact = d, dt__lte = dt).order_by('-dt')[0]
    except IndexError:
        dt = timezone.now()
        d = dt.date()
        try:
            m = EnergyMeasure.objects.filter(d__exact = d, dt__lte = dt).order_by('-dt')[0]
        except IndexError:
            return formatErrorResponse(1, "energy/tomorrow: no data found")
        dt = m.dt + timedelta(days = 1)
        j = {}
        j['dt'] = dt
        j['d'] = dt.date()
        j['fossil_ratio'] = float(m.fossil_ratio) * random.uniform(0.8, 1.2)
        j['renewable_ratio'] = float(m.renewable_ratio) * random.uniform(0.8, 1.2)
        j['nuclear_ratio'] = 1.0 - j['fossil_ratio'] - j['renewable_ratio']
        m = EnergyMeasure(**j)
        m.save()
    s = EnergyMeasureSerializer(m)
    return s.data


'''
def getTomorrowEnergy():
    jo = fetchEnergyForecast()
    jr = {}
    if 'forecasts' not in jo:
        return formatErrorResponse(1, "energy/tomorrow: key 'forecasts' missing")
    ja = jo['forecasts']
    n_pt = len(ja)
    if n_pt == 0:
        return formatErrorResponse(2, "energy/tomorrow: no production type returned")
    for i_pt in range(0, n_pt):
        pt = ja[i_pt]
        n_val = len(pt['values'])
        if n_val == 0:
            return formatErrorResponse(3, "energy/tomorrow: no values returned")
        for i_val in range(0, n_val):
            dt = pt['values'][i_val]['end_date']
            if dt in jr:
                je = jr[dt]
            else:
                je = {}
                je['dt'] = pt['values'][i_val]['end_date']
                je['fossil'] = 0
                je['nuclear'] = 0
                je['renewable'] = 0
                je['total'] = 0
            val = pt['values'][i_val]['value']
            if pt['production_type'] == 'AGGREGATED_PROGRAMMABLE_FRANCE':
                je['fossil'] += val * 0.1
                je['nuclear'] += val * 0.9
            elif pt['production_type'] == 'AGGREGATED_NON_PROGRAMMABLE_FRANCE':
                je['fossil'] += val * 0.05
                je['renewable'] += val * 0.95
            else:
                continue
            jr[dt] = je
    jo = jr
    jr = []
    for dt in sorted(jo, reverse = True):
        je = jo[dt]
        je['total'] = je['fossil'] + je['nuclear'] + je['renewable']
        m = updateEnergy(je)
        jr.append(je)
    return jr
'''


def getYesterdayEnergy():
    dt = timezone.now() - timedelta(days = 1)
    return getEnergy(dt)



def updateWeather(jo):
    dt = datetime.fromtimestamp(jo['dt'], timezone.utc)
    d = dt.date()
    try:
        wm = WeatherMeasure.objects.get(dt = dt)
    except WeatherMeasure.DoesNotExist:
        wm = WeatherMeasure(d = d, dt = dt)
    wm.temp = jo['main']['temp']
    wm.cloudiness = jo['clouds']['all']
    wm.cond_id = jo['weather'][0]['id']
    wm.cond_text = jo['weather'][0]['main']
    wm.description = jo['weather'][0]['description']
    wm.save()
    return wm


def fetchWeather():
    jr = {}
    je = fetchWeatherCurrent()
    m = updateWeather(je)
    s = WeatherMeasureSerializer(m)
    jr['current'] = s.data
    jr['forecast'] = []
    jo = fetchWeatherForecast()
    if 'list' in jo:
        for je in jo['list']:
            m = updateWeather(je)
            s = WeatherMeasureSerializer(m)
            jr['forecast'].append(s.data)
    return jr

def getWeather(dt):
    d = dt.date()
    try:
        m = WeatherMeasure.objects.filter(d__exact = d, dt__lte = dt).order_by('-dt')[0]
    except IndexError:
        return formatErrorResponse(1, "weather: no data found")
    s = WeatherMeasureSerializer(m)
    jr = s.data
    jr['temp_min'] = WeatherMeasure.objects.filter(d__exact = d).aggregate(Min('temp'))['temp__min']
    jr['temp_max'] = WeatherMeasure.objects.filter(d__exact = d).aggregate(Max('temp'))['temp__max']
    return jr



def getCurrentWeather():
    dt = timezone.now()
    return getWeather(dt)


def getTomorrowWeather():
    dt = timezone.now() + timedelta(days = 1)
    return getWeather(dt)


def getYesterdayWeather():
    dt = timezone.now() - timedelta(days = 1)
    return getWeather(dt)


@api_view(['GET'])
def get_combined_update(request, format = None):
    jr = {}
    jr['data'] = {}
    jr['data']['weather'] = fetchWeather()
    jr['data']['energy'] = fetchEnergy()
    return Response(jr)


@api_view(['GET'])
def get_combined_today(request, format = None):
    jr = {}
    jr['data'] = {}
    jr['data']['weather'] = getCurrentWeather()
    jr['data']['energy'] = getCurrentEnergy()
    return Response(jr)


@api_view(['GET'])
def get_combined_tomorrow(request, format = None):
    jr = {}
    jr['data'] = {}
    jr['data']['weather'] = getTomorrowWeather()
    jr['data']['energy'] = getTomorrowEnergy()
    return Response(jr)


@api_view(['GET'])
def get_combined_yesterday(request, format = None):
    jr = {}
    jr['data'] = {}
    jr['data']['weather'] = getYesterdayWeather()
    jr['data']['energy'] = getYesterdayEnergy()
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


