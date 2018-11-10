# -*- coding: utf-8 -*-
from __future__ import unicode_literals

from django.shortcuts import render

from rest_framework import generics
from rest_framework.decorators import api_view
from rest_framework.response import Response
from rest_framework.reverse import reverse

from .models import EnergyMeasure, WeatherMeasure
from .serializers import EnergyMeasureSerializer, WeatherMeasureSerializer


@api_view(['GET'])
def index(request, format = None):
    return Response({
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