FROM trafex/alpine-nginx-php7:latest

USER root
RUN apk add --no-cache php7-simplexml
USER nobody

COPY --chown=nobody src/ /var/www/html

EXPOSE 8080
