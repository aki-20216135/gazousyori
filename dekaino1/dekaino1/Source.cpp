#define _CRT_SECURE_NO_WARNINGS
#include "stdio.h"
#include "stdlib.h"
#include <string.h>
#include <windows.h>
//画像サイズを定義する
#define X_SIZE 640
#define Y_SIZE 480
HANDLE hFind;
WIN32_FIND_DATA fd;
//読み込みと保存用のファイルパスを用意
char read_path[500];
char save_path[500];

//入力のRGB値を用意
unsigned char r_in[Y_SIZE][X_SIZE], g_in[Y_SIZE][X_SIZE], b_in[Y_SIZE][X_SIZE];

//グレイ画像の出力先の配列
unsigned char gray[Y_SIZE][X_SIZE];

//関数のプロトタイプを宣言する
void read_img(char* read_path, unsigned char r_in[Y_SIZE][X_SIZE], unsigned char g_in[Y_SIZE][X_SIZE], unsigned char b_in[Y_SIZE][X_SIZE]);
void gray_img(unsigned char r[Y_SIZE][X_SIZE], unsigned char g[Y_SIZE][X_SIZE], unsigned char b[Y_SIZE][X_SIZE], unsigned char img[Y_SIZE][X_SIZE]);
void save_img(char* save_path, unsigned char img[Y_SIZE][X_SIZE]);

void main(void)
{
	printf("カレントディレクトリのパスを入力-->");
	scanf("%s", read_path);
	hFind = FindFirstFile("*.raw", &fd); /* カレントディレクトリの1番最初にヒットするもの */
	//一つもヒットしなかった場合
	if (hFind == INVALID_HANDLE_VALUE) {
		fprintf(stderr, "ファイルを取得できません。\n");

	}
	//画像処理
	do {
		printf("\n");
	//入力画像の読み込み
	read_img(read_path, r_in, g_in, b_in);

	//グレイスケール化
	gray_img(r_in, g_in, b_in, gray);

	//出力画像の保存
	save_img(save_path, gray);

	//ファイル名の表示
	/*printf("%s\n", fd.cFileName);*/

	} while (FindNextFile(hFind, &fd));
	printf("\nowari\n");
	/*FindFirstFileとかの 開放 */
	FindClose(hFind);
}

//入力画像の読み込み
void read_img(char* read_path, unsigned char r[Y_SIZE][X_SIZE], unsigned char g[Y_SIZE][X_SIZE], unsigned char b[Y_SIZE][X_SIZE])
{
	int i, j;



	printf("このファイルを加工します-->");
	sprintf(save_path, "%s\\%s",read_path, fd.cFileName);
	//strcat(read_path, );
	printf("%s\n", save_path);
	FILE* fp;

	//ファイルを開く
	fp = fopen(save_path, "rb");

	//もし，ファイルが無いときに終了させる
	if (fp == NULL)
	{
		printf("ファイルが存在しませ", save_path);
		exit(-1);
	}

	//画像内からRGB値の取得（ラスタ走査）
	for (j = 0; j < Y_SIZE; j++)
	{
		for (i = 0; i < X_SIZE; i++)
		{
			r[j][i] = fgetc(fp);
			g[j][i] = fgetc(fp);
			b[j][i] = fgetc(fp);
		}
	}
	//ファイルを閉じる
	fclose(fp);

}

//グレイ化
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

//出力画像の保存
void save_img(char* save_path, unsigned char img[Y_SIZE][X_SIZE])
{
	int i, j;

	FILE* fp;

	printf("このファイルに保存します-->");
	/*scanf("%s", read_path);*/
	sprintf(save_path, "%s\\%s", read_path, fd.cFileName);
	//ファイルを開く
	printf("%s\n", save_path);
	fp = fopen(save_path, "wb");

	////もし，ファイルが無いときに終了させる
	if (fp == NULL)
	{
		printf("ファイルが存在しません", save_path);
		exit(-1);
	}
	//画像のRGB値をファイルに保存する
	for (j = 0; j < Y_SIZE; j++)
	{
		for (i = 0; i < X_SIZE; i++)
		{
			fputc(img[j][i], fp);
		}
	}

	//ファイルを閉じる
	fclose(fp);
}