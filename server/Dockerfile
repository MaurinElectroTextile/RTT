FROM dyne/devuan:ascii

RUN apt-get -y update --fix-missing
RUN apt-get -y install \
	python3 \
	python3-pip \
	python3-setuptools

WORKDIR /rtt
COPY src /rtt
RUN update-alternatives --install /usr/bin/python python /usr/bin/python3 1
RUN pip3 install -r requirements.txt
