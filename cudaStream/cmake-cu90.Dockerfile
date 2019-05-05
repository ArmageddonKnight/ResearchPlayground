FROM nvidia/cuda:9.0-cudnn7-devel-ubuntu16.04

RUN apt-get update && \
    apt-get install -y --no-install-recommends \
	vim g++ make wget libboost-all-dev && \
    rm -rf /var/lib/apt/lists/*

ENV CMAKE_VERSION=3.14
ENV CMAKE_BUILD=1

WORKDIR /tmp
RUN wget https://cmake.org/files/v${CMAKE_VERSION}/cmake-${CMAKE_VERSION}.${CMAKE_BUILD}.tar.gz && \
	tar -xzvf cmake-${CMAKE_VERSION}.${CMAKE_BUILD}.tar.gz && \
	rm -rf    cmake-${CMAKE_VERSION}.${CMAKE_BUILD}.tar.gz

# Install CMake
WORKDIR /tmp/cmake-${CMAKE_VERSION}.${CMAKE_BUILD}
RUN ./bootstrap && \
	make -j $(nproc) && \
	make install

WORKDIR /
RUN rm -rf /tmp/cmake-${CMAKE_VERSION}.${CMAKE_BUILD}
