#include <iostream>
#include <vector>
#include <string>
#include <pqxx/pqxx>
#include <boost/thread/locks.hpp>
#include <boost/thread/mutex.hpp>
#include "ThreadPool.hpp"

#include <errno.h>
#include <error.h>

#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>

#include <sys/epoll.h>

struct connection{
    pqxx::connection conn;
    bool is_using;
    connection(std::string conn_str):conn(conn_str){
        is_using = false;
    }
};

void setnonblocking(int fd){
    int ret = 0;
    if( (ret=fcntl(fd,F_GETFL)) == -1){
        perror("fcntl get");
    }
    ret = ret|O_NONBLOCK;
    if( -1== (ret=fcntl(fd,F_SETFL,ret)))
        perror("fcntl set");
}

class ConnectionPool{
private:
    std::vector<connection *> pool;
    int max_size;
    std::string opt;
    boost::mutex mutex;
public:
    ConnectionPool(int _size=10 ,const std::string _opt=std::string("")):max_size(_size),
    opt(_opt){
        for(int i=0; i<max_size; ++i)
        {
            pool.push_back(new connection(opt));
        }
    }

    connection * getConnection(){
        boost::unique_lock<boost::mutex> lock(mutex);
        for(int i=0; i<max_size; ++i){
            if( !pool[i]->is_using)
            {
                if(pool[i]->conn.is_open())
                {
                    pool[i]->is_using = true;
                    return pool[i];
                }
            }
        }

        connection *pconn = new connection(opt);
        pconn->is_using = true;
        bool invalid = false;
        for(int i=0; i<max_size; ++i){
            if(pool[i]->is_using==false && pool[i]->conn.is_open()==false){
                connection *pold = pool[i];
                pool[i] = pconn;
                invalid = true;
                delete pold;
            }
        }

        if(!invalid){
            pool.push_back(pconn);
        }
        return pconn;
    }

    void releaseConnection(connection *pconn){
        boost::unique_lock< boost::mutex> lock(mutex);
        pconn->is_using = false;
    }
};

class server{
private:
    short port;
    int     server_fd;
public:
    server(short port=1111):port(port){}
    void start(){
        try{
            server_fd = socket(AF_INET, SOCK_STREAM, 0);
            int reuse = 1;
            setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, (const void *)&reuse,sizeof(int));
            struct sockaddr_in addr;
            addr.sin_family = AF_INET;
            addr.sin_port = htons(port);
            inet_pton(AF_INET,"0.0.0.0", &addr.sin_addr );
            if( 0!=bind(server_fd, (struct sockaddr *)&addr, sizeof(addr)))
            {
               perror("bind") ;
               exit(1);
            }

            if(0!=listen(server_fd, 5)){
                perror("listen");
                exit(1);
            }

            int max_events = 1024;
           int epfd = epoll_create(max_events);
           epoll_event ev, events[max_events];
           ev.data.fd = server_fd;
           ev.events = EPOLLIN;
           epoll_ctl(epfd, EPOLL_CTL_ADD, server_fd, &ev);

           while(true){
               int nfds = epoll_wait(epfd, events, max_events, -1);
                for(int i=0 ;i<nfds; ++i)
                {
                    int fd = events[i].data.fd;
                    if(fd == server_fd){
                        int connfd;
                        struct sockaddr_in client_addr;
                        socklen_t len = sizeof(client_addr);
                        while( (connfd=accept(server_fd,(struct sockaddr *)&client_addr,&len))>0)
                        {
                            ev.data.fd = connfd;
                            ev.events = EPOLLIN|EPOLLET;
                            setnonblocking(connfd);
                            epoll_ctl(epfd, EPOLL_CTL_ADD, connfd, &ev);
                        }
                    }
                    else if( events[i].events & EPOLLIN){
                        char buf[256] = {0};
                        int error = 0;
                        while(true){
                            int ret = recv(fd,buf,256,0);
                            if(ret==0){
                                error=1;
                                break;
                            }if(ret == -1){
                                if(errno != EAGAIN)
                                    error = 1;
                                break;
                            }
                        }
                        if(error){
                            close(fd);
                            epoll_ctl(epfd,EPOLL_CTL_DEL, fd, &ev);
                        }
                    }
                }
           }
        }
        catch(const std::exception &e){
            std::cout<<e.what()<<std::endl;
        }
    }
};

int main(){
    try{
        std::string str("dbname=postgres user=postgres password=123456 \
      hostaddr=192.168.100.38 port=5432");
    }
    catch(const std::exception &e){
        std::cout<<e.what()<<std::endl;
    }
    return 0;
}
