Please refer to <https://github.com/hackerspacesg/SIGFOX/wiki>

Running on rpi with

	while true; do echo "$(date +%s)" | tee /dev/ttyUSB0 >> sendlog-$(date +%Y-%m-%d).txt; sleep 600 ; done
