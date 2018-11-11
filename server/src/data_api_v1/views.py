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
from .providers.openweather import fetchWeatherMeasure


@api_view(['GET'])
def index(request, format = None):
    return Response({
        'combined/today': reverse('combined-today', request = request, format = format),
        'combined/tomorrow': reverse('combined-tomorrow', request = request, format = format),
        'combined/yesterday': reverse('combined-yesterday', request = request, format = format),
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
    update_forced = ('update' in request.GET)
    if not update_forced:
        today = date.today()
        try:
            weather = WeatherMeasure.objects.filter(dt__gte = today).order_by('-dt')[0]
        except IndexError as e:
            update_forced = True
    if update_forced:
        weather_data = fetchWeatherMeasure()[0]
        try:
            weather = WeatherMeasure.objects.get(dt = weather_data['dt'])
        except WeatherMeasure.DoesNotExist as e:
            weather = WeatherMeasure(**weather_data)
            weather.save()
    weather_serializer = WeatherMeasureSerializer(weather)
    jr = {}
    jr['data'] = {}
    jr['data']['weather'] = weather_serializer.data
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

