FROM nvcr.io/nvidia/tensorflow:18.08-py2
# e.g. FROM osrf/ros:kinetic-desktop-full

MAINTAINER Jiaming Liu (liujiaming@sensetime.com)

# optional, if the default user is not "root", you might need to switch to root here and at the end of the script to the original user again.
# e.g.
# USER root

RUN sed -i 's/archive.ubuntu.com/mirrors.ustc.edu.cn/g' /etc/apt/sources.list && \
    sh -c '. /etc/lsb-release && echo "deb http://mirrors.ustc.edu.cn/ros/ubuntu/ $DISTRIB_CODENAME main" > /etc/apt/sources.list.d/ros-latest.list' && \
    apt-key adv --keyserver hkp://ha.pool.sks-keyservers.net:80 --recv-key 421C365BD9FF1F717815A3895523BAEEB01FA116 && \
    apt-get clean && \
    apt-get update --fix-missing && \
    DEBIAN_FRONTEND=noninteractive apt-get install -yq --no-install-recommends \
        ros-kinetic-desktop ros-kinetic-moveit ros-kinetic-ros-control ros-kinetic-ros-controllers iputils-ping ros-kinetic-trac-ik-kinematics-plugin ros-kinetic-catkin python-catkin-tools \
        pkg-config \
        libxau-dev \
        libxdmcp-dev \
        libxcb1-dev \
        libxext-dev \
        libx11-dev \
        libasound2 libatk1.0-0 libc6 libcairo2 libcups2 libdbus-1-3 \
        libexpat1 libfontconfig1 libgcc1 libgconf-2-4 libgdk-pixbuf2.0-0 libglib2.0-0 libgtk-3-0 libnspr4 \
        libpango-1.0-0 libpangocairo-1.0-0 libstdc++6 libx11-6 libx11-xcb1 libxcb1 \
        libxcursor1 libxdamage1 libxext6 libxfixes3 libxi6 libxrandr2 libxrender1 libxss1 libxtst6 \
        libnss3 \
        libglu1



    # dpkg --remove --force-depends python-pyassimp && \

RUN echo "source /opt/ros/kinetic/setup.bash" >> /root/.bashrc && \
    pip install -U pip numpy && \
    pip install pyassimp==3.3 gym==0.10.5 ruamel.yaml opencv-python && \
    pip install https://download.pytorch.org/whl/cu100/torch-1.1.0-cp27-cp27mu-linux_x86_64.whl && \
    pip install torchvision && \ 
    pip install --upgrade cryptography && \
    python -m easy_install --upgrade pyOpenSSL && \
    # DEBIAN_FRONTEND=noninteractive apt-get install python-pyassimp && \
    apt-get clean && \
    rm -rf /var/lib/apt/lists/*

RUN rosdep init && \
    rosdep update

# replace with other Ubuntu version if desired
# see: https://hub.docker.com/r/nvidia/opengl/
COPY --from=nvidia/cudagl:9.0-runtime-ubuntu16.04 \
  /usr/local/lib/x86_64-linux-gnu \
  /usr/local/lib/x86_64-linux-gnu

# replace with other Ubuntu version if desired
# see: https://hub.docker.com/r/nvidia/opengl/
COPY --from=nvidia/cudagl:9.0-runtime-ubuntu16.04 \
  /usr/local/share/glvnd/egl_vendor.d/10_nvidia.json \
  /usr/local/share/glvnd/egl_vendor.d/10_nvidia.json

RUN echo '/usr/local/lib/x86_64-linux-gnu' >> /etc/ld.so.conf.d/glvnd.conf && \
    ldconfig && \
    echo '/usr/local/$LIB/libGL.so.1' >> /etc/ld.so.preload && \
    echo '/usr/local/$LIB/libEGL.so.1' >> /etc/ld.so.preload

# nvidia-container-runtime
ENV NVIDIA_VISIBLE_DEVICES \
    ${NVIDIA_VISIBLE_DEVICES:-all}
ENV NVIDIA_DRIVER_CAPABILITIES \
    ${NVIDIA_DRIVER_CAPABILITIES:+$NVIDIA_DRIVER_CAPABILITIES,}graphics

WORKDIR /root

# USER original_user
# RUN groupadd -r sensetime && useradd -r -g sensetime sensetime
# USER sensetime
