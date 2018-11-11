# -*- coding: utf-8 -*-
from __future__ import unicode_literals

from datetime import datetime, timedelta
import requests
import json
import logging

from django.utils import timezone


logger = logging.getLogger(__name__)

RTE_ID_B64 = 'YTBjYzMyODQtYzE5Yi00YzZjLTk1YTMtNGFmYmUxY2ViZjlhOmJhNzViYzFkLWI4NWEtNDUwMS05ZjVmLTZjYzdjNGE0YTlmMg=='

rte_auth_token = ''
rte_auth_expiry_date = datetime.fromtimestamp(0, timezone.utc)


def getAuthToken():
    global rte_auth_expiry_date
    global rte_auth_token
    now = timezone.now()
    if now < rte_auth_expiry_date:
        logger.info('rte: auth token still valid: %s', rte_auth_token)
        return rte_auth_token
    url = 'https://digital.iservices.rte-france.com/token/oauth/'
    auth_header = { 'Authorization': 'Basic ' + RTE_ID_B64}
    r = requests.post(url, headers = auth_header)
    jr = r.json()
    ttl = jr['expires_in']
    rte_auth_token = jr['access_token']
    rte_auth_expiry_date = now + timedelta(seconds = ttl)
    logger.info('rte: auth token refreshed: %s, expire in: %d seconds', rte_auth_token, ttl)
    return rte_auth_token


def fetchEnergyCurrent(period=timedelta(days=30)):
    now = timezone.now()
    url = 'https://digital.iservices.rte-france.com/open_api/actual_generation/v1/actual_generations_per_production_type'
    auth_header = { 'Authorization': 'Bearer ' + getAuthToken()}
    try :
        r = requests.get(url, headers = auth_header)
        r.raise_for_status()
        jr = r.json()
    except requests.exceptions.HTTPError as e:
        jr = {}
        jr['error'] = {}
        jr['error']['status-code'] = r.status_code
    return jr


def fetchEnergyForecast(period=timedelta(days=30)):
    now = timezone.now()
    url = 'https://digital.iservices.rte-france.com/open_api/generation_forecast/v2/forecasts'
    auth_header = { 'Authorization': 'Bearer ' + getAuthToken()}
    try :
        r = requests.get(url, headers = auth_header)
        r.raise_for_status()
        jr = r.json()
    except requests.exceptions.HTTPError as e:
        jr = {}
        jr['error'] = {}
        jr['error']['status-code'] = r.status_code
    return jr
