$(CC) = gcc

bluetooth : main.c hcicmd.c linux.c
	$(CC) main.c hcicmd.c linux.c hcievent.c -o bluetooth -pthread

ble : mainle.c hcicmdle.c linux.c
	$(CC) mainle.c hcicmd.c hcicmdle.c linux.c -o ble
clean :
	rm bluetooth ble
