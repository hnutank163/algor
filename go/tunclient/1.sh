ip tuntap add tunclient mode tun
ifconfig tunclient 11.11.11.11 netmask 255.255.255.0
ifconfig tunclient up
ip route add 20.20.20.0/24 via 11.11.11.11
ip route add 223.6.6.6 via 11.11.11.11

./main
