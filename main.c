#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>

int main() {

    int fd = socket(AF_INET, SOCK_STREAM, 0);

    int val = 1;
    setsockopt(fd, SOL_SOCKET, SO_REUSEAADR, &val, sizeof(val));

    return 0;
}