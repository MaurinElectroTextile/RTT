# -*- coding: utf-8 -*-
from __future__ import unicode_literals

from django.db import models


class EnergyMeasure(models.Model):
    dt = models.DateTimeField('update date')
    fossil_ratio = models.DecimalField('fossil ration', max_digits = 3, decimal_places = 2, default = 0.0)
    nuclear_ratio = models.DecimalField('nuclear ration', max_digits = 3, decimal_places = 2, default = 0.0)
    renewable_ratio = models.DecimalField('renewable ratio', max_digits = 3, decimal_places = 2, default = 0.0)


class WeatherMeasure(models.Model):
    dt = models.DateTimeField('update date')
    temp = models.DecimalField('temperature', max_digits = 5, decimal_places = 2, default = 0.0)
    temp_min = models.DecimalField('minimum temperature', max_digits = 5, decimal_places = 2, default = 0.0)
    temp_max = models.DecimalField('maximum temperature', max_digits = 5, decimal_places = 2, default = 0.0)
    cond_id = models.IntegerField('condition id', default = 0)
    cond_text = models.TextField('condition text', blank = True, default = '')
    description = models.TextField('description', blank = True, default = '')