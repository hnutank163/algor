#include <stdio.h>
#include <stdlib.h>
#include <uv.h>

uv_loop_t *loop;

void alloc_buffer(uv_handle_t *handle, size_t suggested_size, uv_buf_t *buf)
{
    buf->base = (char *)malloc(sizeof(char)*suggested_size);
    buf->len = suggested_size;
}

void echo_write(uv_write_t *req, int status)
{
    if(status<0)
        fprintf(stderr, "write error %s\n", uv_strerror(status));
    free(req);
}

void echo_read(uv_stream_t *client, int nread, const uv_buf_t *buf){
    if(nread < 0)
    {
        if(nread != UV_EOF)
            fprintf(stderr, "read error %s\n", uv_strerror(nread));
        else
            fprintf(stdout, "client terminal\n");
        uv_close((uv_handle_t*)client, NULL);
    }
    else if(nread>0)
    {
        uv_write_t *req = (uv_write_t*) malloc(sizeof(uv_write_t));
        uv_buf_t wbuf = uv_buf_init(buf->base, nread);
        uv_write(req, client, &wbuf, 1, echo_write);
    }

}

void new_connection(uv_stream_t *server, int status){
    if(status < 0)
    {
        fprintf(stderr, "new connection error %s\n", uv_strerror(status));
        return;
    }

    uv_tcp_t *client = (uv_tcp_t *) malloc(sizeof(uv_tcp_t));
    uv_tcp_init(loop, client);
    if( uv_accept(server, (uv_stream_t*)client) == 0)
        uv_read_start( (uv_stream_t*)client, alloc_buffer, echo_read);
    else
    {
        uv_close((uv_handle_t *)client,NULL);
    }
}

int main()
{
    struct sockaddr_in addr;
    loop = uv_default_loop();
    uv_tcp_t server;
    uv_tcp_init(loop,&server);
    uv_ip4_addr("192.168.100.231", 8181, &addr);
    uv_tcp_bind(&server, (const struct sockaddr*)&addr,0);
    int ret = uv_listen((uv_stream_t*)&server, 5, new_connection);
    if(ret<0)
    {
        fprintf(stderr, "listen error: %s\n", uv_strerror(ret));
    }

    uv_run(loop, UV_RUN_DEFAULT);
}
