//
// ���͕s�����R�[�h�f�[�^���쐬����
// ���̓t�@�C���Ƃ���1�s��1������ASCII�f�[�^���K�v
// ASCII�R�[�h�ŏ����ꂽ16�i�f�[�^���o�C�i���f�[�^(HEX)�ɕϊ�����
// ��)
//    ASCII                     -> BINARY
//    8140(0x38,0x31,0x34,0x30) -> 0x8140
//    8141(0x38,0x31,0x34,0x31) -> 0x8141
// �ϊ������f�[�^�́A�w�茅�����܂ł�1�s�Ƃ��ĉ��s����
//
#include <stdio.h>
#include <stdlib.h>

int main( int argc, char *argv[] )
{
	FILE *in_fp;			// ���̓t�@�C�� (ASCII�R�[�h)
	FILE *out_fp;			// �o�̓t�@�C�� (�o�C�i���f�[�^)
	char buf[16] = { 0 };	// ���̓t�@�C���ǂݍ��݃o�b�t�@
	int line = 0;
	int num_of_char = 32;	// 1�s�̕�����

	// �����̐����`�F�b�N
	if( ( argc <= 2 ) || ( argc >= 5 ) ) {
		printf("Usage: %s INPUTFILE OUTPUTFILE [NUMBER_OF_CHARACTERS]\n", argv[0]);
		return -1;
	}

	// 1�s�̕��������擾
	if( argc == 4 ) {
		num_of_char = atoi(argv[3]);
		if( num_of_char == 0 ) {
			num_of_char = 32;
		}
	}

	//
	// ���o�̓t�@�C���I�[�v��
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
	// �ϊ�����
	//
	unsigned char writedata = 0x00;
	// �P�s�Âǂݍ���
	while( fgets( buf, sizeof(buf), in_fp) != NULL ) {
		line++;
		// �P���Â`�F�b�N
		for( int col = 0; buf[col] != '\0'; col++ ) {
			unsigned char workdata = 0x00;
			if( ( buf[col] == 0x0d ) || ( buf[col] == 0x0a ) ) {
				// ���s�R�[�h�͖���
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

			// 1byte�f�[�^���쐬���A1byte�����΃t�@�C����������
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
			// �w�蕶�����ŉ��s
			writedata = '\n';
			fputc(writedata, out_fp);
			printf("\n");
		}
	}

	// �ŏI�s �w�蕶�����ɂ݂��Ȃ��ꍇ�����s
	writedata = '\n';
	fputc(writedata, out_fp);
	printf("\n");

	//
	// ���o�̓t�@�C���I�[�v��
	//
	fclose(in_fp);
	fclose(out_fp);

	return 0;
}
