#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <zip.h>

#ifndef _MSC_VER
#include <unistd.h>
#else
#include <windows.h>
#define sleep(x) Sleep(1000 * (x))
#endif


typedef struct evtc_agent evtc_agent;

const char MAGICNUMBER[] = "EVTC20";

struct evtc_agent {
    uint64_t addr;
    uint32_t prof;
    uint32_t is_elite;
    uint16_t toughness;
    uint16_t concentration;
    uint16_t healing;
    uint16_t hitbox_width;
    uint16_t condition;
    uint16_t hitbox_height;
    char name[64];
};

/* define skill */
typedef struct evtc_skill {
    int32_t id;
    char name[64];
} evtc_skill;

enum iff { IFF_FRIEND, IFF_FOE, IFF_UNKNOWN };

int print_header(char header[16]) {
    char version[13] = {0};
    for (int i = 0; i < 12; i++) {
        version[i] = header[i];
    }
    printf("Version: %s\n", version);
    printf("Revision: %d\n", header[12]);
    printf("Boss Type: %x%x\n", header[14], header[13]);
}

char *get_data_uncompressed(char *filename, long *datasize) {
    FILE *fd = fopen(filename, "rb");
    if (!fd) {
        printf("Error opening file: %s\n", filename);
        return NULL;
    }
    fseek(fd, 0L, SEEK_END);
    size_t filesize = ftell(fd);
    fseek(fd, 0L, SEEK_SET);
    char *data = calloc(filesize + 1, sizeof(char));
    if (!data) {
        fprintf(stderr, "Failed to allocate memory.\n");
        fclose(fd);
        return NULL;
    }
    size_t elements_read = fread(data, sizeof(char), filesize, fd);
    if (elements_read != filesize) {
        fprintf(stderr, "Read less than expected! %d!=%d\n", elements_read,
                filesize);
    }
    fclose(fd);

    *datasize = elements_read;
    return data;
}

char *get_data_compressed(char *filename, long *datasize) {
    int errorp = 0;
    zip_t *archive = NULL;
    archive = zip_open(filename, 0, &errorp);
    struct zip_stat *file_info = NULL;
    file_info = calloc(1, sizeof(struct zip_stat));
    zip_stat_init(file_info);
    zip_file_t *zfd = NULL;
    char *data = NULL;
    *datasize = 0;
    if (zip_stat_index(archive, 0, 0, file_info) == 0) {
        data = calloc(file_info->size + 1, sizeof(char));
        zfd = zip_fopen_index(archive, 0, 0);
        size_t elements_read = zip_fread(zfd, data, file_info->size);
        if (elements_read != file_info->size) {
            fprintf(stderr, "Read less than expected! %d!=%d\n", elements_read,
                    file_info->size);
        }
        *datasize = elements_read;
    }
    zip_close(archive);
    return data;
}
int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        return -1;
    }

    long data_size = 0;
    char *data = get_data_uncompressed(argv[1], &data_size);
    
    if (data && strncmp(MAGICNUMBER, data, 6)!=0) {
        fprintf(stderr, "Attempting to decompress.\n");
        free(data);
        data = get_data_compressed(argv[1], &data_size);
    } 

    if (data && strncmp(MAGICNUMBER, data, 6) != 0) {
        fprintf(stderr, "After decompression, bad magic number: ");
        for (int i = 0; i < 6; i++) {
            printf("%c ", data[i]);
        }
        printf("\n");
        free(data);
        return -1;
    }

    if( !data ){
        fprintf(stderr, "Could not read file.\n");
        return -1;
    }

    size_t index = 16;
    uint32_t ag_count = 0; 
    memcpy(&ag_count,&data[index],sizeof(uint32_t));    
    index += sizeof(uint32_t);

    evtc_agent *evag_array = calloc(ag_count, sizeof(evtc_agent));
    int friendly_count = 0;
    for (int i = 0; i < ag_count; i++) {
        evtc_agent *evag = &evag_array[friendly_count];
        memcpy(evag, &data[index], sizeof(evtc_agent));
        index += sizeof( evtc_agent );
        if( evag->is_elite == 0xffffffff || ( evag->name[0]=='p' && evag->name[3] == '-' )){
            continue;
        }
        friendly_count++;
    }
    printf("%d Friendly Characters\n",friendly_count);
    for (int i = 0; i < friendly_count; i++) {
        if (evag_array[i].is_elite != 0xffffffff) {
            evag_array[i].name[63]='\0';

            printf("%d - %s\n", i,evag_array[i].name);
        }
    }
    printf("Spinning.");
    for(int i=0; i<3; i++){
        sleep(1);
        printf(".");
    }
    printf(".\n");
    srand(time(NULL));

    int winner= rand() % friendly_count;
    printf("The lucky winner is [%d] %s", winner, evag_array[winner].name);

    free(data);
    return 0;
}