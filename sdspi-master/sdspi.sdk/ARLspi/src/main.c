#include <stdio.h>
#include <stdint.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <linux/types.h>
#include <linux/spi/spidev.h>



int
main (int argc, char *argv[])
{


	int i, fid, status, len;
	struct spi_ioc_transfer xfer;
	unsigned char rx_buf[8];
	unsigned char tx_buf[32];
	unsigned char out_buf[32];
	unsigned int tx_val;
	char *name = argv[1];			/* device file is the first argument */
	int xfer_len = argc - 2;

	for(i = 0; i < 32; i++) {
		tx_buf[i] = 0;
	}
	tx_buf[3] = 1;

	printf("Opening SPIDev: %s\n", name);
	fid = open(name, O_RDWR);

	memset(tx_buf, 0, sizeof(tx_buf));
	memset(rx_buf, 0, sizeof(rx_buf));
	memset(&xfer, 0, sizeof(struct spi_ioc_transfer));


	for (i = 0; i < xfer_len; i++) {
		sscanf(argv[i + 2], "%x", (unsigned int *)&tx_buf[i]);
	}

	if (fid < 0) {
		perror("Opening file");
		return 1;
	}
	while(1) {
		xfer.tx_buf = (unsigned long)tx_buf;
		xfer.rx_buf = (unsigned long)rx_buf;
		xfer.speed_hz = 500000;
		xfer.len = xfer_len;

		status = ioctl(fid, SPI_IOC_MESSAGE(1), &xfer);

		len = sprintf(out_buf, "MOSI: ");
		for (i = 0; i < xfer_len; i++) {
			len += sprintf(&out_buf[len], "0x%02X ", tx_buf[i]);
		}

		len += sprintf(&out_buf[len], "\nMISO: ");
		for (i = 0; i < xfer_len; i++) {
			len += sprintf(&out_buf[len], "0x%02X ", rx_buf[i]);
		}

		printf("%s\n", out_buf);
	}
}
