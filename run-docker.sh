#!/bin/sh

if [ "$1" = "-b" ] || [ "$1" = "--build" ]; then
    docker build --tag tendra/build docker
fi
docker run --tty --interactive --rm --volume "$(pwd)":/tendra tendra/build
