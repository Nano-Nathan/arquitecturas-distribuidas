path="/home/mpiuser/serrano_cristian/arquitecturas-distribuidas/TP3/E02"
file="/home/mpiuser/serrano_cristian/arquitecturas-distribuidas/TP1/E02"
cp $file/patrones.txt $path
cp $file/texto.txt $path
scp $file/patrones.txt mpiuser@ip:$path
scp $file/texto.txt mpiuser@ip:$path