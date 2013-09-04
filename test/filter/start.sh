#!/bin/sh

./test_filter \
    -ORB_trace_level 5 \
    -ORB_trace_file test_filter.log \
    -ORB_max_blocked_time 1500000 \
    -ORB_poa_min_threads 3 \
    -ORB_poa_max_threads 3 \
    < /tmp/notify_factory.ior 
