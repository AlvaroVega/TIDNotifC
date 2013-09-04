#!/bin/bash
# rm -rf .notif
# rm *.ior
# ./notif_daemon > agent.ior&
# sleep 5
# ./tidnotif start < agent.ior &
# sleep 5
# ./tidnotif factory < agent.ior > factory.ior&
# sleep 5
# echo 'tidnotif started'
i=`cat /tmp/notify_factory.ior`


echo "Launching server consumer"
./server_consumer $i \
    -ORB_trace_level 5 \
    -ORB_trace_file server_consumer.log \
    -ORB_max_blocked_time 1500000 &
sleep 5


echo "Launching server supplier $i"
./server_supplier $i \
    -ORB_trace_level 5 \
    -ORB_trace_file server_supplier.log \
    -ORB_max_blocked_time 1500000 &
sleep 5


echo "Launching revocer server supplier $i"
./recover_server_supplier $i \
    -ORB_trace_level 5 \
    -ORB_trace_file recover_server_supplier.log \
    -ORB_max_blocked_time 1500000 &
sleep 5

# killall -9 lt-notif_daemon
# killall -9 lt-server_supplier
# killall -9 lt-server_consumer

