FROM gcc:latest as build

RUN apt-get update && \
    apt-get install -y \
      libboost-dev libboost-program-options-dev \
      cmake \
      libzmq3-dev

ADD ./src /client/src

WORKDIR /client/build

RUN cmake ../src && \
    cmake --build .

FROM ubuntu:latest

RUN groupadd -r pubsub && useradd -r -g pubsub tester
USER tester

WORKDIR /client

COPY --from=build /client/build/server_app .

# Установим точку входа
ENTRYPOINT ["./server_app"]

