#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

//
// �v���Z�XID����R�}���h�����擾����
//
int getProcName(pid_t pid, char *pName)
{
	FILE *fp;
	int ret = 0;
	char cmd[32] = { 0x00 };
	char pidstr[8] = { 0x00 };
	char procname[64] = { 0x00 };

	sprintf(pidstr, "%d", pid);

	// ps �R�}���h���쐬����
	//  -p �v���Z�XID
	//  ^h �w�b�_�s��\�����Ȃ�
	//  -o cmd �R�}���h���݂̂�\������
	strcat(cmd, "ps -p ");
	strcat(cmd, pidstr);
	strcat(cmd, " -h -o cmd");

	fp = popen(cmd, "r");
	if( NULL == fp ){
		ret = -1;
	}
	else {
		fgets(procname, sizeof(procname), fp);
		pclose(fp);
		ret = 0;
	}

	strcpy(pName, procname);

	return ret;
}

int main (void)
{
	pid_t pid;
	char procname[64] = { 0x00 };

	// ���g�̃v���Z�XID���擾����
	pid = getpid();

	// �v���Z�XID����R�}���h�����擾����
	getProcName(pid, procname);

	printf("procname=%s\n", procname);
}
