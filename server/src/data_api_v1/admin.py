# -*- coding: utf-8 -*-
from __future__ import unicode_literals

from django.contrib import admin

from .models import EnergyMeasure, WeatherMeasure

admin.site.register(EnergyMeasure)
admin.site.register(WeatherMeasure)
