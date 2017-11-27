#include "ids.h"
#include <pthread.h>

using namespace std;

void *mainProcess(void *arg){
    char *device;
    device = (char *)arg;
    Ids ids;
    ids.setup(device);
}

void *sqlProcess(void *){
    Sql sql;
    bool state;
    state = sql.connect();
    if (state == false){
      sql.connect();
    }
    sql.insertData();
    sql.addData();
    sql.selectData();
}

void *socketProcess(void *){
    Socket socket;
    socket.getData();
    socket.startSock();
}

void *intervalProcess(void *){
    Ids ids;
    while(1){
      sleep(1);
      cout << "Interval test : " << ids.freqUp() << endl;
    }
}

int main(int argc, char *argv[]){
    //checking arguments
    if (argc < 2){
      cout << "Missing argument" << endl;
      cout << "Usage : interface" << endl;
      exit(1);
    }
    else if (argc > 2) {
      cout << "Too many argument given" << endl;
      cout << "This might cause program fail. Exiting..." << endl;
      exit(1);
    }
    //Creating threads
    pthread_t loopThread, sqlThread, sockThread, intervalThread;
    const char *dev = argv[1];
    int loop, sql, sock, interval;
    loop = pthread_create(&loopThread, NULL, mainProcess, (void *)dev);
    if (loop){
      cout << "Error unable to create thread : " << loop << endl;
      exit(1);
    }
    sql = pthread_create(&sqlThread, NULL, sqlProcess, NULL);
    if (sql){
      cout << "Error unable to create thread : " << sql << endl;
      exit(1);
    }
    sock = pthread_create(&sockThread, NULL, socketProcess, NULL);
    if (sock){
      cout << "Error unable to create thread : " << sock << endl;
      exit(1);
    }
    interval = pthread_create(&intervalThread, NULL, intervalProcess, NULL);
    if (interval){
      cout << "Error unable to create thread :" << interval << endl;
      exit(1);
    }
    pthread_join(loopThread, NULL);
    pthread_join(sqlThread, NULL);
    pthread_join(sockThread, NULL);
    pthread_join(intervalThread, NULL);
}
