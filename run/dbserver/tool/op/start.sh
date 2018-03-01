#!/bin/sh

cd ../../
program=`pwd | xargs -i basename {}`
proc_result=`ps -ef | grep "$program" | grep -v grep | wc -l`

if [ $proc_result -ne 0 ]; then
	echo "server already started!!!"
else
	echo "server starting ....."
	./bin/$program -d > /dev/null 2>&1
	PID=`ps -ef | grep $program | grep -v grep | awk '{print $2}'`
	if [ $PID ]; then
		echo "start server PID $PID sucess!!!"
	else
		echo "start server $PID failed!!"
	fi
fi


