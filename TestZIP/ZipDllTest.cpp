#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <direct.h>
#include <stdlib.h>
#include <stdio.h>
#include <io.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <zip.h>

#pragma warning(disable : 4996)
//#pragma comment(lib, "jvm.lib")

static int writeCurrentFile(int i, struct zip* za, struct zip_stat zipStat, char bufForFileName[]) {

    struct zip_file* zipFile; // ��������� ��� ������ � ������� ������ ������
    int fd; // �������� ����������
    zip_int64_t lenOfReadData; // ������� ���� ���� ��������� �� �����
    char buf[512]; // ����� ��� ������ ���������� �� ������

    zipFile = zip_fopen_index(za, i, 0);
    if (!zipFile) {

        return 1;
    }
    fd = _open(bufForFileName, O_RDWR | O_TRUNC | O_CREAT, 0644); //������� ����
    if (fd < 0) { // ���� ���� ������ �������, ������ ��������� ������

        zip_fclose(zipFile);
        return 1;
    }
    zip_uint64_t sum = 0; // ������ ������ �������� ����� � ������
    while (sum != zipStat.size) {

        lenOfReadData = zip_fread(zipFile, buf, sizeof(buf) * sizeof(buf[0]));
        if (lenOfReadData < 0) {

            zip_fclose(zipFile);
            return 1;
        }
        _write(fd, buf, lenOfReadData);
        sum += lenOfReadData;
    }
    close(fd);
    int zipCloseResult = zip_fclose(zipFile);
    if (zipCloseResult != 0) {

        return 1;
    }
    return 0;
}


static int loopThroughFiles(const char* archiveRoot, struct zip* za) {

    int i; // ���������� ��� ������������
    struct zip_stat zipStat; // ���������� � �����
    size_t currentItemNameLength; // ����� ����� �������� �������� � ������

    for (i = 0; i < zip_get_num_entries(za, 0); i++) {

        if (zip_stat_index(za, i, 0, &zipStat) == 0) {

            currentItemNameLength = strlen(zipStat.name);
            printf("��� �����: [%s], ", zipStat.name);
            printf("������: [%llu], ", zipStat.size);
            printf("\n");
            char bufForFileName[300]; // ����� ��� ����� ����� � ������ �������� �����
            strcpy(bufForFileName, archiveRoot);
            strcat(bufForFileName, zipStat.name);
            if (zipStat.name[currentItemNameLength - 1] == '/') { // ���� ������� ������� ������ - �����, �� ����� ������� ����� �� �����

                if (mkdir(bufForFileName) < 0) { // ���� �� ������� ������� �����
                    if (errno != EEXIST) { // ���� �� ������� ������� ����� �� ������� ����, ��� ��� ��� ���� �������, �� �� ���������, ����� �������� ���������

                        return 1;
                    }
                }
            }
            else { // ������� ������� - ����, � ������ ����� ��������������� ������� ��� ������ � �������� �� �� ����

                writeCurrentFile(i, za, zipStat, bufForFileName);
            }
        }
    }
    return 0;
}


int enumerateArchive(const char* filePath, const char* archiveRoot) {

    struct zip* za;// ��������� ��� ������ � �������
    int err; // ��� ��������� ������
    // ���������� ������� ���� � �������, ���� �� ���������� - �������� �� ������
    if ((za = zip_open(filePath, ZIP_CREATE | ZIP_RDONLY, &err)) == NULL) {

        return 1;
    }
    // �������� �� ���� ��������� ������
    loopThroughFiles(archiveRoot, za);
    // ������� ���� � ������� (���� �� ���������� - �������� �� ������)
    if (zip_close(za) == -1) {

        return 1;
    }
    return 0;
}

int main() {
    enumerateArchive("C:\\Users\\User\\pi2.rar", "");
}
