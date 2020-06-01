FROM tiangolo/uwsgi-nginx-flask:python3.8-alpine

RUN apk add --update --no-cache gcc musl-dev git libressl-dev libffi-dev

RUN pip install --upgrade pip
COPY requirements.txt /
RUN pip install --requirement /requirements.txt

COPY ./app /app

ENV LISTEN_PORT=8000
ENV FLAG='flag{1n53cur3_tok3n5_5474212}'
ENV PASSWORD='INzq`JlcH,IA`oH"@/NOGwyQJI+I|uw^'
EXPOSE 8000
