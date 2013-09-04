#!/bin/sh

for i in 1 2 3 4 5 6 7 8 9 10 11 12 13 14; do 
    if test -r /tmp/notify_factory.ior; then break 
    else sleep 1
    fi 
done

./server -ORB_trace_level 4 -ORB_trace_file server.log \
    -ORB_max_blocked_time 1500000 \
    -ORB_poa_min_threads 3 -ORB_poa_max_threads 3 \
    -ORB_miop_send_delay 0 \
    < /tmp/notify_factory.ior > /tmp/channel.ior &

server_pid=$!
sleep 1 

for i in 1 2 3 4 5 6 7 8 9 10 11 12 13 14; do 
    if test -r /tmp/channel.ior; then break 
    else sleep 1
    fi 
done

./consumer1 -ORB_trace_level 4 -ORB_trace_file consumer1.log \
    -ORB_max_blocked_time 1500000 \
    -ORB_poa_min_threads 3 -ORB_poa_max_threads 3 \
    -ORB_miop_send_delay 0 \
    < /tmp/channel.ior &
consumer1_pid=$!

./consumer2 -ORB_trace_level 4 -ORB_trace_file consumer2.log \
    -ORB_max_blocked_time 1500000 \
    -ORB_poa_min_threads 3 -ORB_poa_max_threads 3 \
    -ORB_miop_send_delay 0 \
    < /tmp/channel.ior &
consumer2_pid=$!
sleep 3 

./supplier -ORB_trace_level 4 -ORB_trace_file supplier.log \
    -ORB_max_blocked_time 15000000 \
    -ORB_poa_min_threads 3 -ORB_poa_max_threads 3 \
    -ORB_miop_send_delay 0 \
    < /tmp/channel.ior

read c
sleep 10
kill -9 $consumer1_pid
kill -9 $consumer2_pid
kill -9 $server_pid
kill -9 $Notif_pid
kill -9 $supplier_pid

