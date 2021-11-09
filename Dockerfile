FROM archlinux:latest

ARG PACKAGES

RUN pacman --noconfirm -Syyy
RUN pacman --noconfirm -S git
RUN pacman --noconfirm -S $PACKAGES
