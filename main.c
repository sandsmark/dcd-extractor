#include <stdio.h>
#include "imximage.h"
#include <endian.h>

int main(int argc, char *argv[])
{
    if (argc < 2) {
        printf("usage: %s uboot.bin\n", argv[0]);
        return 1;
    }

    FILE *file = fopen(argv[1], "r");
    if (!file) {
        printf("Unable to open u-boot binary %s\n", argv[1]);
        return 1;
    }

    dcd_v2_t dcd_table;

    int byte = getc(file);

    while (byte != EOF) {
        if (byte != IVT_HEADER_TAG) {
            byte = getc(file);
            continue;
        }

        long pos = ftell(file);
        ungetc(byte, file);

        imx_header_v2_t header;
        fread(&header, sizeof(imx_header_v2_t), 1, file);
        dcd_v2_t dcd_table = header.data.dcd_table;
        if (header.fhdr.header.tag != IVT_HEADER_TAG ||
            header.fhdr.header.version != IVT_VERSION ||
            dcd_table.header.tag != DCD_HEADER_TAG ||
            dcd_table.header.version != DCD_VERSION) {
            printf("Got false positive\n");
            fseek(file, pos, SEEK_SET);
            byte = getc(file);
            continue;
        }
        for (size_t i = 0; i < MAX_HW_CFG_SIZE_V2; i++) {
            printf("DATA 4, 0x%08x, 0x%08x\n", be32toh(dcd_table.addr_data[i].addr), be32toh(dcd_table.addr_data[i].value));
        }
        break;
    }

    fclose(file);
    if (byte == EOF) {
        printf("Unable to find imx header in file\n");
        return 1;
    } else {
        return 0;
    }
}
