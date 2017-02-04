#ifndef FT_STREAM_NODE_H
#define FT_STREAM_NODE_H
#include <sys/types.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <QtNetwork/QtNetwork>
#include <QtCore/QtCore>



#define PORT 49152 /* Port the Net F/T always uses */
#define COMMAND 2 /* Command code 2 starts streaming */
#define NUM_SAMPLES 1 /* Will send 1 sample before stopping */

class myFT:public QObject
{
    Q_OBJECT
public:
    explicit myFT(QObject *parent = 0);
    typedef unsigned int uint32;
    typedef int int32;
    typedef unsigned short uint16;
    typedef short int16;
    typedef struct response_struct {
        uint32 rdt_sequence;
        uint32 ft_sequence;
        uint32 status;
        int32 FTData[6];
    } RESPONSE;
    ~myFT();

    void publish();
    template<typename T>QByteArray IntToArray(T source);
    int32 ArrayToInt_int32(QByteArray source);
    uint32 ArrayToInt_uint32(QByteArray source);

    QUdpSocket *client;			/* Handle to UDP socket used to communicate with Net F/T. */
    RESPONSE resp;				/* The structured response received from the Net F/T. */
    //byte2 response[36];			/* The raw response data received from the Net F/T. */
    int i;						/* Generic loop/array index. */
    int err;					/* Error status of operations. */
    //char * AXES[];	/* The names of the force and torque axes. */
    int32 FTdata_cal[6];
    //int32 FTdata_pub[6];
    QByteArray ba_request;
    QByteArray ba_response;


};

#endif // FT

