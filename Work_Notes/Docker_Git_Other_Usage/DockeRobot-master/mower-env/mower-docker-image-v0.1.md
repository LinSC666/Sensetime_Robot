# Steps to use mower docker image
## build details
- ubuntu 16.04
- opengl
- cuda 9.0
- cudnn 7.0.5
- ros-kinetic
- git-lfs 1.4.4
- opencv 3.3.1 (in ROS)
- TensorRT 3.0.4
- husqvarna hrp ros packages
- other utilities

## Notes
HOME DIR: /sensetime
USER NAME: sensetime
USER PASSWORD: sensetime

## requirements
docker
nvidia-docker2
nvidia driver >= 410

## pull command
docker login registry.sensetime.com
docker pull registry.sensetime.com/mower-env/mower-env:cuda10.0-py2-ubuntu16.04

## run command (home directory refer to image home directory)
docker run -it \
    --env="DISPLAY=$DISPLAY" \
    --env="QT_X11_NO_MITSHM=1" \
    --volume="/tmp/.X11-unix:/tmp/.X11-unix:rw" \
    --env="XAUTHORITY=$XAUTH" \
    --volume="$XAUTH:$XAUTH" \
    --runtime=nvidia \
    --privileged -v "/dev:/dev" \
    -v "/home:/home" \
    registry.sensetime.com/mower-env/mower-env:cuda10.0-py2-ubuntu16.04 \
    bash

## run as root (home directory refer to image home directory)
docker run -it \
    --env="DISPLAY=$DISPLAY" \
    --env="QT_X11_NO_MITSHM=1" \
    --volume="/tmp/.X11-unix:/tmp/.X11-unix:rw" \
    --env="XAUTHORITY=$XAUTH" \
    --volume="$XAUTH:$XAUTH" \
    --runtime=nvidia \
    --privileged -v "/dev:/dev" \
    -v "/home:/home" \
    --user root \
    registry.sensetime.com/mower-env/mower-env:cuda10.0-py2-ubuntu16.04 \
    bash

## continue a container (if it is started)
docker exec -it --privileged [--user root] <container ID> bash

