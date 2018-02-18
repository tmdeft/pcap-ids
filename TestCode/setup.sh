#!/bin/bash
printf "Required dependencies:\nG++\nMySql\nPHP\nApache\nLibPcap\nLpthread\nMySql-connector-c++\nComposer\n"
printf "**********\nChecking dependencies...\n"
state=1
if command -v g++ >/dev/null 2>&1 ; then
    echo "g++ found"
else
    echo "g++ not found!"
    state=0
fi
if command -v mysql >/dev/null 2>&1 ; then
    echo "MySql found"
else
    echo "MySql not found!"
    state=0
fi
if command -v php >/dev/null 2>&1 ; then
    echo "PHP Found"
else
    echo "PHP not found!"
    state=0
fi
if command ldconfig -p |grep libpcap >/dev/null 2>&1 ; then
    echo "LibPcap found"
else
    echo "Libpcap not found!"
    state=0
fi
if command ldconfig -p |grep libmysqlcppconn >/dev/null 2>&1 ; then
    echo "MySql-connector-c++ found"
else
    echo "MySql-connector-c++ not found!"
    state=0
fi
if command ldconfig -p |grep libpthread >/dev/null 2>&1 ; then
    echo "Lpthread found"
else
    echo "Lpthread not found!"
    state=0
fi
if command httpd -v >/dev/null 2>&1 ; then
    echo "Apache found"
else
    echo "Apache not found!"
    state=0
fi
if command composer -V >/dev/null 2>&1 ; then
    echo "Composer found"
else
    echo "Composer not found"
    state=0
fi
if [ "$state" = "1" ] ; then
    echo "All dependencies are installed"
else
    echo "Missing dependency... exiting."
    exit 1
fi
printf "\n**********\nCompiling..."
cd TestCode
g++ -c main.cpp sql.cpp socketData.cpp process_packet.cpp
wait $!
g++ -o ~/Documents/test main.o sql.o socketData.o process_packet.o -lpcap -lpthread -lmysqlcppconn
wait $!
printf "Done\n*Please make sure MySql user is 'ids' and password is 'QWEasd'*\n*Report any bug to j.in12d067@gmail.com*\n"
cd ../WebService
printf "Installing Laravel dependencies\n"
composer install
wait $!
cp env .env
php artisan key:generate
wait $!
php artisan cache:clear
php artisan migrate
wait $!
php artisan serve
