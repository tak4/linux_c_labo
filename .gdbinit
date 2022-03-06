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
