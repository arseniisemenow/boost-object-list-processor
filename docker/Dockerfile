FROM ubuntu:20.04

WORKDIR /app

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
gdb

RUN apt-get install -y \
    openssh-server

# Create a user and set a password
RUN useradd -m user && yes password | passwd user

# Configure SSH
RUN mkdir /var/run/sshd

# Allow password authentication and configure SSH
RUN sed -i 's/#PermitRootLogin prohibit-password/PermitRootLogin yes/' /etc/ssh/sshd_config && \
    sed -i 's/#PasswordAuthentication yes/PasswordAuthentication yes/' /etc/ssh/sshd_config

EXPOSE 22

#RUN cmake . && make

#CMD ["./rest_api_service"]
#ENTRYPOINT ["tail", "-f", "/dev/null"]

CMD ["/usr/sbin/sshd", "-D"]