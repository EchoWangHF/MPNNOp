#for var in "$@"
#do
#    echo "$var"
#    clang-format -style=Google -i $var
#done
function format_file(){
  #file = $1
  #中括号和标识符之间一定要有空格
  if [ "${1##*.}"x == "cpp"x ]||[ "${1##*.}"x == "c"x ] || [ "${1##*.}"x == "mlu"x ]\
     || [ "${1##*.}"x == "cu"x ] || [ "${1##*.}"x == "h"x ] || [ "${1##*.}"x == "hpp"x ]
  then
    clang-format -style=Google -i $1
  else
    echo "sorry, style_format just support *.cpp, *.c, *.h, *.hpp, *.mlu or *.cu now!"
  fi
}

function read_dir() {
for file in `ls $1` #注意此处这是两个反引号，表示运行系统命令
do
  if [ -d $1"/"$file ] #注意此处之间一定要加上空格，否则会报错
  then
    read_dir $1"/"$file
  else
    echo $1"/"$file #在此处处理文件即可
    #clang-format -style=Google -i $1"/"$file
    format_file $1"/"$file
  fi
done
}


for var in "$@"
do
  if [ -d $var ]
  then
    #echo "$var is a directory"
    read_dir $var
  elif [ -f $var ]
  then
    echo "$var"
    #clang-format -style=Google -i $var
    format_file $var
  else
    echo "sorry, the input style_format.sh can not do!"
  fi
done

