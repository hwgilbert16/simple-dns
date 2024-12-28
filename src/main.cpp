#include <sys/socket.h>
#include <netinet/in.h>
#include "iostream"

int main() {
    int fd = socket(AF_INET, SOCK_DGRAM, 0);

    int val = 1;
    setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &val, sizeof(val));

    struct sockaddr_in addr = {};

    addr.sin_family = AF_INET;
    addr.sin_port = ntohs(53);
    addr.sin_addr.s_addr = ntohl(0);

    int rv = bind(fd, (const sockaddr*)&addr, sizeof(addr));
    if (rv) {
        printf("die");
    }

    rv = listen(fd, SOMAXCONN);
    if (rv) {
        printf("die");
    }

    while (true) {
        struct sockaddr_in client_addr = {};
        socklen_t addrlen = sizeof(client_addr);

        int connfd = accept(fd, (struct sockaddr *)&client_addr, &addrlen);
        if (connfd < 0) {
            continue;
        }
    }
}