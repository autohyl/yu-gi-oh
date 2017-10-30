#!/bin/sh

cd ../../
program=`pwd | xargs -i basename {}`
proc_result=`ps -ef | grep "$program" | grep -v grep | wc -l`

if [ $proc_result -eq 0 ]; then
	echo "server not run!!!"
else
	echo "wait stop server ..."
	PID=`ps -ef | grep "$program" | grep -v grep | awk '{print $2}'`
	kill -s USR2 $PID > /dev/null 2>&1
	echo "stop server PID $PID sucess!!!"
fi
