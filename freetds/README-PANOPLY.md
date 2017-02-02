# Panoply
Low-TCB Linux Applications with SGX Enclaves

Please refer to the [Project Page](https://shwetasshinde24.github.io/Panoply) for documentation and setup details.

#FreeTDS Case Study

## Compilation

### Go to the src directory of the case study 

<code>
$ cd case-studies/freetds/src/
</code>

### Ensure that you have all the necessary library files:

<code>
$ ls *.a
</code>

case-studies/freetds/src/libcrypto.a
case-studies/freetds/src/libevent.a
case-studies/freetds/src/libevent_core.a
case-studies/freetds/src/libevent_extra.a
case-studies/freetds/src/libevent_openssl.a
case-studies/freetds/src/libevent_pthreads.a
case-studies/freetds/src/libssl.a
case-studies/freetds/src/libz.a

### Compile the case study

<code>
$ make all
</code>

## Execution

The test logs in to the remote database server, performs SQL operations on the database, and then logs out. 

### Start the FreeTDS Client test

<code>
$ ./app 
</code>