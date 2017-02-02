# Panoply
Low-TCB Linux Applications with SGX Enclaves

Please refer to the [Project Page](https://shwetasshinde24.github.io/Panoply) for documentation and setup details.


# OpenSSL Case Study	


## Compilation

### Build libssl and libcrypto libraries

<code>
cd openssl/topenssl/
</code>

<code>
make all -j8
</code>

This produces _libssl.a_ and _libcrypto.a_ files in the topenssl folder.

### Copy the libraries to src folder

<code>
cp libcrypto.a libssl.a ../src/
</code>

### Build the Enclave and the App

<code>
cd ../src/
</code>

<code>
make all
</code>

This produces a _TopensslEnclave.signed.so_ file for enclave and an _app_ file for the executable.

## Execution

### Run the app

<code>
./app sha1
</code>

The above command is just an example. You can try other tests for the OpenSSL benchmark. For running the complete benchmark, just run the app file without any arguments. 

<code>
./app
</code>

## Making changes to the App

The App.cpp file has the following code:

* Current code

<code>
/* ret = TopensslEnclave_ecall_test_bm_ssl(global_eid, &ecall_return, argc, argv); */
</code>

<code>
ret = TopensslEnclave_ecall_test_speed_crypto(global_eid, &ecall_return, argc, argv);
</code>

You can modify the above code to execute the SSL test. Do the following changes to the code.

* Modified code

<code>
ret = TopensslEnclave_ecall_test_bm_ssl(global_eid, &ecall_return, argc, argv);         
</code>

<code>
/* ret = TopensslEnclave_ecall_test_speed_crypto(global_eid, &ecall_return, argc, argv); */
</code>

* Build and re-run the app

<code>
make all
</code>

<code>
./app -dhe1024dsa -bytes 102400 -num 10 -tls1 -server_auth -time
</code>
