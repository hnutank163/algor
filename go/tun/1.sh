ip tuntap add tun0 mode tun
ifconfig tun0 6.6.6.6 netmask 255.255.255.0
ifconfig tun0 up
ip route add 10.10.10.0/24 via 6.6.6.6
./main
