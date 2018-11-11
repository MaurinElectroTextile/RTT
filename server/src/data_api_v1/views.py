# -*- coding: utf-8 -*-
from __future__ import unicode_literals

from datetime import datetime, date, timedelta

from django.shortcuts import render

from rest_framework import generics
from rest_framework.decorators import api_view
from rest_framework.response import Response
from rest_framework.reverse import reverse

from .models import EnergyMeasure, WeatherMeasure
from .serializers import EnergyMeasureSerializer, WeatherMeasureSerializer
from .providers.openweather import fetchWeatherCurrent, fetchWeatherForecast


@api_view(['GET'])
def index(request, format = None):
    return Response({
        'combined/today': reverse('combined-today', request = request, format = format),
        'combined/tomorrow': reverse('combined-tomorrow', request = request, format = format),
        'combined/yesterday': reverse('combined-yesterday', request = request, format = format),
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


@api_view(['GET'])
def get_combined_today(request, format = None):
    jr = {}
    jr['data'] = {}
    jr['data']['weather'] = {}
    jr['data']['energy'] = {}
    return Response(jr)


@api_view(['GET'])
def get_combined_tomorrow(request, format = None):
    jr = {}
    jr['data'] = {}
    jr['data']['weather'] = {}
    jr['data']['energy'] = {}
    return Response(jr)


@api_view(['GET'])
def get_combined_yesterday(request, format = None):
    jr = {}
    jr['data'] = {}
    jr['data']['weather'] = {}
    jr['data']['energy'] = {}
    return Response(jr)


@api_view(['GET'])
def proxy_weather_current(request, format = None):
    jr = fetchWeatherCurrent()
    return Response(jr)


@api_view(['GET'])
def proxy_weather_forecast(request, format = None):
    jr = fetchWeatherForecast()
    return Response(jr)


