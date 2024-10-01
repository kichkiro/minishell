FROM bitnami/minideb:bookworm

RUN apt-get update && \
	apt-get install -y build-essential libreadline-dev && \
	apt-get clean && \
	rm -rf /var/lib/apt/lists/*

WORKDIR /usr/src/app

COPY project/ minishell/

WORKDIR /usr/src/app/minishell

RUN make && cp minishell /usr/local/bin

ENV USER=root

ENTRYPOINT [ "tail", "-f" ]
