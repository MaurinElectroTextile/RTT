#!/bin/bash

docker-compose -f docker-compose.yml exec web "./manage.py" "$@"
