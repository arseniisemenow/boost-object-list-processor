FROM ubuntu:20.04

WORKDIR /app

COPY . .

ARG DEBIAN_FRONTEND=noninteractive

RUN apt-get update && apt-get upgrade -y  && apt-get install -y \
cmake \
gfortran \
libcoarrays-dev \
libboost-all-dev \
aptitude \
libpqxx-dev \
libpq-dev \
postgresql-server-dev-all \
rsync \
gcc \
g++ \
gdb \
nlohmann-json3-dev

RUN make uninstall && make install_server

CMD ["./build-server/object-list-processor-server"]
#ENTRYPOINT ["tail", "-f", "/dev/null"]

