#include "ids.h"
#include <pthread.h>

using namespace std;
bool dbState = false;

void *mainProcess(void* ptr){
    char *dev;
    dev = (char *)ptr;
    MainProcess mp;
    mp.setup(dev);
}

void *socketProcess(void *){
    SocketData sd;
    sd.setSocket();
}

void *sqlProcess(void *){
    Database db;
    dbState = db.connect();
    if (dbState == false)
      dbState = db.connect();
}

void *updateProcess(void *){
    string ipAddress;
    unsigned int port = 0;
    string macAddress;
    MainProcess mp;
    Database db;
    while(1){
        sleep(1);
        if(mp.freqUp() > 300){
            db.insert();
            mp.setCounter();
        }
    }
}

int main(int argc, char *argv[]){
    if(argc < 2){
        cout << "Missing argument!\nUsage: <interface>" << endl;
        exit(EXIT_FAILURE);
    }
    else if (argc > 2){
        cout << "Too many arguments given...\nExiting..." << endl;
        exit(EXIT_FAILURE);
    }
    const char *interface = argv[1];
    //Creating threads;
    pthread_t mainThread, socketThread, sqlThread, updateThread;
    int mt, sockt, sqlt, upt;
    mt = pthread_create(&mainThread, NULL, mainProcess, (void *)interface);
    if(mt){
        cout << "Error - creating main thread, return code : " << mt << endl;
        exit(EXIT_FAILURE);
    }
    sockt = pthread_create(&socketThread, NULL, socketProcess, NULL);
    if(sockt){
        cout << "Error - creating socket thread, return code : " << sockt << endl;
        exit(EXIT_FAILURE);
    }
    sqlt = pthread_create(&sqlThread, NULL, sqlProcess, NULL);
    if(sqlt){
        cout << "Error - creating sql thread, return code : " << sqlt << endl;
        exit(EXIT_FAILURE);
    }
    upt = pthread_create(&updateThread, NULL, updateProcess, NULL);
    if(upt){
        cout << "Error - creating update thread, return code : " << upt << endl;
        exit(EXIT_FAILURE);
    }
    pthread_join(mainThread, NULL);
    pthread_join(socketThread, NULL);
    pthread_join(sqlThread, NULL);
    while(1){
        sleep(1);
        cout << "Testing" << endl;
    }
    return 0;
}
