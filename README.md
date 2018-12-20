# maxconn
Testing the maximum number of TCP connections

2018.12.19
При запуске "./client/launcher03 400" четыреста соединений на один сервер server2 с форками без select
в /var/log/messages появляется:
kernel: sonewconn: pcb 0xfffff80168dc6000: Listen queue overflow: 193 already in queue awaiting acceptance (544 occurrences)
клиенты выдают ошибку "connect error: Connection reset by peer"
Быстрое решение для FreeBSD - увеличить kern.ipc.somaxconn
sysctl kern.ipc.somaxconn     # посмотреть
sysctl kern.ipc.somaxconn=512 # изменить
netstat -Lan

