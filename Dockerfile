FROM archlinux:latest

RUN pacman --noconfirm -Syyy gcc cmake ninja

COPY . /PP

ENTRYPOINT ["/PP/docker.sh"]
