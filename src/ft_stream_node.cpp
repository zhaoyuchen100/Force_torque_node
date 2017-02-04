//#include <include/ft_node/ft_stream_node.h>
#include <include/ft_node/ft_stream_node.h>
myFT::myFT(QObject *parent) : QObject(parent)
{
    client = new QUdpSocket(this);
    const QString netboxaddr = "192.168.1.1";
    //const QString netboxaddr = "127.0.0.1";
    client->connectToHost(netboxaddr,PORT);
    if (!client->waitForConnected(5000)) {
        qDebug()<<"Connection Error";
        exit(1);
    }
    else
    {
        qDebug()<< "Connected!!";
    }

    ba_request = QByteArray("");
    //ba_request.resize(8);
    for (int i=0;i<3;i++)
    {
        if (i==0){
        ba_request.append(this->IntToArray(static_cast<uint16>(0x1234)));
        }
        if (i==1){
        ba_request.append(this->IntToArray(static_cast<uint16>(COMMAND)));
        }
        if (i==2){
        ba_request.append(this->IntToArray(static_cast<uint32>(NUM_SAMPLES)));
        }
    }

}
myFT::~myFT(){delete(client); }

void myFT::publish()
{
    client->write(ba_request,ba_request.length()); // you can pass char * into something that expects a const char* without any
                                               // explicit cast, however you can't do reverse. since it is unsafe.
    //qDebug()<<ba_request.length();
    ba_response = QByteArray("");
    client->waitForBytesWritten(1000);
    client->waitForReadyRead(1000);
    /* Receiving the response. */
    ba_response.append(client->readAll());
    resp.rdt_sequence = this->ArrayToInt_uint32(ba_response.mid(0,3));
    resp.ft_sequence = this->ArrayToInt_uint32(ba_response.mid(4,7));
    resp.status = this->ArrayToInt_uint32(ba_response.mid(8,11));
    for( i = 0; i < 6; i++ ) {

        resp.FTData[i] = this->ArrayToInt_int32(ba_response.mid(12+4*i,15+4*i));
//        if (cal_status == true)
//        {
//            FTdata_cal[i] = abs(resp.FTData[i]);
//        }
//        if(myFT::resp.FTData[i]>0)
//        {
//        FTdata_pub = myFT::resp.FTData[i]-FTdata_cal[i];
//        }
//        else
//        {
//            FTdata_pub = myFT::resp.FTData[i]+FTdata_cal[i];
//        }

    }
//    cal_status = false;

}

template<typename T>QByteArray myFT::IntToArray(T source)
{
    QByteArray temp_ba = QByteArray("");
    QDataStream data(&temp_ba,QIODevice::ReadWrite);
    data << source;
    return temp_ba;
}

myFT::int32 myFT::ArrayToInt_int32(QByteArray source)
{
    int32 temp;
    QDataStream data(&source ,QIODevice::ReadWrite);
    data >> temp;
    return temp;
}

myFT::uint32 myFT::ArrayToInt_uint32(QByteArray source)
{
    uint32 temp;
    QDataStream data(&source ,QIODevice::ReadWrite);
    data >> temp;
    return temp;
}


