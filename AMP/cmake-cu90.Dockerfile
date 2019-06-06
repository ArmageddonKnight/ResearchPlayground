FROM nvidia/cuda:9.0-cudnn7-devel-ubuntu16.04

RUN apt-get update && \
    apt-get install -y --no-install-recommends \
        cuda-samples-9-0 \
        curl python3 \
        vim build-essential libboost-all-dev && \
    rm -rf /var/lib/apt/lists/*

RUN curl https://bootstrap.pypa.io/get-pip.py -o get-pip.py && \
    python3 get-pip.py && rm -f get-pip.py && \
    apt-get purge -y curl && apt-get autoremove -y

RUN pip3 install cmake
