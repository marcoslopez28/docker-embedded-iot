FROM ubuntu:22.04

ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update && apt-get install -y \
    build-essential \
    imagemagick \
    make \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /usr/src/app

COPY . .

CMD ["make", "all"]
