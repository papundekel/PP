FROM archlinux:latest

COPY . /PP

ENTRYPOINT ["/PP/entrypoint.sh"]
