#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include <event2/event-config.h>
#include <event2/event.h>
#include <event2/dns.h>
#include <event2/dns_struct.h>
#include <event2/util.h>

#define DNS_PORT 53

static int cpuNum()
{
  //char buf[4];
  //snprintf(buf, 4, "%ld", sysconf(_SC_NPROCESSORS_ONLN));
  return (int) sysconf(_SC_NPROCESSORS_ONLN);
  //return atoi(buf);
}

static void evdns_server_callback(struct evdns_server_request *req, void *data)
{
  printf("Get DNS query\n");
  return;
}

void proxyService()
{
  struct event_base *event_base = NULL;
  //struct evdns_base *evdns_base = NULL;
  event_base = event_base_new();
  //evdns_base = evdns_base_new(event_base, 0);
  evutil_socket_t sock;
  struct sockaddr_in my_addr;
  sock = socket(PF_INET, SOCK_DGRAM, 0);
  if(sock == -1) {
    printf("socket create error\n");
    return;
  }
  evutil_make_socket_nonblocking(sock);
  my_addr.sin_family = AF_INET;
  my_addr.sin_port = htons(53);
  my_addr.sin_addr.s_addr = INADDR_ANY;
  if(bind(sock, (struct sockaddr*)&my_addr, sizeof(my_addr))<0) {
    printf("bind error\n");
    return;
  }
  evdns_add_server_port_with_base(event_base, sock, 0, evdns_server_callback, NULL);
  event_base_dispatch(event_base);
}

int main(int argc, char **argv)
{
  printf("DNS proxy server starting...\n");
  printf("Number of CPU %d\n", cpuNum());
  proxyService();
  return 0;
}
