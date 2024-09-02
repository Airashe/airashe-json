FROM archlinux:latest

# Install packages
USER root
RUN pacman -Sy --noconfirm

## Install python and conan
RUN pacman -S --noconfirm python-pip
RUN pacman -S --noconfirm python-pipx

RUN pipx install conan
RUN pipx install conan_package_tools
RUN pipx ensurepath

# Install gcc and CMake
RUN pacman -S --noconfirm gcc
RUN pacman -S --noconfirm make
RUN pacman -S --noconfirm cmake

# Install perl
RUN pacman -S --noconfirm perl

# Setup
RUN PATH=$PATH:/root/.local/bin
#RUN conan profile detect

# Copy source code
WORKDIR /
RUN mkdir /usr/src/airashe-json
COPY . /usr/src/airashe-json/
RUN rm -rf /usr/src/airashe-json/build

WORKDIR /usr/src/airashe-json

#build and run
RUN PATH=$PATH:/root/.local/bin &&  \
    chmod +x tools/create_package.sh &&  \
    chmod +x tools/create_project.sh &&  \
    tools/create_package.sh \
    #tools/create_project.sh \