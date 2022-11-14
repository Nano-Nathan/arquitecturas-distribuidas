path="/TP3/E01"
export PATH_SRC='/home/hash/serrano_cristian/arquitecturas-distribuidas'
export PATH_FILE=$path
ssh mpiuser@10.65.4.46 "export PATH_SRC='/home/hash/serrano_cristian/arquitecturas-distribuidas';export PATH_FILE=$path"
ssh mpiuser@10.65.4.104 "export PATH_SRC='/home/hash/serrano_cristian/arquitecturas-distribuidas';export PATH_FILE=$path"
ssh mpiuser@10.65.4.231 "export PATH_SRC='/home/hash/serrano_cristian/arquitecturas-distribuidas';export PATH_FILE=$path"
ssh mpiuser@10.65.4.230 "export PATH_SRC='/home/hash/serrano_cristian/arquitecturas-distribuidas';export PATH_FILE=$path"
ssh mpiuser@10.65.4.227 "export PATH_SRC='/home/hash/serrano_cristian/arquitecturas-distribuidas';export PATH_FILE=$path"
chmod +x ./execute.sh
./execute.sh