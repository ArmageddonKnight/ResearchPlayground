ARG CUDA_BASE_VERSION=11.2.0
ARG UBUNTU_RELEASE_VERSION=20.04

FROM nvidia/cuda:${CUDA_BASE_VERSION}-devel-ubuntu${UBUNTU_RELEASE_VERSION}

RUN apt-get update && \
    CUDA_VERSION_=$(printf ${CUDA_VERSION} | grep -oE '[0-9]+.[0-9]+') && \
    apt-get install -y --no-install-recommends \
        cuda-nvvp-${CUDA_VERSION_} \
        libgl1 libfontconfig libxkbcommon-x11-0 && \
    rm -rf /var/lib/apt/lists/*

# ==============================================================================
# C++ & Java
# ==============================================================================

RUN apt-get update && \
    apt-get install -y --no-install-recommends vim && \
    rm -rf /var/lib/apt/lists/*

RUN apt-get update && \
    DEBIAN_FRONTEND=noninteractive \
        apt-get install -y --no-install-recommends \
            libcanberra-gtk-module \
            libcanberra-gtk3-module && \
    rm -rf /var/lib/apt/lists/*

RUN apt-get update && \
    apt-get install -y --no-install-recommends openjdk-8-jdk && \
    ln -sf /usr/lib/jvm/java-1.8.0-openjdk-amd64/jre/bin/java /usr/bin/java && \
    rm -rf /var/lib/apt/lists/*

WORKDIR /mnt
