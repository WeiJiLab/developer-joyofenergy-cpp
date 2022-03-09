FROM ubuntu:20.04

COPY sources.list /etc/apt/

ENV DEBIAN_FRONTEND="noninteractive"

RUN apt update && apt install build-essential gcc g++ cmake python3 python3-pip -y && python3 -m pip install conan

CMD ["bash"]

