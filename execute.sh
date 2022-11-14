cd $PATH_SRC
git pull
cd $PATH_FILE
mpicxx -O3 -o main.o main.cpp -O3
ssh mpiuser@10.65.4.46 'cd $PATH_SRC; git pull;cd $PATH_FILE;mpicxx -O3 -o main.o main.cpp -O3'
ssh mpiuser@10.65.4.104 'cd $PATH_SRC; git pull;cd $PATH_FILE;mpicxx -O3 -o main.o main.cpp -O3'
ssh mpiuser@10.65.4.231 'cd $PATH_SRC; git pull;cd $PATH_FILE;mpicxx -O3 -o main.o main.cpp -O3'
ssh mpiuser@10.65.4.230 'cd $PATH_SRC; git pull;cd $PATH_FILE;mpicxx -O3 -o main.o main.cpp -O3'
ssh mpiuser@10.65.4.227 'cd $PATH_SRC; git pull;cd $PATH_FILE;mpicxx -O3 -o main.o main.cpp -O3'