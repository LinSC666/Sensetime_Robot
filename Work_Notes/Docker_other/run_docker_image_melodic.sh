#!/bin/bash

# usage ./run_docker.sh <docker image name>

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"
datetime=`date +%Y%m%d%H%M%S`

# give xhost access to root
xhost +local:root

docker tag gophield:ubuntu18.04 registry.sensetime.com/gophield/gophield:ubuntu18.04
IMAGE_NAME=registry.sensetime.com/gophield/gophield:ubuntu18.04

docker run \
  -it \
  --privileged \
  --mount "type=bind,source=${DIR},destination=/root/gophield" \
  --network host \
  --volume /media:/media \
  --volume /dev:/dev \
  --volume /etc/udev/rules.d:/etc/udev/rules.d \
  --volume /tmp/.X11-unix:/tmp/.X11-unix:rw \
  --env DISPLAY=$DISPLAY \
  --env QT_X11_NO_MITSHM=1 \
  --env="XAUTHORITY=$XAUTH" \
  --volume="$XAUTH:$XAUTH" \
  --runtime=nvidia \
  --name gophield_test_tmp_${datetime} \
  --workdir "/root/gophield/scripts" \
  ${IMAGE_NAME} \
  /bin/bash

# return access control
xhost -local:root

