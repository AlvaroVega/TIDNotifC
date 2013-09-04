#include "MyConsumerImpl.h"

#include <sys/time.h>
#include <time.h>

using namespace std;



MyConsumerImpl::MyConsumerImpl() {
  //  cerr << "[MyConsumerImpl] MyConsumerImpl()" << endl;

};


MyConsumerImpl::~MyConsumerImpl() {

};



void MyConsumerImpl::push(const CORBA::Any& alarm_info) 
  throw (CORBA::SystemException, CosEventComm::Disconnected)
{
  // Metodo que ejecuta el ProxyPushSupplier para enviar eventos al Consumer
  const Event::TIEMPO *t_inicio;	
  struct timeval t_fin, t_diff;
  struct timezone tz;

  // Obtenemos el tiempo de llegada del evento
  gettimeofday(&t_fin,&tz);

  // Recogemos el evento que ha llegado
  alarm_info >>= t_inicio;

  // Calculamos la diferencia de tiempos
  t_diff.tv_sec  = t_fin.tv_sec  - t_inicio->tv_sec;
  t_diff.tv_usec = t_fin.tv_usec - t_inicio->tv_usec;

  cerr << "[MyConsumerImpl] push recibido:" << endl;
  cerr << "[MyConsumerImpl]      Id: " << t_inicio->id << " Inicio:  " << t_inicio->tv_sec << "/" 
                                                       << t_inicio->tv_usec << endl;
  cerr << "[MyConsumerImpl]      Id: " << t_inicio->id << " Fin:     " << t_fin.tv_sec << "/" 
                                                       << t_fin.tv_usec << endl;
  cerr << "[MyConsumerImpl]      Id: " << t_inicio->id << " Diff:    " << t_diff.tv_sec << "/" 
                                                       << t_diff.tv_usec << endl;
  return;
};


