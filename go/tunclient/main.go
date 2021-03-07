package main

import (
	"log"
	"net"

	"github.com/songgao/water"
	"golang.org/x/net/ipv4"
)

type Client struct {
	conn     net.Conn
	inStream chan []byte
}

var queue = make(chan []byte, 10000)

func newClient(addr string) *Client {
	tcpAddr, _ := net.ResolveTCPAddr("tcp", "192.168.31.178:12345")
	conn, err := net.DialTCP("tcp", nil, tcpAddr)
	if err != nil {
		log.Panic(err)
	}

	// handshake
	conn.Write([]byte(addr))
	buf := make([]byte, 256)
	n, _ := conn.Read(buf)
	if string(buf[:n]) != "OK" {
		log.Printf("handshake failed, %v", string(buf[:n]))
	}

	return &Client{
		conn:     conn,
		inStream: make(chan []byte, 1024),
	}
}

var clients map[string]*Client

func main() {
	clients := make(map[string]*Client)
	conf := water.Config{
		DeviceType: water.TUN,
	}
	conf.Name = "tunclient"

	ifce, err := water.New(conf)
	if err != nil {
		log.Panic(err)
	}

	go func() {
		for {
			buf := <-queue
			ifce.Write(buf)
		}
	}()

	for {
		buf := make([]byte, 1024)
		n, err := ifce.Read(buf)
		if err != nil {
			log.Panic(err)
		}

		ipver := buf[0] >> 4
		log.Printf("ipver is %v", ipver)
		if ipver != 4 {
			continue
		}

		header, _ := ipv4.ParseHeader(buf[:n])
		client, ok := clients[header.Src.String()]
		if !ok {
			log.Printf("can't find client, new")
			client = newClient(header.Src.String())
			clients[header.Src.String()] = client

			go func(client *Client) {

				go func() {
					for {
						buf := <-client.inStream
						client.conn.Write(buf)
					}
				}()

				for {
					buf := make([]byte, 1500)
					n, err := client.conn.Read(buf)
					if err != nil {
						log.Printf("read from tun proxy failed, ", err)
						break
					}

					select {
					case queue <- buf[:n]:
					default:
						log.Printf("write to tun failed")
					}
				}
			}(client)
		}

		log.Printf("write to client %v", buf[:n])
		select {
		case client.inStream <- buf[:n]:
		default:
			log.Printf("write to client queue failed")
		}
	}
}
