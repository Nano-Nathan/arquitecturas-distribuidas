path="/home/mpiuser/serrano_cristian/arquitecturas-distribuidas/TP3/E02"
file="/home/mpiuser/serrano_cristian/arquitecturas-distribuidas/TP1/E02"
cp $file/patrones.txt $path
cp $file/texto.txt $path
scp $file/patrones.txt mpiuser@10.65.4.46:$path
scp $file/texto.txt mpiuser@10.65.4.46:$path
scp $file/patrones.txt mpiuser@10.65.4.231:$path
scp $file/texto.txt mpiuser@10.65.4.231:$path
scp $file/patrones.txt mpiuser@10.65.4.230:$path
scp $file/texto.txt mpiuser@10.65.4.230:$path
scp $file/patrones.txt mpiuser@10.65.4.227:$path
scp $file/texto.txt mpiuser@10.65.4.227:$path