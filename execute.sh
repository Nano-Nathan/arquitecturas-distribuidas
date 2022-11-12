cd $PATH_SRC
git pull
cd $PATH_FILE
mpicxx -O3 -o main.o main.cpp -O3
ssh mpiuser@ip 'cd $PATH_SRC; git pull;cd $PATH_FILE;mpicxx -O3 -o main.o main.cpp -O3'
mpirun -n 10 --hostfile ../machinesfile.txt ./main.o