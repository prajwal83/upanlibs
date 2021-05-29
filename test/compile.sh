INCLUDES="-I${UPANLIBS_HOME}/libustd/infra -I${UPANLIBS_HOME}/libustd/ds -I${UPANLIBS_HOME}/libustd/algo"
DFLAGS=-D__LOCAL_TEST__
CXXFLAGS=-std=c++11

rm -f *.aout

echo "compiling test_vector.C..."
g++ ${CXXFLAGS} ${INCLUDES} ${DFLAGS} test_vector.C -o test_vector.aout

echo "compiling test_queue.C..."
g++ ${CXXFLAGS} ${INCLUDES} ${DFLAGS} test_queue.C -o test_queue.aout

echo "compiling test_list.C..."
g++ ${CXXFLAGS} ${INCLUDES} ${DFLAGS} test_list.C -o test_list.aout

echo "compiling test_map.C..."
g++ ${CXXFLAGS} ${INCLUDES} ${DFLAGS} test_map.C -o test_map.aout
