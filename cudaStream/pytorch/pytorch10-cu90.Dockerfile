FROM nvidia/cuda:9.0-cudnn7-devel-ubuntu16.04

RUN apt-get update && \
    apt-get install -y --no-install-recommends \
        vim \
        python3-dev \
        python3-pip \
        python3-numpy \
        python3-six \
        python3-setuptools && \
    rm -rf /var/lib/apt/lists/*

RUN pip3 install --upgrade pip

RUN pip3 install torch==1.0 torchvision==0.2.2
