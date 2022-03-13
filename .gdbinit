set history save on
set history size 10000
set history filename ~/.gdb_history
set listsize 25
set print pretty on
# set confirm 0
# set follow-fork child

# memset byte(char�^)�f�[�^�Ŗ��߂�
# memset &ts 0xaa 8
define memset
set var $addr = &{char}$arg0
set var $i = 0
while $i < $arg2
set var {char}($addr+$i) = $arg1
set var $i = $i + 1
end
end

# �������_���v(byte)
# memdump &ts 8
define memdump
x /$arg1xb $arg0
end

define memsetc
set $i=0
while $i < $arg2
set {char}($arg0+$i) = $arg1
set $i = $i + 1
end
end

define memseti
set $i=0
while $i < $arg2
set {int}($arg0+$i) = $arg1
set $i = $i + 1
end
end

define modec
set follow-fork child
show follow-fork
end

define subb
b fork_test.c:68
r
set breakpoint pending on
b subprocess
set breakpoint pending off
set follow-fork child
c
end

# �����\��
# info args
# show args

# ���[�J���ϐ��\��
# info local

# breakpoint��30�񖳎�
# ignore 3 30

# �֐��\��
# help function

# �������r
# p $_streq(bufc, "TEST")
# b if $_streq(bufc, "TEST")

# breakpoint�L��/������
# disable br 1
# enable br 1

# ���m�̃V���{���ւ�breakpoint�ݒ�
# set breakpoint pending on
# set breakpoint pending off
