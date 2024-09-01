FROM gcc:latest

WORKDIR /app

COPY . .

RUN apt-get update && apt-get install -y \
    cmake \
    libboost-all-dev \
    libpqxx-dev \
    libpq-dev \
    rsync \
    gdb || true
RUN apt-get install -y \
    openssh-server || true

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