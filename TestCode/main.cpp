#include "ids.h"
#include <pthread.h>
#include <string>

using namespace std;

//Packet processing function for thread
void *mainProcess(void *arg){
    char *device;
    device = (char *)arg;
    Ids ids;
    ids.setup(device);
}

//Connection to sql database function for thread
void *sqlProcess(void *){
    Sql sql;
    bool state;
    state = sql.connect();
    if (state == false){
      sql.connect();
    }
}

//Socket creation function for thread
void *socketProcess(void *){
    Socket socket;
    socket.getData();
    socket.startSock();
}

//Getting interface by interval
void *intervalProcess(void *){
    Ids ids;
    Sql sql;
    unsigned int port = 0;
    string ipAddress = "";
    string macAddress = "";
    string currentAttacker = "";
    unsigned int cnt = 0;
    while(1){
      sleep(1);
      if(ids.freqUp() > 200){
          port = ids.getPort();
          ipAddress = ids.getIp();
          macAddress = ids.getMac();
          cout << "before if : " << ipAddress << endl;
          if(ipAddress != "Not yet"){
            if (cnt == 0){
                cout << "test ip : " << ipAddress << endl;
                currentAttacker = ipAddress;
                //strcpy(currentAttacker, testpointer);
                cnt ++;
                cout << "cnt=0 IP : " << currentAttacker << endl;
                sql.insertData(ipAddress, macAddress, port);
            }
            else if (cnt > 0){
                if(currentAttacker == ipAddress){
                    cout << "Same attacker with : " << currentAttacker << endl;
                }
                else {
                    sql.insertData(ipAddress, macAddress, port);
                    cout << "New attacker with : " << ipAddress << endl;
                    cout << "Current attacker with : " << currentAttacker << endl;
                }
                cnt ++;
            }
          }
      }
    }
}

//main function
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
    //starting threads
    pthread_join(loopThread, NULL);
    pthread_join(sqlThread, NULL);
    pthread_join(sockThread, NULL);
    pthread_join(intervalThread, NULL);
}
