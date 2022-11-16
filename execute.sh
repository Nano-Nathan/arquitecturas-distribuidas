cd '/home/mpiuser/serrano_cristian/arquitecturas-distribuidas'
git pull
cd 'TP3/E03'
mpicxx -O3 -o main.o main.cpp -O3
ssh mpiuser@10.65.4.46 "cd '/home/mpiuser/serrano_cristian/arquitecturas-distribuidas'; git pull;cd 'TP3/E03';mpicxx -O3 -o main.o main.cpp -O3"
ssh mpiuser@10.65.4.231 "cd '/home/mpiuser/serrano_cristian/arquitecturas-distribuidas'; git pull;cd 'TP3/E03';mpicxx -O3 -o main.o main.cpp -O3"
ssh mpiuser@10.65.4.230 "cd '/home/mpiuser/serrano_cristian/arquitecturas-distribuidas'; git pull;cd 'TP3/E03';mpicxx -O3 -o main.o main.cpp -O3"
ssh mpiuser@10.65.4.227 "cd '/home/mpiuser/serrano_cristian/arquitecturas-distribuidas'; git pull;cd 'TP3/E03';mpicxx -O3 -o main.o main.cpp -O3"
mpirun -n 3 --hostfile /home/mpiuser/serrano_cristian/arquitecturas-distribuidas/TP3/machinesfile.txt /home/mpiuser/serrano_cristian/arquitecturas-distribuidas/TP3/E03/main.o