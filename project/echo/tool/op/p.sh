#!/bin/sh

cd ../../
program=$(pwd | xargs -i basename {})
ps -flu ${LOGNAME} 2>/dev/null | awk '{ if(FNR == 1) print $0}'
ps -flu ${LOGNAME} 2>/dev/null | grep "./$program" | grep -v grep | awk '{print $0}'
