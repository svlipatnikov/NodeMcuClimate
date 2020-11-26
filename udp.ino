//=======================================================================================================
// функции UDP

unsigned long Last_UDP_send_time; // время крайней отправки по udp
const int UDP_SEND_PERIOD = 3000; // частота отправки пакетов UDP

// функция отправки по UDP
void Send_UDP(char data[UDP_TX_PACKET_MAX_SIZE])
{
  if (currentCicleTime - Last_UDP_send_time > UDP_SEND_PERIOD)
  {
    Last_UDP_send_time = currentCicleTime;
    Udp.beginPacket(IP_Fan_controller, 8888);
    Udp.write(data);
    Udp.endPacket();
  }
}
