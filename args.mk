ifndef NUM_EPOCHS
	NUM_EPOCHS = 100
endif

ifndef L
	L=0.1
endif

_ARGS = -n data/net.nn -o data/$(OUT_NET_FILENAME) -t data/td.td -e $(NUM_EPOCHS) -l $(L) -p 10 | tee $(LOG_FILE)

ifndef ARGS
	ARGS = _ARGS
else
	ARGS += _ARGS
endif
