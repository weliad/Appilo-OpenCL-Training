CC=gcc
LIBS_FLAGS=-lOpenCL -L/opt/rocm/opencl/lib/
INCL_FLAGS=-I/opt/rocm/include/
CFLAGS=-DCL_TARGET_OPENCL_VERSION=200

OBJ = upper_case_cl.o 

%.o: %.c
	$(CC) -c -o $@ $< $(INCL_FLAGS) $(CFLAGS)

upper_case_cl: $(OBJ)
	$(CC) -o $@ $^ $(INCL_FLAGS) $(CFLAGS) $(LIBS_FLAGS) $(LIBS)

.PHONY: clean

clean:
	rm $(OBJ) upper_case_cl
