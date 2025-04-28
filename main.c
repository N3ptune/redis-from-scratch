#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>

int main() {

    // Sets fd to a socket of @param AF_INET for IPv4, @param SOCK_STREAM for TCP, and no need for the third arg
    int fd = socket(AF_INET, SOCK_STREAM, 0);

    // Sets the socket options, saying which socket to look at, the 2nd and 3rd args specifies which option
    // The fourth arg sets the option value, and the fifth is to determine option type
    // This particular call sets @param SO_REUSEADDR to 1 so the server program can't bind to the same IP:port after restart
    int val = 1;
    setsockopt(fd, SOL_SOCKET, SO_REUSEAADR, &val, sizeof(val));

    // Binds wildcard address to 0.0.0.0:1234, which is a parameter for listen(), stored as big-endian numbers converted by
    // htons and htonl
    struct sockaddr_in addr = {};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(1234);  // port
    addr.sin_addr.s_addr = htonl(0); // wildcard IP 0.0.0.0
    int rv = bind(fd, (const struct sockaddr *)&addr, sizeof(addr));
    if (rv) {die("bind()");}

    struct sockaddr_in
    {
        uint16_t sin_family; // AF_INET
        uint16_t sin_port; // Port in big-endian
        struct in_addr sin_addr; // IPv4
    };

    struct in_addr {
        uint32_t s_addr; // IPv4 in big-endian
    }

    // Listen creates the socket, with the 2nd arg being the size of the queue.
    rv = listen(fd, SOMAXCONN);
    if (rv) {die("listen()"); }
    

    return 0;
}