# Panoply
Low-TCB Linux Applications with SGX Enclaves

# LMBench 

## Configuring Inividual Benchmarks

The current code takes in a benchmark ID before compilation to produce the corresponding executable. 

For example, to get the executable for lat_mem_rd benchmark, we have configured the current code with index number 20 as shown in the following line no. 431 in src/App/App.cpp.

<code>
    ret = MyEnclave_ecall_fork_enter_main(global_eid, NULL, 0, argc, argv, 20);
</code>

You can build other benchmarks by changing the index numbers. Refer to the following list for compiling individual benchmarks of LMBench:

0: bwfilerd
1: bwmem
2: bwmmaprd
3: bwpipe
4: bwtcp
6: bwunix
8: disk
9: enough
11: helloworld
13: latconnect
14: latctx
16: latfcntl
17: latfifo
18: latfs
19: lathttp
20: lat_mem_rd
21: latmmap
23: latpagefault
24: latpipe
26: latproc
28: latrpc
29: latselect
31: latsig
32: latsyscall
33: lattcp
34: latudp
35: latunix
36: latunixconnect
40: memsize
41: mhz
42: msleep
49: lmhttp
50: lmdd

## Configuring Inividual Benchmarks

Once you add the correct benchmark ID, build the code with the following command:

<code>
make 
</code>

This will produce the executable named app in the src folder.

## Executing individual benchmark

Simply run the executable with the correct arguments for the corresonding benchmark as below.

<code>
./app args-to-benchmark
</code>


In our example of lat_mem_rd, you can run it with the following command, where 1 is the size of the file in MB:

<code>
./app 1
</code>

## Compiling the complete suite

Coming Soon..
