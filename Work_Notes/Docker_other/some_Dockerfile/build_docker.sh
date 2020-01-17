#!/bin/bash

## make sure "registry-mirrors": ["https://docker.mirrors.ustc.edu.cn/"], not in /etc/docker/daemon.json

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"
cd ${DIR}/../..
export DOCKER_BUILDKIT=1
docker build -t gophield:ubuntu18.04 -f docker/x86_64/Dockerfile .