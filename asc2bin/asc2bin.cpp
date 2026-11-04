//
// 入力不可文字コードデータを作成する
// 入力ファイルとして1行に1文字のASCIIデータが必要
// ASCIIコードで書かれた16進データをバイナリデータ(HEX)に変換する
// 例)
//    ASCII                     -> BINARY
//    8140(0x38,0x31,0x34,0x30) -> 0x8140
//    8141(0x38,0x31,0x34,0x31) -> 0x8141
// 変換したデータは、指定桁数分までを1行として改行する
//
#include <stdio.h>
#include <stdlib.h>

int main( int argc, char *argv[] )
{
	FILE *in_fp;			// 入力ファイル (ASCIIコード)
	FILE *out_fp;			// 出力ファイル (バイナリデータ)
	char buf[16] = { 0 };	// 入力ファイル読み込みバッファ
	int line = 0;
	int num_of_char = 32;	// 1行の文字数

	// 引数の数をチェック
	if( ( argc <= 2 ) || ( argc >= 5 ) ) {
		printf("Usage: %s INPUTFILE OUTPUTFILE [NUMBER_OF_CHARACTERS]\n", argv[0]);
		return -1;
	}

	// 1行の文字数を取得
	if( argc == 4 ) {
		num_of_char = atoi(argv[3]);
		if( num_of_char == 0 ) {
			num_of_char = 32;
		}
	}

	//
	// 入出力ファイルオープン
	//
	if( ( in_fp = fopen( argv[1], "r" ) ) == NULL ) {
		printf(" file open error :%s\n", argv[1]);
		return -1;
	}
	
	if( ( out_fp = fopen( argv[2], "w" ) ) == NULL ) {
		printf(" file open error :%s\n", argv[2]);
		return -1;
	}

	//
	// 変換処理
	//
	unsigned char writedata = 0x00;
	// １行づつ読み込み
	while( fgets( buf, sizeof(buf), in_fp) != NULL ) {
		line++;
		// １桁づつチェック
		for( int col = 0; buf[col] != '\0'; col++ ) {
			unsigned char workdata = 0x00;
			if( ( buf[col] == 0x0d ) || ( buf[col] == 0x0a ) ) {
				// 改行コードは無視
				continue;
			}
			else if( ( buf[col] >= '0' ) && ( buf[col] <= '9' ) ) {
				workdata = buf[col] - '0';
			}
			else if( ( buf[col] >= 'A' ) && ( buf[col] <= 'F' ) ) {
				workdata = buf[col] - 'A' + 0xa;
			}
			else if( ( buf[col] >= 'a' ) && ( buf[col] <= 'f' ) ) {
				workdata = buf[col] - 'a' + 0xa;
			}
			else {
				printf("\n input data error\n");
				break;
			}

			// 1byteデータを作成し、1byte揃えばファイル書き込み
			if( ( col % 2 ) == 0 ) {
				writedata = ( workdata << 4 );
			}
			else {
				writedata |= workdata;
				printf("%02x ", writedata);
				fputc(writedata, out_fp);
			}
		}

		if( ( line % num_of_char ) == 0 ) {
			// 指定文字数で改行
			writedata = '\n';
			fputc(writedata, out_fp);
			printf("\n");
		}
	}

	// 最終行 指定文字数にみたない場合も改行
	writedata = '\n';
	fputc(writedata, out_fp);
	printf("\n");

	//
	// 入出力ファイルオープン
	//
	fclose(in_fp);
	fclose(out_fp);

	return 0;
}
