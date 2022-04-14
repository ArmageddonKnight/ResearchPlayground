ARG CUDA_BASE_VERSION=11.2.0
ARG UBUNTU_RELEASE_VERSION=20.04

FROM nvidia/cuda:${CUDA_BASE_VERSION}-devel-ubuntu${UBUNTU_RELEASE_VERSION}

RUN apt-get update && \
    CUDA_VERSION_=$(printf ${CUDA_VERSION} | grep -oE '[0-9]+.[0-9]+') && \
    apt-get install -y --no-install-recommends \
        cuda-nvvp-${CUDA_VERSION_} \
        libcudnn${CUDNN_MAJOR_VERSION}=${CUDNN_VERSION}*+cuda${CUDA_VERSION_} \
        libcudnn${CUDNN_MAJOR_VERSION}-dev=${CUDNN_VERSION}*+cuda${CUDA_VERSION_} && \
    rm -rf /var/lib/apt/lists/*
