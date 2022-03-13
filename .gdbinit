set history save on
set history size 10000
set history filename ~/.gdb_history
set listsize 25
set print pretty on
# set confirm 0
# set follow-fork child

# memset byte(char型)データで埋める
# memset &ts 0xaa 8
define memset
set var $addr = &{char}$arg0
set var $i = 0
while $i < $arg2
set var {char}($addr+$i) = $arg1
set var $i = $i + 1
end
end

# メモリダンプ(byte)
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

# 引数表示
# info args
# show args

# ローカル変数表示
# info local

# breakpointを30回無視
# ignore 3 30

# 関数表示
# help function

# 文字列比較
# p $_streq(bufc, "TEST")
# b if $_streq(bufc, "TEST")

# breakpoint有効/無効化
# disable br 1
# enable br 1

# 未知のシンボルへのbreakpoint設定
# set breakpoint pending on
# set breakpoint pending off
