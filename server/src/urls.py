# -*- coding: utf-8 -*-

from django.urls import path
from django.conf.urls import include, url
from django.contrib import admin

from rest_framework import routers
from rest_framework.documentation import include_docs_urls
from rest_framework.schemas import get_schema_view

API_TITLE = 'Smart Window Data API'
API_DESCRIPTION = 'A Web API for viewing Smart Window Data.'

schema_view = get_schema_view(title=API_TITLE)


urlpatterns = [
    url(r'^admin/', admin.site.urls),
    url(r'^api-auth/', include('rest_framework.urls', namespace='rest_framework')),
    url(r'^docs/', include_docs_urls(title=API_TITLE, description=API_DESCRIPTION)),
    url(r'^schema/$', schema_view),
    path('data/v1/', include('data_api_v1.urls')),
]
