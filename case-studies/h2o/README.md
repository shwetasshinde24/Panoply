# Panoply
Low-TCB Linux Applications with SGX Enclaves

Please refer to the [Project Page](https://shwetasshinde24.github.io/Panoply) for documentation and usage details.

#H2O Case Study

## Compilation

### Go to the src directory of the case study 

<code>
$ cd case-studies/h2o/src/
</code>

### Ensure that you have all the necessary library files:

<code>
$ ls *.a
</code>

case-studies/h2o/src/libcrypto.a

case-studies/h2o/src/libssl.a

case-studies/h2o/src/libyaml.a

case-studies/h2o/src/libyrmcds.a

case-studies/h2o/src/libz.a

### Compile the case study

<code>
$ make all
</code>

## Execution

### Start the H2O webserver with appropriate configuration file

<code>
$ ./app -c h2o.conf
</code>

### Check if the server is up and running

<code>
$ netstat -plnt
</code>

In the results, you should see one entry similar to the following

<code>
tcp        0      0 127.0.0.1:8888          0.0.0.0:*               LISTEN      12397/.         
</code>

<code>
$ openssl s_client -connect 127.0.0.1:8888
</code>

The above command should return the connection details along with the server certificate.

### Testing with Browser 

Open the following URL in your browser: 
[https://localhost:8888/](https://localhost:8888/)

Note: Ignore the SSL warning, since the server is using self-signed certificate

The URL will load our default index.html page, which is a replica of [Eclipse Foundation Software User Agreement](http://www.eclipse.org/licenses/notice.html)

### Test other sample pages via following URLs:

[https://localhost:8888/index2.html](https://localhost:8888/index2.html)

[https://localhost:8888/dummy/notice.html](https://localhost:8888/dummy/notice.html)

[https://localhost:8888/file200B.txt](https://localhost:8888/file200B.txt)
