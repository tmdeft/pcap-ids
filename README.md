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
MySQL with database configured
Apache server with PHP 7.0 support
```

### Installing

A step by step series of examples that tell you have to get a development env running

Say what the step will be

```
Git clone project. Run make file. After installation complete start the service using systemctl start ids-pcap or service ids-pcap start
```

And repeat

```
until finished
```

End with an example of getting some data out of the system or using it for a little demo

## Running the tests

Explain how to run the automated tests for this system

### Break down into end to end tests

Explain what these tests test and why

```
Give an example
```

### And coding style tests

Explain what these tests test and why

```
Give an example
```

## Deployment

Add additional notes about how to deploy this on a live system

## Built With

* [Laravel](https://laravel.com/) - The web framework used
* [Libpcap](http://www.tcpdump.org/) - Library for live packet capture
* [MySQL](https://www.mysql.com/) - Database management

## Contributing

Please read [CONTRIBUTING.md](https://gist.github.com/PurpleBooth/b24679402957c63ec426) for details on our code of conduct, and the process for submitting pull requests to us.

## Versioning

We use [SemVer](http://semver.org/) for versioning. For the versions available, see the [tags on this repository](https://github.com/your/project/tags). 

## Authors

* **Naiame Nel'theri** - *Initial work*

## License

This project is licensed under the MIT License - see the [LICENSE.md](LICENSE.md) file for details

## Acknowledgments

* Thanks to binarytides which gave me perfect example for extracting packets with libpcap
