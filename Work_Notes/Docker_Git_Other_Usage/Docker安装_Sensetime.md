# Docker: robot-env 使用文档

## Docker简介

- 什么是Docker

  <https://yeasy.gitbooks.io/docker_practice/introduction/what.html>

- 为什么要用docker？

  <https://yeasy.gitbooks.io/docker_practice/introduction/what.html>

## Docker 基本概念

### 镜像

- 文件系统

  >  Docker 镜像是一个特殊的文件系统，除了提供容器运行时所需的程序、库、资源、配置等文件外，还包含了一些为运行时准备的一些配置参数（如匿名卷、环境变量、用户等）。镜像不包含任何动态数据，其内容在构建之后也不会被改变

- 分层存储

  > 严格来说，镜像并非是像一个 ISO 那样的打包文件，镜像只是一个虚拟的概念，其实际体现并非由一个文件组成，而是由一组文件系统组成，或者说，由多层文件系统联合组成
  >
  > 镜像构建时，会一层层构建，前一层是后一层的基础。每一层构建完就不会再发生改变，后一层上的任何改变只发生在自己这一层。比如，删除前一层文件的操作，实际不是真的删除前一层的文件，而是仅在当前层标记为该文件已删除。在最终容器运行的时候，虽然不会看到这个文件，但是实际上该文件会一直跟随镜像。因此，在构建镜像的时候，需要额外小心，每一层尽量只包含该层需要添加的东西，任何额外的东西应该在该层构建结束前清理掉
  >
  > 分层存储的特征还使得镜像的复用、定制变的更为容易。甚至可以用之前构建好的镜像作为基础层，然后进一步添加新的层，以定制自己所需的内容，构建新的镜像

### 容器

- 容器是镜像运行时的实体

  > 镜像（`Image`）和容器（`Container`）的关系，就像是面向对象程序设计中的 `类` 和 `实例` 一样，镜像是静态的定义，容器是镜像运行时的实体。容器可以被创建、启动、停止、删除、暂停等
  >
  > 容器的实质是进程，但与直接在宿主执行的进程不同，容器进程运行于属于自己的独立的命名空间。因此容器可以拥有自己的 `root` 文件系统、自己的网络配置、自己的进程空间，甚至自己的用户 ID 空间。容器内的进程是运行在一个隔离的环境里，使用起来，就好像是在一个独立于宿主的系统下操作一样。这种特性使得容器封装的应用比直接在宿主运行更加安全。也因为这种隔离的特性，很多人初学 Docker 时常常会混淆容器和虚拟机

- 容器存储层

  > 镜像使用的是分层存储，容器也是如此。每一个容器运行时，是以镜像为基础层，在其上创建一个当前容器的存储层，我们可以称这个为容器运行时读写而准备的存储层为容器存储层
  >
  > 容器存储层的生存周期和容器一样，容器消亡时，容器存储层也随之消亡。因此，任何保存于容器存储层的信息都会随容器删除而丢失
  >
  > 按照 Docker 最佳实践的要求，容器不应该向其存储层内写入任何数据，容器存储层要保持无状态化。所有的文件写入操作，都应该使用数据卷（Volume）、或者绑定宿主目录，在这些位置的读写会跳过容器存储层，直接对宿主（或网络存储）发生读写，其性能和稳定性更高
  >
  > 数据卷的生存周期独立于容器，容器消亡，数据卷不会消亡。因此，使用数据卷后，容器删除或者重新运行之后，数据却不会丢失


## 使用Docker所需的依赖

- Ubuntu 

  > Ubuntu 16.04及以上版本在显卡驱动安装的步骤可以更加方便

- NVidia driver

  > 使用从**源**切换NVidia driver可以有效减少显卡驱动安装的步骤和风险（尤其针对新款显卡）

  > 为了兼容docker中高版本的cuda推荐使用**418.xx**或以上版本的显卡驱动（可以兼容低版本的cuda）

  ```shell
  $ sudo add-apt-repository ppa:graphics-drivers/ppa
  $ sudo apt-get purge nvidia*
  $ sudo apt update
  $ sudo apt-get install build-essential
  $ ubuntu-drivers devices
  # install newest driver
  $ sudo ubuntu-drivers autoinstall 
  # Alternatively, install desired driver
  $ sudo apt install nvidia-418 nvidia-settings nvidia-prime
  # Alternatively, use GUI tool to install
  $ sudo software-properties-gtk
  ```

