FROM nvidia/cuda:10.0-devel-ubuntu18.04

RUN chmod ugo+rwXt /tmp

ENV CUDNN_VERSION 7.6.3.30-1
ENV CUDNN_MAJOR_VERSION 7
ENV CUDNN_MINOR_VERSION 6

RUN apt-get update && \
    apt-get install -y --no-install-recommends \
        cuda-samples-10-0 \
        cuda-nsight-compute-10-2 \
        cuda-nsight-systems-10-2 \
        libcudnn7=${CUDNN_VERSION}+cuda10.0 \
        libcudnn7-dev=${CUDNN_VERSION}+cuda10.0 \
        vim curl python3 \
        build-essential libboost-all-dev && \
    rm -rf /var/lib/apt/lists/*

RUN curl https://bootstrap.pypa.io/get-pip.py -o get-pip.py && \
    python3 get-pip.py && rm -f get-pip.py && \
    apt-get purge -y curl && apt-get autoremove -y

RUN pip3 install cmake==3.14.4
