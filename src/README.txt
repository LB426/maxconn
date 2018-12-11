build cscope database:
cd maxconn/src
find . -name '*.c' -o -name '*.h' > cscope.files
cscope -b -q -k
