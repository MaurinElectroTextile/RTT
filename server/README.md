# RTT API Server

## Setup

* Install docker: https://docs.docker.com/engine/installation/
* Install docker compose: https://docs.docker.com/compose/install/
* Build the docker image : `./docker.sh build`
* Start the stack: `./docker.sh up`
* Create database: `./manage.sh migrate`
* Create admin user: `./manage.sh createsuperuser --email admin@example.com --username admin`
* You server is accessible at http://locahost
