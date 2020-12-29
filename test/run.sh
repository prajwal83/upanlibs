INCLUDES="-I${UPANIX_HOME}/libmcpp/infra -I${UPANIX_HOME}/libmcpp/ds"
DFLAGS=-D__LOCAL_TEST__
CXXFLAGS=-std=c++11

./compile.sh

./test_vector.aout
./test_queue.aout
./test_list.aout
./test_map.aout
