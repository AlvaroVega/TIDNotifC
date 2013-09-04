#!/bin/sh

#
# Script para lanzar todos los procesos involucrados en el ejemplo
#


# $TIDNOTIF_HOME/bin/Notif -ORB_trace_level 4 -ORB_trace_file Notif.log > /tmp/factory.ior &
# Notif_pid=$!
# sleep 1

for i in 1 2 3 4 5 6 7 8 9 10 11 12 13 14; do 
    if test -r /tmp/factory.ior; then break 
    else sleep 1
    fi 
done

./server -ORB_trace_level 4 -ORB_trace_file server.log < /tmp/factory.ior > /tmp/channel.ior &
server_pid=$!
sleep 1 

for i in 1 2 3 4 5 6 7 8 9 10 11 12 13 14; do 
    if test -r /tmp/channel.ior; then break 
    else sleep 1
    fi 
done

./consumer1 -ORB_trace_level 4 -ORB_trace_file consumer1.log < /tmp/channel.ior &
consumer1_pid=$!

./consumer2 -ORB_trace_level 4 -ORB_trace_file consumer2.log < /tmp/channel.ior &
consumer2_pid=$!
sleep 3 

./supplier -ORB_trace_level 4 -ORB_trace_file supplier.log < /tmp/channel.ior

echo -n "Pulsa una tecla para terminar"
read c
sleep 5
kill -9 $consumer1_pid
kill -9 $consumer2_pid
kill -9 $server_pid
#kill -9 $Notif_pid
#kill -9 $supplier_pid

