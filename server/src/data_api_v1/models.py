# -*- coding: utf-8 -*-
from __future__ import unicode_literals

from django.db import models


class EnergyMeasure(models.Model):
    d = models.DateField('update date')
    dt = models.DateTimeField('update datetime')
    fossil_ratio = models.DecimalField('fossil ration', max_digits = 3, decimal_places = 2, default = 0.0)
    nuclear_ratio = models.DecimalField('nuclear ration', max_digits = 3, decimal_places = 2, default = 0.0)
    renewable_ratio = models.DecimalField('renewable ratio', max_digits = 3, decimal_places = 2, default = 0.0)

    class Meta:
        indexes = [
            models.Index(fields = [ 'd', 'dt' ]),
        ]
        ordering = [ '-dt' ]


class WeatherMeasure(models.Model):
    d = models.DateField('update date')
    dt = models.DateTimeField('update datetime')
    temp = models.DecimalField('temperature', max_digits = 5, decimal_places = 2, default = 0.0)
    cond_id = models.IntegerField('condition id', default = 0)
    cond_text = models.TextField('condition text', blank = True, default = '')
    description = models.TextField('description', blank = True, default = '')

    class Meta:
        indexes = [
            models.Index(fields = [ 'd', 'dt' ]),
        ]
        ordering = [ '-dt' ]
