ARG CUDA_BASE_VERSION=11.3.0
ARG UBUNTU_RELEASE_VERSION=20.04

FROM nvidia/cuda:${CUDA_BASE_VERSION}-devel-ubuntu${UBUNTU_RELEASE_VERSION}

ARG CUDNN_VERSION=8.2.0

# ==============================================================================
# CUDA & cuDNN
# ==============================================================================

RUN apt-get update && \
    CUDA_VERSION_=$(printf ${CUDA_VERSION} | grep -oE '[0-9]+.[0-9]+') && \
    CUDNN_MAJOR_VERSION=$(printf ${CUDNN_VERSION} | grep -oE '[0-9]+' | head -1) && \
    apt-get install -y --no-install-recommends \
        cuda-samples-${CUDA_VERSION_} \
        libcudnn${CUDNN_MAJOR_VERSION}=${CUDNN_VERSION}*+cuda${CUDA_VERSION_} \
        libcudnn${CUDNN_MAJOR_VERSION}-dev=${CUDNN_VERSION}*+cuda${CUDA_VERSION_} && \
    rm -rf /var/lib/apt/lists/*

# ==============================================================================
# C++ & Python
# ==============================================================================

RUN apt-get update && \
    apt-get install -y --no-install-recommends \
        vim build-essential python3-dev wget curl && \
    ln -s /usr/bin/python3 /usr/bin/python && \
    rm -rf /var/lib/apt/lists/*

RUN wget https://bootstrap.pypa.io/get-pip.py && \
    python get-pip.py && rm -f get-pip.py

RUN pip install cmake

# ==============================================================================
# Jupyter Notebook
# ==============================================================================

ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update && \
    apt-get install -y --no-install-recommends libgl1 python3-opencv && \
    rm -rf /var/lib/apt/lists/*

RUN pip install pandas jupyter_http_over_ws

RUN jupyter serverextension enable --py jupyter_http_over_ws

RUN printf "RUN_NOTEBOOK='jupyter notebook --allow-root \
--NotebookApp.allow_origin='https://colab.research.google.com' \
--port=8888 \
--NotebookApp.port_retries=0'\n" >> /root/.bashrc

# ==============================================================================
# Other Dependencies
# ==============================================================================

RUN pip install numpy scipy matplotlib
RUN pip install torch==1.7.0+cu110 torchvision==0.8.1+cu110 -f https://download.pytorch.org/whl/torch_stable.html
