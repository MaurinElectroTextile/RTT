# -*- coding: utf-8 -*-
from __future__ import unicode_literals

from django.urls import path

from rest_framework.urlpatterns import format_suffix_patterns

from . import views

urlpatterns = [
    path('', views.index),
    path('energy/', views.EnergyMeasureList.as_view(), name = 'energy-list'),
    path('energy/<int:pk>/', views.EnergyMeasureDetail.as_view(), name = 'energy-detail'),
    path('weather/', views.WeatherMeasureList.as_view(), name = 'weather-list'),
    path('weather/<int:pk>/', views.WeatherMeasureDetail.as_view(), name = 'weather-detail'),
    path('combined/today', views.get_combined_today, name = 'combined-today'),
    path('combined/tomorrow', views.get_combined_tomorrow, name = 'combined-tomorrow'),
    path('combined/yesterday', views.get_combined_yesterday, name = 'combined-yesterday'),
    path('proxy/energy/current', views.proxy_energy_current, name = 'proxy-energy-current'),
    path('proxy/energy/forecast', views.proxy_energy_forecast, name = 'proxy-energy-forecast'),
    path('proxy/weather/current', views.proxy_weather_current, name = 'proxy-weather-current'),
    path('proxy/weather/forecast', views.proxy_weather_forecast, name = 'proxy-weather-forecast'),
]

urlpatterns = format_suffix_patterns(urlpatterns)
