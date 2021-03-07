package main

import (
	"context"
	"log"
	"net"

	"github.com/songgao/water"
	"golang.org/x/net/ipv4"
)

type Tun struct {
	tun      *water.Interface
	mtu      int
	inStream chan []byte
	clients map[string]*Client
}

func NewTun(name string) *Tun {
	conf := water.Config{
		DeviceType: water.TUN,
	}
	conf.Name = "tun0"

	ifce, err := water.New(conf)
    if err != nil {
        log.Panic(err)
    }

	return &Tun{
		tun:      ifce,
		mtu:      1500,
		inStream: make(chan []byte, 10000),
        clients: make(map[string]*Client),
	}
}

func (tun *Tun) Start() {

    go func() {
        for {
            buf := <- tun.inStream
            // log.Printf("write to tun %v", buf)
            tun.tun.Write(buf)
        }
    }()

    for {
        buf := make([]byte, tun.mtu)
        n, err := tun.tun.Read(buf)
        if err != nil {
            log.Printf("read tun failed, ", err)
        }

        ipver := buf[0] >> 4
        log.Printf("ip version is %v", ipver)
        if ipver != 4 {
            continue
        }

        header, _ := ipv4.ParseHeader(buf[:n])

        log.Printf("recv packet src %v, dst %v", header.Src.String(), header.Dst.String())
        client := tun.clients[header.Dst.String()]
        if client == nil {
            log.Printf("can't find a client to write packet")
            continue
        }
        select {
        case client.inStream <- buf[:n]:
        default:
            log.Printf("write client failed")
        }

    }
}

func (tun *Tun) addClient(addr string, client *Client) {
    tun.clients[addr] = client
}

type Client struct {
	conn     net.Conn
	ctx      context.Context
	tun      *Tun
	inStream chan []byte
}

func NewClient(conn net.Conn, tun *Tun) *Client {
	return &Client{
		conn:     conn,
		tun:      tun,
		inStream: make(chan []byte, 1024),
	}
}

func (c *Client) Pipe() {
	// client -> tun

	go func() {
		for {
			buf := make([]byte, c.tun.mtu)
			n, err := c.conn.Read(buf)
			if err != nil {
				log.Printf("read from client failed, e %v", err)
				break
			}

			// write to tun queue

			select {
			case c.tun.inStream <- buf[:n]:
			    // log.Printf("write packet to tun stream")
			default:
				log.Printf("write to tun queue fail")
			}
		}
	}()

	// tun -> client
	go func() {
		for {
			buf := <-c.inStream
			// write to client
			c.conn.Write(buf)
		}
	}()
}

type TunManager struct {
	tunTable map[int]*Tun
	clients map[string]*Client
}

func (tunManager *TunManager) getTunByAddr(addr string) *Tun {
	return tunManager.tunTable[0]
}

func (tunManager *TunManager) getClientByAddr(addr string) *Client {
    return tunManager.clients[addr]
}

func (tunManager *TunManager) Start() {
    for _, tun := range tunManager.tunTable {
        go tun.Start()
    }
}

func main() {

	tunTable := make(map[int]*Tun)
	tunTable[0] = NewTun("tun0")
	tunManager := &TunManager{
		tunTable: tunTable,
	}


	addr, err := net.ResolveTCPAddr("tcp", "0.0.0.0:12345")
	if err != nil {
		log.Panic(err)
	}

	listner, err := net.ListenTCP("tcp", addr)
	if err != nil {
		log.Panic(err)
	}

    go tunManager.Start()
	for {
		conn, err := listner.Accept()
		if err != nil {
			log.Panic(err)
		}

		go func(conn net.Conn) {
			// handshake
			buf := make([]byte, 256)
			n, _ := conn.Read(buf)
			conn.Write([]byte("OK"))

            tun := tunManager.getTunByAddr(string(buf[:n]))
			client := NewClient(conn, tun)
            tun.addClient(string(buf[:n]), client)
            log.Printf("recv new client %v", client.conn.RemoteAddr())
			client.Pipe()
		}(conn)
	}
}
