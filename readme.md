# AISE PMI SERVER

To build simply run make, feel free to fork this version for your work !


## Using MPIRUN

```
mpirun [PMI SERVER] [PROCESS] [CMD] [ARGS..]
```
- PMI SERVER: a field exported as PMI_SERVER in the env
- PROCESS: the number of processes to be launched
- CMD: the commadn
- ARGS: optionnal arguments

example:
```
mpirun 127.0.0.1:9000 16 ./a.out
```

You may change the PMI server to match your implementation.

## PMI Test

Used to validate that your PMI runtime works.

```
make
mpirun 127.0.0.1:9000 16 ./test_value
```

## PMI Perf

Used to validate the performance of your PMI runtime.
Only runs on two processes.

```
make
mpirun 127.0.0.1:9000 2 ./test_perf
```


