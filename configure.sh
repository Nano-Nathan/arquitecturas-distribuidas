path="TP3/E02"
export PATH_SRC='/home/hash/serrano_cristian/arquitecturas-distribuidas'
export PATH_FILE=$path
ssh mpi@ip "export PATH_SRC='/home/hash/serrano_cristian/arquitecturas-distribuidas';export PATH_FILE=$path"
chmod +x ./execute.sh
./execute.sh