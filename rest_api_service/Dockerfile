FROM gcc:latest

WORKDIR /app

COPY . .

RUN apt-get update && apt-get install -y \
    cmake \
    libboost-all-dev \
    libpqxx-dev \
    libpq-dev || true

RUN cmake . && make

CMD ["./rest_api_service"]
