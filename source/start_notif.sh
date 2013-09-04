#
#  Copyright (C) 2006 Telefonica I+D S.A.
#
#  This source file is a property of Telefonica I+D. You can not
#  use it for any purpose unless you have an explicit authorization
#  by owner.
#

#!/bin/sh
if [ -z "$TIDNOTIFC_HOME" ]; then
        echo "Environment variable TIDNOTIFC_HOME must be set"
        exit 1
fi

# num=`netstat -ntap 2> /dev/null | grep 2006 | wc -l`
# if [ $num != "0" ]; then
#         echo "Port 2006 busy"
#         exit 1
# fi

#
# TIDNotifC++ options :
#
#   TIDNotif.orb.port num_port
#   TIDNotif.persistence.db { none | file }
#   TIDNotif.data.path path
#   TIDNotif.data.root path
#   TIDNotif.channel.poa 0  { 0=global /  1=local }
#   TIDNotif.supplier.poa 0 { 0=global /  1=local }
#   TIDNotif.consumer.poa 0 { 0=global /  1=local }


echo "Starting TIDNotif daemon..."
$TIDNOTIFC_HOME/bin/notifd \
    -ORB_trace_level 5 \
    -ORB_trace_file tidnotif.log \
    -ORB_max_blocked_time 150000 \
    -ORB_poa_max_queued_requests 10000 \
    -ORB_typecode_cache_size 2000 \
    -ORB_poa_min_threads 8 \
    -ORB_poa_max_threads 8 \
    TIDNotif.orb.port 2022 \
    TIDNotif.persistence.db file \
    TIDNotif.channel.poa 0 \
    TIDNotif.supplier.poa 0 \
    TIDNotif.consumer.poa 0 \
    > /tmp/notify_service.ior &
notif_daemon_pid=$!
sleep 2


echo "Starting TIDNotif service..."
$TIDNOTIFC_HOME/bin/tidnotif start \
    -ORB_max_blocked_time 1500000 \
    < /tmp/notify_service.ior
sleep 1


echo "Obtaining a factory..."
$TIDNOTIFC_HOME/bin/tidnotif factory \
    -ORB_max_blocked_time 1500000 \
    < /tmp/notify_service.ior \
    > /tmp/notify_factory.ior 


echo "Press any key to stop tidnotif daemon"
read n
sleep 1
$TIDNOTIFC_HOME/bin/tidnotif stop \
    -ORB_max_blocked_time 1500000 \
    < /tmp/notify_service.ior


echo "Press any key to restart tidnotif daemon"
read n
sleep 1
$TIDNOTIFC_HOME/bin/tidnotif start \
    -ORB_max_blocked_time 1500000 \
    < /tmp/notify_service.ior


echo "Press any key to halt notif daemon"
read n
sleep 1
$TIDNOTIFC_HOME/bin/tidnotif halt \
    -ORB_max_blocked_time 1500000 \
    < /tmp/notify_service.ior 


# sleep 1
# echo "Killing notif daemon..."
# kill $notif_daemon_pid
