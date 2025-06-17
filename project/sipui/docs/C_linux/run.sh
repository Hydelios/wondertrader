export LD_LIBRARY_PATH=./
g++ -o demo work.cpp -DMULTI_CONS -I../include -L./ -lsipui2x64 -lrt -ldl
./demo
