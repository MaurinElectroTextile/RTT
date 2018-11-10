# -*- coding: utf-8 -*-
from __future__ import unicode_literals

from rest_framework import serializers

from .models import EnergyMeasure, WeatherMeasure


class EnergyMeasureSerializer(serializers.ModelSerializer):
    ts = serializers.SerializerMethodField()

    def get_ts(self, obj):
        return int(obj.dt.timestamp())

    class Meta:
        model = EnergyMeasure
        fields = ('id', 'dt', 'ts', 'fossil_ratio', 'nuclear_ratio', 'renewable_ratio')


class WeatherMeasureSerializer(serializers.ModelSerializer):
    ts = serializers.SerializerMethodField()

    def get_ts(self, obj):
        return int(obj.dt.timestamp())

    class Meta:
        model = WeatherMeasure
        fields = ('id', 'dt', 'ts', 'temp', 'temp_min', 'temp_max', 'cond_id', 'cond_text', 'description')

