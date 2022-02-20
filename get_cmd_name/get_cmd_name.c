#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

//
// プロセスIDからコマンド名を取得する
//
int getProcName(pid_t pid, char *pName)
{
	FILE *fp;
	int ret = 0;
	char cmd[32] = { 0x00 };
	char pidstr[8] = { 0x00 };
	char procname[64] = { 0x00 };

	sprintf(pidstr, "%d", pid);

	// ps コマンドを作成する
	//  -p プロセスID
	//  ^h ヘッダ行を表示しない
	//  -o cmd コマンド名のみを表示する
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

	// 自身のプロセスIDを取得する
	pid = getpid();

	// プロセスIDからコマンド名を取得する
	getProcName(pid, procname);

	printf("procname=%s\n", procname);
}
