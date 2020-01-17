# syntax = docker/dockerfile:1.0-experimental

FROM nvidia/cuda:10.0-devel-ubuntu18.04 as base-nv

ENV CUDNN_VERSION 7.5.0.56
ENV TENSORRT_VERSION 5.1.5
LABEL com.nvidia.cudnn.version="${CUDNN_VERSION}"

# install system packages
RUN apt-get -y update && apt-get -y install \
    tmux vim ssh openssh-server chrony \
    cmake wget curl unzip \
    lsb-release lsb-core \
    libboost-all-dev libavcodec-dev libavformat-dev libavutil-dev libswscale-dev libnetpbm10-dev \
    ffmpeg v4l2loopback-utils v4l-utils libeigen3-dev libuvc-dev \
    udev iputils-ping pkg-config locales-all dbus-x11 \
    usbutils libusb-1.0-0 libusb-1.0-0-dev libusb-dev \
    libcudnn7=$CUDNN_VERSION-1+cuda10.0 \
    && apt-mark hold libcudnn7 \
    && rm -rf /var/lib/apt/lists/*

# install tensorrt
RUN wget https://developer.download.nvidia.com/compute/cuda/repos/ubuntu1804/x86_64/cuda-repo-ubuntu1804_10.0.130-1_amd64.deb \
    && dpkg -i --force-confold cuda-repo-*.deb \
    && rm cuda-repo-ubuntu1804_10.0.130-1_amd64.deb
RUN apt-get update && apt-get -y install \
    libnvinfer5=$TENSORRT_VERSION-1+cuda10.0 \
    && rm -rf /var/lib/apt/lists/* /root/tensorrt

FROM base-nv as base-cv

# install opencv dependencies
RUN apt-get -y update && apt-get -y install \
    libjpeg-dev libtiff-dev libpng-dev \
    libgtk-3-dev qt5-default \
    libswscale-dev libavcodec-dev libavformat-dev \
    libxvidcore-dev libx264-dev libv4l-dev \
    libtbb2 libtbb-dev libhdf5-dev \
    libatlas-base-dev gfortran libblas-dev liblapack-dev \
    software-properties-common \
    && add-apt-repository "deb http://security.ubuntu.com/ubuntu xenial-security main" \
    && apt-get -y install libjasper1 libjasper-dev \
    && rm -rf /var/lib/apt/lists/*

# download and build opencv
ARG OPENCV_VERSION=3.4.7
RUN cd /root \
    && wget -O opencv.zip https://github.com/opencv/opencv/archive/$OPENCV_VERSION.zip \
    && wget -O opencv_contrib.zip https://github.com/opencv/opencv_contrib/archive/$OPENCV_VERSION.zip \
    && unzip opencv.zip \
    && unzip opencv_contrib.zip \
    && rm opencv.zip opencv_contrib.zip \
    && mkdir /root/opencv-$OPENCV_VERSION/build \
    && cd /root/opencv-$OPENCV_VERSION/build \
    && cmake \
        -D CMAKE_BUILD_TYPE=RELEASE -D CMAKE_INSTALL_PREFIX=/usr/local \
        -D ENABLE_PRECOMPILED_HEADERS=OFF \
        -D OPENCV_EXTRA_MODULES_PATH=/root/opencv_contrib-$OPENCV_VERSION/modules \
        -D WITH_TBB=ON -D WITH_V4L=ON -D WITH_QT=ON \   
        -D WITH_CUDA=ON -D CUDA_FAST_MATH=1  -D WITH_CUBLAS=1 -D CUDA_NVCC_FLAGS="-D_FORCE_INLINES" \
        -D WITH_OPENGL=ON -D ENABLE_FAST_MATH=1 .. \
    ## Add variable to enable make to use all cores
    && make -j$(nproc --all) install \
    ## Remove following lines if you need to move OpenCV
    && rm -rf /root/opencv-$OPENCV_VERSION /root/opencv_contrib-$OPENCV_VERSION


FROM base-cv as base-ros

# add ros melodic and robot control dependencies
ARG DEBIAN_FRONTEND=noninteractive
RUN sh -c 'echo "deb http://packages.ros.org/ros/ubuntu $(lsb_release -sc) main" > /etc/apt/sources.list.d/ros-latest.list'
RUN apt-key adv --keyserver 'hkp://keyserver.ubuntu.com:80' --recv-key C1CF6E31E6BADE8868B172B4F42ED6FBAB17C654
RUN apt-get update && apt-get install -y \
    ros-melodic-ros-base \
    ros-melodic-libuvc-camera \
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
    ros-melodic-interactive-markers \
    ros-melodic-grid-map-msgs \
    ros-melodic-serial \
    ros-melodic-grid-map-loader \
    ros-melodic-laser-geometry \
    ros-melodic-costmap-converter \
    ros-melodic-mbf-msgs \
    ros-melodic-map-server \
    ros-melodic-mbf-costmap-core \
    ros-melodic-nmea-msgs \
    ros-melodic-tf2-eigen \
    ros-melodic-grid-map-ros \
    ros-melodic-grid-map-costmap-2d \
    ros-melodic-angles \
    ros-melodic-libg2o \
    ros-melodic-grid-map-filters \
    ros-melodic-tf2-geometry-msgs \
    ros-melodic-tf2-sensor-msgs \
    ros-melodic-grid-map-cv \
    ros-melodic-grid-map-core \
    ros-melodic-geographic-msgs \
    ros-melodic-eigen-conversions \
    ros-melodic-roslint \
    ros-melodic-rviz \
    && rm -rf /var/lib/apt/lists/* \
    && echo 'source /opt/ros/melodic/setup.bash' >> ~/.bashrc 

FROM base-ros as base-robot

# nvidia-container-runtime
ENV NVIDIA_VISIBLE_DEVICES \
    ${NVIDIA_VISIBLE_DEVICES:-all}
ENV NVIDIA_DRIVER_CAPABILITIES \
    ${NVIDIA_DRIVER_CAPABILITIES:+$NVIDIA_DRIVER_CAPABILITIES,}graphics

# install gtest & gflags
RUN apt-get update && apt-get install -y \
    libgtest-dev libgflags-dev \
    && mkdir /tmp/gtest_build && cd /tmp/gtest_build \
    && cmake /usr/src/gtest && make \
    && cp *.a /usr/lib \
    && rm -rf /var/lib/apt/lists/*

## install pip and utilities
RUN apt-get update && apt-get install -y \
    python-pip python-dev python3-pip python-numpy \
    python-catkin-tools python-catkin-pkg python-rosinstall python-matplotlib \
    && pip install numpy scipy \
    && pip3 install conan \
    && rm -rf /var/lib/apt/lists/*

## install utilities for robot
RUN apt-get update && apt-get install -y --no-install-recommends \
    libnetpbm10-dev \
    libyaml-cpp-dev \
    libboost-all-dev \
    libavcodec-dev \
    libavformat-dev \
    libavutil-dev \
    libswscale-dev \
    librosbag-dev \
    librospack-dev \
    gimp \
    && rm -rf /var/lib/apt/lists/* \
    && rosdep init

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

RUN echo "source /root/gophield/ros_ws/devel/setup.bash" >> ~/.bashrc \
    && echo "export LD_LIBRARY_PATH=\$LD_LIBRARY_PATH:/root/gophield/ros_ws/src/perception/install/aarch64/lib:/root/gophield/ros_ws/src/perception/install/x86_64/lib" >> ~/.bashrc


### Docker Experimental
RUN --mount=type=bind,source=./ros_ws/src/camera_driver/MYNT-EYE-D-SDK,destination=/tmp/MYNT-EYE-D-SDK \
    mkdir -p /root/gophield/ros_ws/src/camera_driver/ && \
    cp -R /tmp/MYNT-EYE-D-SDK /root/gophield/ros_ws/src/camera_driver/MYNT-EYE-D-SDK && \
    cd /root/gophield/ros_ws/src/camera_driver/MYNT-EYE-D-SDK && \
    make install && make ros && rm -rf /root/gophield/ros_ws/src/camera_driver/MYNT-EYE-D-SDK
#FROM base-robot as tmp-build
#COPY ./ros_ws/src/camera_driver/MYNT-EYE-D-SDK /tmp-build/MYNT-EYE-D-SDK
#RUN cd /tmp-build/MYNT-EYE-D-SDK && make install && make ros
#
#FROM base-robot as base-robot-with-build-lib
#COPY --from=tmp-build /usr/local/include/ /usr/local/include/
#COPY --from=tmp-build /usr/local/lib/ /usr/local/lib/
