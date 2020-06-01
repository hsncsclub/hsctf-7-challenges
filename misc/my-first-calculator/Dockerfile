FROM ubuntu:18.04

RUN apt-get update && apt-get install -y \
    python \
    xinetd \
 && rm -rf /var/lib/apt/lists/*

COPY ctf.xinetd /etc/xinetd.d/ctf

COPY calculator.py flag.txt /

CMD ["xinetd", "-dontfork"]

EXPOSE 9999