- Docker

  - 安装docker

    ```bash
    $ sudo apt-get update
    $ sudo apt-get install \
        apt-transport-https \
        ca-certificates \
        curl \
        gnupg-agent \
        software-properties-common
    $ curl -fsSL https://mirrors.ustc.edu.cn/docker-ce/linux/ubuntu/gpg | sudo apt-key add -
    $ sudo add-apt-repository \
        "deb [arch=amd64] https://mirrors.ustc.edu.cn/docker-ce/linux/ubuntu \
        $(lsb_release -cs) \
        stable"
    $ sudo apt-get update
    $ sudo apt-get install docker-ce  docker-ce-cli containerd.io
    ```

    另一种方式：自动安装脚本

      ```shell
      $ curl -fsSL get.docker.com -o get-docker.sh
      $ sudo sh get-docker.sh --mirror Aliyun
      ```

  - 启动docker

    ```bash
    $ sudo systemctl enable docker
    $ sudo systemctl start docker
    ```

  - 建立 docker 用户组

      ```shell
      $ sudo groupadd docker
      $ sudo usermod -aG docker $USER
      ```

      > 配置完成这一步之后注销之后重新登录使设置生效

- NVidia-docker

  ```bash
  # If you have nvidia-docker 1.0 installed: we need to remove it and all existing GPU containers
  docker volume ls -q -f driver=nvidia-docker | xargs -r -I{} -n1 docker ps -q -a -f volume={} | xargs -r docker rm -f
  sudo apt-get purge -y nvidia-docker
  
  # Add the package repositories
  curl -s -L https://nvidia.github.io/nvidia-docker/gpgkey | \
    sudo apt-key add -
  
  distribution=$(. /etc/os-release;echo $ID$VERSION_ID)
  
  curl -s -L https://nvidia.github.io/nvidia-docker/$distribution/nvidia-docker.list | \
    sudo tee /etc/apt/sources.list.d/nvidia-docker.list
  
  sudo apt-get update
  
  # Install nvidia-docker2 and reload the Docker daemon configuration
  sudo apt-get install -y nvidia-docker2
  sudo pkill -SIGHUP dockerd
  ```

- 配置docker镜像仓库

  > 对于Ubuntu系统，请在 `/etc/docker/daemon.json` 中写入如下内容（如果文件不存在请新建该文件）
  
    ```json
{
       "registry-mirrors": ["https://docker.mirrors.ustc.edu.cn/"],
       "runtimes": {
           "nvidia": {
               "path": "nvidia-container-runtime",
               "runtimeArgs": []
           }
       }
   }
    ```

  > 注意，一定要保证该文件符合 json 规范，否则 Docker 将不能启动

  > 之后重新启动服务
  
  ```bash
  $ sudo systemctl daemon-reload
  $ sudo systemctl restart docker
  ```
  
  

## 下载Docker镜像

```bash
$ docker login registry.sensetime.com
$ docker pull registry.sensetime.com/robot-env/robot-env:cuda10.0-py2-ubuntu16.04
```

> `registry.sensetime.com/robot-env/robot-env`：镜像名

> `19.02-ros-py2`：镜像tag



## 运行一个robot-env镜像的容器
可直接运行  ./run_docker_image_ros2.sh

也可：
- 创建

  例如使用如下命令创建一个robot-env的容器

  ```bash
   $ docker run -it \                     
      --env="DISPLAY=$DISPLAY" \
      --env="QT_X11_NO_MITSHM=1" \
      --volume="/tmp/.X11-unix:/tmp/.X11-unix:rw" \
      --env="XAUTHORITY=$XAUTH" \
      --volume="$XAUTH:$XAUTH" \
      --runtime=nvidia \
      --volume="/home:/home" \
      registry.sensetime.com/robot-env/robot-env:cuda10.0-py2-ubuntu16.04 \
      bash
  ```

  参数详解

  

- 启动

  ```
docker container start <container id>
  docker container exec -it --user root <container id> /bin/bash
  ```

- 停止

- 删除

  - docker container prune
  - docker container rm

- 导出与导入



## 构建一个新的镜像

示例






## 疑难问题

- 硬件映射
  
- --privilege
  - -v /dev:/dev
  
- IDE

- user权限

  - groupadd -r sensetime && useradd -r -g sensetime sensetime
  - docker container exec -it --user root <container id> /bin/bash
