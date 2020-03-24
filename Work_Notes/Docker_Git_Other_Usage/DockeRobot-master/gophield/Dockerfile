FROM nvidia/cuda:10.0-devel-ubuntu18.04 as develop

ENV CUDNN_VERSION 7.5.0.56
LABEL com.nvidia.cudnn.version="${CUDNN_VERSION}"

# install system packages
RUN apt-get -y update && apt-get -y install \
    tmux vim \
    cmake wget curl unzip \
    lsb-release lsb-core \
    ffmpeg v4l2loopback-utils \
    udev iputils-ping pkg-config locales-all dbus-x11 \
    usbutils libusb-1.0-0 libusb-1.0-0-dev \
    libcudnn7=$CUDNN_VERSION-1+cuda10.0 \
    && apt-mark hold libcudnn7 \
    && rm -rf /var/lib/apt/lists/*

# install tensorrt
RUN wget https://developer.download.nvidia.com/compute/cuda/repos/ubuntu1804/x86_64/cuda-repo-ubuntu1804_10.0.130-1_amd64.deb \
    && dpkg -i --force-confold cuda-repo-*.deb 
RUN apt-get update && apt-get -y install \
    libnvinfer4 \
    && rm -rf /var/lib/apt/lists/* /root/tensorrt

FROM develop as develop-ros

# add ros melodic and robot control dependencies
ARG DEBIAN_FRONTEND=noninteractive
RUN sh -c 'echo "deb http://packages.ros.org/ros/ubuntu $(lsb_release -sc) main" > /etc/apt/sources.list.d/ros-latest.list'
RUN apt-key adv --keyserver 'hkp://keyserver.ubuntu.com:80' --recv-key C1CF6E31E6BADE8868B172B4F42ED6FBAB17C654
RUN apt-get update && apt-get install -y \
    ros-melodic-ros-base \
    libuvc-dev ros-melodic-libuvc-camera \
    ros-melodic-cv-bridge \
    ros-melodic-rqt ros-melodic-rqt-image-view \
    ros-melodic-image-transport-plugins \
    ros-melodic-diagnostic-updater \
    ros-melodic-tf \
    ros-melodic-xacro \
    ros-melodic-urdf \
    ros-melodic-joint-state-publisher \
    ros-melodic-robot-state-publisher \
    ros-melodic-image-view \
    ros-melodic-rqt-common-plugins \
    && rm -rf /var/lib/apt/lists/*

FROM develop-ros as develop-robot

# install gtest
RUN apt-get update && apt-get install -y \
    libgtest-dev \
    && mkdir /tmp/gtest_build && cd /tmp/gtest_build \
    && cmake /usr/src/gtest && make \
    && cp *.a /usr/lib

## install pip and utilities
RUN apt-get update && apt-get install -y \
    python-pip python-dev \
    python-catkin-tools python-rosinstall python-matplotlib \
    && curl https://bootstrap.pypa.io/get-pip.py -o get-pip.py \
    && python get-pip.py \
    && pip install numpy scipy

# nvidia-container-runtime
ENV NVIDIA_VISIBLE_DEVICES \
    ${NVIDIA_VISIBLE_DEVICES:-all}
ENV NVIDIA_DRIVER_CAPABILITIES \
    ${NVIDIA_DRIVER_CAPABILITIES:+$NVIDIA_DRIVER_CAPABILITIES,}graphics

# install opencv dependencies
RUN apt-get -y update && apt-get -y install \
    libjpeg-dev libtiff-dev libpng-dev \
    libgtk-3-dev qt5-default \
    libswscale-dev libavcodec-dev libavformat-dev \
    libxvidcore-dev libx264-dev libv4l-dev \
    libtbb2 libtbb-dev libhdf5-dev \
    libatlas-base-dev gfortran libblas-dev liblapack-dev \
    && rm -rf /var/lib/apt/lists/*
RUN apt-get -y update && apt-get -y install \
    software-properties-common \
    && add-apt-repository "deb http://security.ubuntu.com/ubuntu xenial-security main" \
    && apt-get -y install libjasper1 libjasper-dev

# download and build opencv
ARG OPENCV_VERSION=3.4.7
RUN cd /root \
    && wget -O opencv.zip https://github.com/opencv/opencv/archive/$OPENCV_VERSION.zip \
    && wget -O opencv_contrib.zip https://github.com/opencv/opencv_contrib/archive/$OPENCV_VERSION.zip \
    && unzip opencv.zip \
    && unzip opencv_contrib.zip \
    && rm opencv.zip opencv_contrib.zip
RUN mkdir /root/opencv-$OPENCV_VERSION/build \
    && cd /root/opencv-$OPENCV_VERSION/build \
    && cmake \
        -D CMAKE_BUILD_TYPE=RELEASE -D CMAKE_INSTALL_PREFIX=/usr/local \
        -D ENABLE_PRECOMPILED_HEADERS=OFF \
        -D OPENCV_EXTRA_MODULES_PATH=/root/opencv_contrib-$OPENCV_VERSION/modules \
        -D WITH_TBB=ON -D WITH_V4L=ON -D WITH_QT=ON \   
        -D WITH_CUDA=ON -D CUDA_FAST_MATH=1  -D WITH_CUBLAS=1 -D CUDA_NVCC_FLAGS="-D_FORCE_INLINES" \
        -D WITH_OPENGL=ON -D ENABLE_FAST_MATH=1 .. \
    ## Add variable to enable make to use all cores
    && export NUMPROC=$(nproc --all) \
    && make -j$NUMPROC install \
    ## Remove following lines if you need to move openCv
    && rm -r /root/opencv-$OPENCV_VERSION /root/opencv_contrib-$OPENCV_VERSION

FROM develop-robot as develop-robot-opengl

RUN dpkg --add-architecture i386 \
    && apt-get update && apt-get install -y --no-install-recommends \
    libglvnd0 libglvnd0:i386 \
	libgl1 libgl1:i386 \
	libglx0 libglx0:i386 \
	libegl1 libegl1:i386 \
	libgles2 libgles2:i386 \
    && rm -rf /var/lib/apt/lists/*
COPY --from=nvidia/opengl:1.0-glvnd-runtime-ubuntu18.04 \
  /usr/share/glvnd/egl_vendor.d/10_nvidia.json \
  /usr/share/glvnd/egl_vendor.d/10_nvidia.json


FROM develop-robot-opengl as ci-build
LABEL repository=od-automower

