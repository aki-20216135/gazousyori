#define _CRT_SECURE_NO_WARNINGS
#include "stdio.h"
#include "stdlib.h"
#include <string.h>
#include <windows.h>
//�摜�T�C�Y���`����
#define X_SIZE 640
#define Y_SIZE 480
HANDLE hFind;
WIN32_FIND_DATA fd;
//�ǂݍ��݂ƕۑ��p�̃t�@�C���p�X��p��
char read_path[500];
char save_path[500];

//���͂�RGB�l��p��
unsigned char r_in[Y_SIZE][X_SIZE], g_in[Y_SIZE][X_SIZE], b_in[Y_SIZE][X_SIZE];

//�O���C�摜�̏o�͐�̔z��
unsigned char gray[Y_SIZE][X_SIZE];

//�֐��̃v���g�^�C�v��錾����
void read_img(char* read_path, unsigned char r_in[Y_SIZE][X_SIZE], unsigned char g_in[Y_SIZE][X_SIZE], unsigned char b_in[Y_SIZE][X_SIZE]);
void gray_img(unsigned char r[Y_SIZE][X_SIZE], unsigned char g[Y_SIZE][X_SIZE], unsigned char b[Y_SIZE][X_SIZE], unsigned char img[Y_SIZE][X_SIZE]);
void save_img(char* save_path, unsigned char img[Y_SIZE][X_SIZE]);

void main(void)
{
	printf("�J�����g�f�B���N�g���̃p�X�����-->");
	scanf("%s", read_path);
	hFind = FindFirstFile("*.raw", &fd); /* �J�����g�f�B���N�g����1�ԍŏ��Ƀq�b�g������� */
	//����q�b�g���Ȃ������ꍇ
	if (hFind == INVALID_HANDLE_VALUE) {
		fprintf(stderr, "�t�@�C�����擾�ł��܂���B\n");

	}
	//�摜����
	do {
		printf("\n");
	//���͉摜�̓ǂݍ���
	read_img(read_path, r_in, g_in, b_in);

	//�O���C�X�P�[����
	gray_img(r_in, g_in, b_in, gray);

	//�o�͉摜�̕ۑ�
	save_img(save_path, gray);

	//�t�@�C�����̕\��
	/*printf("%s\n", fd.cFileName);*/

	} while (FindNextFile(hFind, &fd));
	printf("\nowari\n");
	/*FindFirstFile�Ƃ��� �J�� */
	FindClose(hFind);
}

//���͉摜�̓ǂݍ���
void read_img(char* read_path, unsigned char r[Y_SIZE][X_SIZE], unsigned char g[Y_SIZE][X_SIZE], unsigned char b[Y_SIZE][X_SIZE])
{
	int i, j;



	printf("���̃t�@�C�������H���܂�-->");
	sprintf(save_path, "%s\\%s",read_path, fd.cFileName);
	//strcat(read_path, );
	printf("%s\n", save_path);
	FILE* fp;

	//�t�@�C�����J��
	fp = fopen(save_path, "rb");

	//�����C�t�@�C���������Ƃ��ɏI��������
	if (fp == NULL)
	{
		printf("�t�@�C�������݂��܂�", save_path);
		exit(-1);
	}

	//�摜������RGB�l�̎擾�i���X�^�����j
	for (j = 0; j < Y_SIZE; j++)
	{
		for (i = 0; i < X_SIZE; i++)
		{
			r[j][i] = fgetc(fp);
			g[j][i] = fgetc(fp);
			b[j][i] = fgetc(fp);
		}
	}
	//�t�@�C�������
	fclose(fp);

}

//�O���C��
void gray_img(unsigned char r[Y_SIZE][X_SIZE], unsigned char g[Y_SIZE][X_SIZE], unsigned char b[Y_SIZE][X_SIZE], unsigned char img[Y_SIZE][X_SIZE])
{
	int i, j;

	for (j = 0; j < Y_SIZE; j++)
	{
		for (i = 0; i < X_SIZE; i++)
		{
			img[j][i] = (unsigned char)(0.30 * r[j][i] + 0.59 * g[j][i] + 0.11 * b[j][i]);
		}
	}
}

//�o�͉摜�̕ۑ�
void save_img(char* save_path, unsigned char img[Y_SIZE][X_SIZE])
{
	int i, j;

	FILE* fp;

	printf("���̃t�@�C���ɕۑ����܂�-->");
	/*scanf("%s", read_path);*/
	sprintf(save_path, "%s\\%s", read_path, fd.cFileName);
	//�t�@�C�����J��
	printf("%s\n", save_path);
	fp = fopen(save_path, "wb");

	////�����C�t�@�C���������Ƃ��ɏI��������
	if (fp == NULL)
	{
		printf("�t�@�C�������݂��܂���", save_path);
		exit(-1);
	}
	//�摜��RGB�l���t�@�C���ɕۑ�����
	for (j = 0; j < Y_SIZE; j++)
	{
		for (i = 0; i < X_SIZE; i++)
		{
			fputc(img[j][i], fp);
		}
	}

	//�t�@�C�������
	fclose(fp);
}