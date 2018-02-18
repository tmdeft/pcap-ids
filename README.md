# Intrusion Detection Tool

An Intrusion Detection Tool with packet analyzing function

## Getting Started

This tool is made for education purpose. The tool sniffs the network adapter extracts every packet that passes through by the network adapter. Including packets that doesn't belong to the host device. It reads the data inside packet checks it and if the packet is DoS type packet tool will execute an alarm to the user and writes important data to MySQL database, including IP Address of the suspected attacker, date and time, destination port number etc. Also tool includes ability to extract packet by headers. Writes header data to a file. User can monitor processes such as network flow, amount of packets seperated by protocol using the Web page.

### Prerequisites

Dependencies for PCAP-IDS

```
C++, C compilers
Libpcap
Libmysqlcppconn /MySQL C++ connector/
LibPthread
MySQL with database configured
Apache server with PHP 7.0 support
Composer
```

### Installing

Before installation user must configure MySql manually by creating user named 'ids'@'localhost' with password 'QWEasd'. Also user must configure php.ini file by enabling socket, pdo_mysql extension. After these configuration run setup.sh file

## Built With

* [Laravel](https://laravel.com/) - The web framework used
* [Libpcap](http://www.tcpdump.org/) - Library for live packet capture
* [MySQL](https://www.mysql.com/) - Database management

## Authors

* **Naiame Nel'theri** - *Initial work*

## License

This project is licensed under the MIT License - see the [LICENSE.md](LICENSE.md) file for details

## Acknowledgments

* Thanks to binarytides which gave me perfect example for extracting packets with libpcap
