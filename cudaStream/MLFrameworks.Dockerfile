FROM nvidia/cuda:9.2-cudnn7-devel-ubuntu16.04

RUN apt-get update && \
    apt-get install -y --no-install-recommends \
	vim \
	libopencv-dev \
	libopenblas-dev \
	python-dev \
	python-pip \
	python-numpy \
	python-six \
	python-setuptools && \
    rm -rf /var/lib/apt/lists/*

RUN pip install --upgrade pip && \
    pip install tensorflow-gpu==1.12.0 \
	mxnet-cu92==1.4.0 \
	torch==1.0 torchvision==1.0
