FROM ubuntu:20.04 as CppBase

RUN apt-get update && \
    apt-get install -y --no-install-recommends \
        vim curl python3-dev ca-certificates \
        build-essential && \
    rm -rf /var/lib/apt/lists/*

FROM CppBase

RUN curl https://bootstrap.pypa.io/get-pip.py -o get-pip.py && \
    python3 get-pip.py && rm -f get-pip.py

RUN pip3 install cmake==3.18
