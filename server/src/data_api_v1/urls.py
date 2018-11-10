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
]

urlpatterns = format_suffix_patterns(urlpatterns)
