These files allow you to build a simple HTTP/HTTPS application that will exchange data with httpbin.org and ensure the BG96 hardware/driver is working correctly.

# Note
  -The following firmware version was used in testing:
      Modem SW Revision: BG96 Rev:BG96MAR02A04M1G



# Required tools
1. mbed-cli (version 1.3.0 or later)
2. latest version of GNU ARM Embedded Toolchain: **https://developer.arm.com/open-source/gnu-toolchain/gnu-rm/downloads**

# Create Project
1. Import the BG96_Example project: **mbed import http://github.com/Avnet/BG96_Example**

2. Goto the BG96_Example folder, Then edit mbed_settings.py and add the path to your compiler using GCC_ARM_PATH

# Build Application
1.  Build the program by executing **'mbed compile -t GCC_ARM -m NUCLEO_L476RG'**

2.  When building the tests, it is possible to enable varying amounts of debug information to be output by the 
    Network driver.  These settings are located in the 'mbed_app.json' file (the bg96_config.json file is used when
    building for Green Tea).  To enable or disable WNC Debug output, set the 'bg96_debug' flag to 'true' (or 1) or 
    to 'false' (or 0) to disable.  

    The amount of debug information output is controlled by the 'bg96-debug-setting' flag in the 'mbed_app.json' file.
    The values for this flag enabled debug output to trace various activities (see mbed_app.json for detailed settings).

3. Verify operation of the basic application program by executing it on the target hardware.  This is done by monitoring 
   the program operation using a teminal program (ex. minicom or hyperterm), with settings of 115200-N81. Program output
    should resemble:

> 
Test HTTP and HTTPS interface
[EasyConnect] Using BG96
[EasyConnect] IPv4 mode
[EasyConnect] Connected to Network successfully
[EasyConnect] MAC address 37:67:61:79:08:72:30
[EasyConnect] IP address 10.192.139.159

Modem SW Revision: BG96 Rev:BG96MAR02A04M1G

>>>>>>>>>>>><<<<<<<<<<<<
>>>  TEST HTTPClient <<<
>>>>>>>>>>>><<<<<<<<<<<<

Connected over TCP to developer.mbed.org

 >>>First, lets get a page from http://developer.mbed.org

----- RESPONSE: -----
Status: 200 - OK
Headers:
	Server: nginx/1.11.10
	Date: Wed, 28 Mar 2018 12:58:12 GMT
	Content-Type: text/plain
	Content-Length: 14
	Connection: keep-alive
	Last-Modified: Fri, 27 Jul 2012 13:30:34 GMT
	Accept-Ranges: bytes
	Cache-Control: max-age=36000
	Expires: Wed, 28 Mar 2018 22:57:52 GMT
	X-Upstream-L1-next-hop: 217.140.101.34:8080
	X-Upstream-L1: developer-sjc-indigo-border-nginx

Body (14 bytes):

Hello world!

Connected over TCP to httpbin.org



 >>>Post data... **

----- RESPONSE: -----
Status: 200 - OK
Headers:
	Connection: keep-alive
	Server: meinheld/0.6.1
	Date: Wed, 28 Mar 2018 12:58:04 GMT
	Content-Type: application/json
	Access-Control-Allow-Origin: *
	Access-Control-Allow-Credentials: true
	X-Powered-By: Flask
	X-Processed-Time: 0
	Content-Length: 335
	Via: 1.1 vegur

Body (335 bytes):

{
  "args": {}, 
  "data": "{\"hello\":\"world\"},{\"test\":\"1234\"}", 
  "files": {}, 
  "form": {}, 
  "headers": {
    "Connection": "close", 
    "Content-Length": "33", 
    "Content-Type": "application/json", 
    "Host": "httpbin.org"
  }, 
  "json": null, 
  "origin": "205.197.242.109", 
  "url": "http://httpbin.org/post"
}



 >>>Put data... 

----- RESPONSE: -----
Status: 200 - OK
Headers:
	Connection: keep-alive
	Server: meinheld/0.6.1
	Date: Wed, 28 Mar 2018 12:58:03 GMT
	Content-Type: application/json
	Access-Control-Allow-Origin: *
	Access-Control-Allow-Credentials: true
	X-Powered-By: Flask
	X-Processed-Time: 0
	Content-Length: 312
	Via: 1.1 vegur

Body (312 bytes):

{
  "args": {}, 
  "data": "This is a PUT test!", 
  "files": {}, 
  "form": {}, 
  "headers": {
    "Connection": "close", 
    "Content-Length": "19", 
    "Content-Type": "application/json", 
    "Host": "httpbin.org"
  }, 
  "json": null, 
  "origin": "205.197.242.109", 
  "url": "http://httpbin.org/put"
}



 >>>Delete data... 

----- RESPONSE: -----
Status: 200 - OK
Headers:
	Connection: keep-alive
	Server: meinheld/0.6.1
	Date: Wed, 28 Mar 2018 12:58:04 GMT
	Content-Type: application/json
	Access-Control-Allow-Origin: *
	Access-Control-Allow-Credentials: true
	X-Powered-By: Flask
	X-Processed-Time: 0
	Content-Length: 295
	Via: 1.1 vegur

Body (295 bytes):

{
  "args": {}, 
  "data": "", 
  "files": {}, 
  "form": {}, 
  "headers": {
    "Connection": "close", 
    "Content-Length": "0", 
    "Content-Type": "application/json", 
    "Host": "httpbin.org"
  }, 
  "json": null, 
  "origin": "205.197.242.109", 
  "url": "http://httpbin.org/delete"
}



 >>>HTTP:stream, send http://httpbin.org/stream/10... 
Chunk Received: {"args": {}, "headers": {"Host": "httpbin.org", "Connection": "close"}, "url": "http://httpbin.org/stream/10", "id": 0, "origin": "205.197.242.109"}
Chunk Received: {"args": {}, "headers": {"Host": "httpbin.org", "Connection": "close"}, "url": "http://httpbin.org/stream/10", "id": 1, "origin": "205.197.242.109"}
Chunk Received: {"args": {}, "headers": {"Host": "httpbin.org", "Connection": "close"}, "url": "http://httpbin.org/stream/10", "id": 2, "origin": "205.197.242.109"}
Chunk Received: {"args": {}, "headers": {"Host": "httpbin.org", "Connection": "close"}, "url": "http://httpbin.org/stream/10", "id": 3, "origin": "205.197.242.109"}
Chunk Received: {"args": {}, "headers": {"Host": "httpbin.org", "Connection": "close"}, "url": "http://httpbin.org/stream/10", "id": 4, "origin": "205.197.242.109"}
Chunk Received: {"args": {}, "headers": {"Host": "httpbin.org", "Connection": "close"}, "url": "http://httpbin.org/stream/10", "id": 5, "origin": "205.197.242.109"}
Chunk Received: {"args": {}, "headers": {"Host": "httpbin.org", "Connection": "close"}, "url": "http://httpbin.org/stream/10", "id": 6, "origin": "205.197.242.109"}
Chunk Received: {"args": {}, "headers": {"Host": "httpbin.org", "Connection": "close"}, "url": "http://httpbin.org/stream/10", "id": 7, "origin": "205.197.242.109"}
Chunk Received: {"args": {}, "headers": {"Host": "httpbin.org", "Connection": "close"}, "url": "http://httpbin.org/stream/10", "id": 8, "origin": "205.197.242.109"}
Chunk Received: {"args": {}, "headers": {"Host": "httpbin.org", "Connection": "close"}, "url": "http://httpbin.org/stream/10", "id": 9, "origin": "205.197.242.109"}


 >>>HTTP:Status...

----- RESPONSE: -----
Status: 200 - OK
Headers:
	Connection: keep-alive
	Server: meinheld/0.6.1
	Date: Wed, 28 Mar 2018 12:58:05 GMT
	Content-Type: application/json
	Access-Control-Allow-Origin: *
	Access-Control-Allow-Credentials: true
	X-Powered-By: Flask
	X-Processed-Time: 0
	Content-Length: 485
	Via: 1.1 vegur

Body (485 bytes):

{
  "args": {
    "show_env": "1"
  }, 
  "headers": {
    "Connect-Time": "0", 
    "Connection": "close", 
    "Host": "httpbin.org", 
    "Total-Route-Time": "0", 
    "Via": "1.1 vegur", 
    "X-Forwarded-For": "205.197.242.109", 
    "X-Forwarded-Port": "80", 
    "X-Forwarded-Proto": "http", 
    "X-Request-Id": "c0473d12-4062-4f12-88f2-7456d75de557", 
    "X-Request-Start": "1522241885624"
  }, 
  "origin": "205.197.242.109", 
  "url": "http://httpbin.org/get?show_env=1"
}

>>>>>>>>>>>>>>>>>>>>>><<<<<<<<<<<<<<<<<<<<<<
>>>  TEST HTTPS - set up TLS connection  <<<
>>>>>>>>>>>>>>>>>>>>>><<<<<<<<<<<<<<<<<<<<<<

Connecting to httpbin.org:443
Starting the TLS handshake...
TLS connection to httpbin.org:443 established
Server certificate:
    cert. version     : 3
    serial number     : 03:55:B1:71:8C:8A:36:EC:AB:6C:1F:EA:C2:DD:D0:EC:F9:AD
    issuer name       : C=US, O=Let's Encrypt, CN=Let's Encrypt Authority X3
    subject name      : CN=httpbin.org
    issued  on        : 2018-03-13 01:23:44
    expires on        : 2018-06-11 01:23:44
    signed using      : RSA with SHA-256
    RSA key size      : 2048 bits
    basic constraints : CA=false
    subject alt name  : httpbin.org, www.httpbin.org
    key usage         : Digital Signature, Key Encipherment
    ext key usage     : TLS Web Server Authentication, TLS Web Client Authentication
Certificate verification passed



 >>>Post data... **

----- RESPONSE: -----
Status: 200 - OK
Headers:
	Connection: keep-alive
	Server: meinheld/0.6.1
	Date: Wed, 28 Mar 2018 12:58:19 GMT
	Content-Type: application/json
	Access-Control-Allow-Origin: *
	Access-Control-Allow-Credentials: true
	X-Powered-By: Flask
	X-Processed-Time: 0
	Content-Length: 336
	Via: 1.1 vegur

Body (336 bytes):

{
  "args": {}, 
  "data": "{\"hello\":\"world\"},{\"test\":\"1234\"}", 
  "files": {}, 
  "form": {}, 
  "headers": {
    "Connection": "close", 
    "Content-Length": "33", 
    "Content-Type": "application/json", 
    "Host": "httpbin.org"
  }, 
  "json": null, 
  "origin": "205.197.242.109", 
  "url": "https://httpbin.org/post"
}



 >>>Put data... 

----- RESPONSE: -----
Status: 200 - OK
Headers:
	Connection: keep-alive
	Server: meinheld/0.6.1
	Date: Wed, 28 Mar 2018 12:58:20 GMT
	Content-Type: application/json
	Access-Control-Allow-Origin: *
	Access-Control-Allow-Credentials: true
	X-Powered-By: Flask
	X-Processed-Time: 0
	Content-Length: 313
	Via: 1.1 vegur

Body (313 bytes):

{
  "args": {}, 
  "data": "This is a PUT test!", 
  "files": {}, 
  "form": {}, 
  "headers": {
    "Connection": "close", 
    "Content-Length": "19", 
    "Content-Type": "application/json", 
    "Host": "httpbin.org"
  }, 
  "json": null, 
  "origin": "205.197.242.109", 
  "url": "https://httpbin.org/put"
}



 >>>Delete data... 

----- RESPONSE: -----
Status: 200 - OK
Headers:
	Connection: keep-alive
	Server: meinheld/0.6.1
	Date: Wed, 28 Mar 2018 12:58:20 GMT
	Content-Type: application/json
	Access-Control-Allow-Origin: *
	Access-Control-Allow-Credentials: true
	X-Powered-By: Flask
	X-Processed-Time: 0
	Content-Length: 296
	Via: 1.1 vegur

Body (296 bytes):

{
  "args": {}, 
  "data": "", 
  "files": {}, 
  "form": {}, 
  "headers": {
    "Connection": "close", 
    "Content-Length": "0", 
    "Content-Type": "application/json", 
    "Host": "httpbin.org"
  }, 
  "json": null, 
  "origin": "205.197.242.109", 
  "url": "https://httpbin.org/delete"
}



 >>>HTTP:stream, send http://httpbin.org/stream/10... 
Chunk Received: {"args": {}, "headers": {"Host": "httpbin.org", "Connection": "close"}, "url": "https://httpbin.org/stream/10", "id": 0, "origin": "205.197.242.109"}
Chunk Received: {"args": {}, "headers": {"Host": "httpbin.org", "Connection": "close"}, "url": "https://httpbin.org/stream/10", "id": 1, "origin": "205.197.242.109"}
Chunk Received: {"args": {}, "headers": {"Host": "httpbin.org", "Connection": "close"}, "url": "https://httpbin.org/stream/10", "id": 2, "origin": "205.197.242.109"}
Chunk Received: {"args": {}, "headers": {"Host": "httpbin.org", "Connection": "close"}, "url": "https://httpbin.org/stream/10", "id": 3, "origin": "205.197.242.109"}
Chunk Received: {"args": {}, "headers": {"Host": "httpbin.org", "Connection": "close"}, "url": "https://httpbin.org/stream/10", "id": 4, "origin": "205.197.242.109"}
Chunk Received: {"args": {}, "headers": {"Host": "httpbin.org", "Connection": "close"}, "url": "https://httpbin.org/stream/10", "id": 5, "origin": "205.197.242.109"}
Chunk Received: {"args": {}, "headers": {"Host": "httpbin.org", "Connection": "close"}, "url": "https://httpbin.org/stream/10", "id": 6, "origin": "205.197.242.109"}
Chunk Received: {"args": {}, "headers": {"Host": "httpbin.org", "Connection": "close"}, "url": "https://httpbin.org/stream/10", "id": 7, "origin": "205.197.242.109"}
Chunk Received: {"args": {}, "headers": {"Host": "httpbin.org", "Connection": "close"}, "url": "https://httpbin.org/stream/10", "id": 8, "origin": "205.197.242.109"}
Chunk Received: {"args": {}, "headers": {"Host": "httpbin.org", "Connection": "close"}, "url": "https://httpbin.org/stream/10", "id": 9, "origin": "205.197.242.109"}


 >>>HTTP:Status...

----- RESPONSE: -----
Status: 200 - OK
Headers:
	Connection: keep-alive
	Server: meinheld/0.6.1
	Date: Wed, 28 Mar 2018 12:58:20 GMT
	Content-Type: application/json
	Access-Control-Allow-Origin: *
	Access-Control-Allow-Credentials: true
	X-Powered-By: Flask
	X-Processed-Time: 0
	Content-Length: 488
	Via: 1.1 vegur

Body (488 bytes):

{
  "args": {
    "show_env": "1"
  }, 
  "headers": {
    "Connect-Time": "0", 
    "Connection": "close", 
    "Host": "httpbin.org", 
    "Total-Route-Time": "0", 
    "Via": "1.1 vegur", 
    "X-Forwarded-For": "205.197.242.109", 
    "X-Forwarded-Port": "443", 
    "X-Forwarded-Proto": "https", 
    "X-Request-Id": "1a203766-8bdd-411b-89a4-25911114e72b", 
    "X-Request-Start": "1522241901714"
  }, 
  "origin": "205.197.242.109", 
  "url": "https://httpbin.org/get?show_env=1"
}

 - - - - - - - ALL DONE - - - - - - - 

> 

# Build for Greentea testing
You can test driver operation by building and running the MBed OS Greentea test suite:
1. There is a known issue when using Greentea (https://os.mbed.com/docs/v5.7/tools/testing-applications.html)
   whereby there cannot be a main() function outside of a TESTS directory when building and running tests. This 
   is because all nontest code is compiled and linked with the test code and a linker error will occur due to 
   multiple main() functions defined. To eleminate this problem, rename the main application file in the 'source'
   directory to build. NOTE: this only applies when using the Greentea test suite.

   In summary, rename the application source file 'source/main-x.cpp' to 'source/main-x.keepcpp'.

2. Execute the command: **mbed test -m NUCLEO_L476RG -t GCC_ARM -c --test-config bg96_config.json -n mbed-os-tests-netsocket-\***
   When running the test suite, it programs different test files into the hardware to run so execution will take
   some time to complete.  When finished, you will get a summary report similar to:

<code>
    mbedgt: test suite report:

+-----------------------+---------------+-----------------------------------------+--------+--------------------+-------------+
| target                | platform_name | test suite                              | result | elapsed_time (sec) | copy_method |
+-----------------------+---------------+-----------------------------------------+--------+--------------------+-------------+
| NUCLEO_L476RG-GCC_ARM | NUCLEO_L476RG | mbed-os-tests-netsocket-connectivity    | OK     | 47.72              | default     |
| NUCLEO_L476RG-GCC_ARM | NUCLEO_L476RG | mbed-os-tests-netsocket-gethostbyname   | OK     | 25.99              | default     |
| NUCLEO_L476RG-GCC_ARM | NUCLEO_L476RG | mbed-os-tests-netsocket-ip_parsing      | OK     | 11.83              | default     |
| NUCLEO_L476RG-GCC_ARM | NUCLEO_L476RG | mbed-os-tests-netsocket-socket_sigio    | OK     | 36.46              | default     |
| NUCLEO_L476RG-GCC_ARM | NUCLEO_L476RG | mbed-os-tests-netsocket-tcp_echo        | OK     | 37.9               | default     |
| NUCLEO_L476RG-GCC_ARM | NUCLEO_L476RG | mbed-os-tests-netsocket-tcp_hello_world | OK     | 28.42              | default     |
| NUCLEO_L476RG-GCC_ARM | NUCLEO_L476RG | mbed-os-tests-netsocket-udp_echo        | OK     | 30.89              | default     |
+-----------------------+---------------+-----------------------------------------+--------+--------------------+-------------+
mbedgt: test suite results: 7 OK
mbedgt: test case report:
+-----------------------+---------------+-----------------------------------------+----------------------------------------+--------+--------+--------+--------------------+
| target                | platform_name | test suite                              | test case                              | passed | failed | result | elapsed_time (sec) |
+-----------------------+---------------+-----------------------------------------+----------------------------------------+--------+--------+--------+--------------------+
| NUCLEO_L476RG-GCC_ARM | NUCLEO_L476RG | mbed-os-tests-netsocket-connectivity    | Bringing the network up and down       | 1      | 0      | OK     | 14.03              |
| NUCLEO_L476RG-GCC_ARM | NUCLEO_L476RG | mbed-os-tests-netsocket-connectivity    | Bringing the network up and down twice | 1      | 0      | OK     | 21.89              |
| NUCLEO_L476RG-GCC_ARM | NUCLEO_L476RG | mbed-os-tests-netsocket-gethostbyname   | DNS literal                            | 1      | 0      | OK     | 0.02               |
| NUCLEO_L476RG-GCC_ARM | NUCLEO_L476RG | mbed-os-tests-netsocket-gethostbyname   | DNS preference literal                 | 1      | 0      | OK     | 0.02               |
| NUCLEO_L476RG-GCC_ARM | NUCLEO_L476RG | mbed-os-tests-netsocket-gethostbyname   | DNS preference query                   | 1      | 0      | OK     | 0.02               |
| NUCLEO_L476RG-GCC_ARM | NUCLEO_L476RG | mbed-os-tests-netsocket-gethostbyname   | DNS query                              | 1      | 0      | OK     | 0.14               |
| NUCLEO_L476RG-GCC_ARM | NUCLEO_L476RG | mbed-os-tests-netsocket-ip_parsing      | Hollowed IPv6 address                  | 1      | 0      | OK     | 0.0                |
| NUCLEO_L476RG-GCC_ARM | NUCLEO_L476RG | mbed-os-tests-netsocket-ip_parsing      | Left-weighted IPv4 address             | 1      | 0      | OK     | 0.02               |
| NUCLEO_L476RG-GCC_ARM | NUCLEO_L476RG | mbed-os-tests-netsocket-ip_parsing      | Left-weighted IPv6 address             | 1      | 0      | OK     | 0.0                |
| NUCLEO_L476RG-GCC_ARM | NUCLEO_L476RG | mbed-os-tests-netsocket-ip_parsing      | Null IPv4 address                      | 1      | 0      | OK     | 0.0                |
| NUCLEO_L476RG-GCC_ARM | NUCLEO_L476RG | mbed-os-tests-netsocket-ip_parsing      | Null IPv6 address                      | 1      | 0      | OK     | 0.0                |
| NUCLEO_L476RG-GCC_ARM | NUCLEO_L476RG | mbed-os-tests-netsocket-ip_parsing      | Right-weighted IPv4 address            | 1      | 0      | OK     | 0.0                |
| NUCLEO_L476RG-GCC_ARM | NUCLEO_L476RG | mbed-os-tests-netsocket-ip_parsing      | Right-weighted IPv6 address            | 1      | 0      | OK     | 0.01               |
| NUCLEO_L476RG-GCC_ARM | NUCLEO_L476RG | mbed-os-tests-netsocket-ip_parsing      | Simple IPv4 address                    | 1      | 0      | OK     | 0.0                |
| NUCLEO_L476RG-GCC_ARM | NUCLEO_L476RG | mbed-os-tests-netsocket-ip_parsing      | Simple IPv6 address                    | 1      | 0      | OK     | 0.0                |
| NUCLEO_L476RG-GCC_ARM | NUCLEO_L476RG | mbed-os-tests-netsocket-socket_sigio    | Socket Attach Test                     | 1      | 0      | OK     | 3.59               |
| NUCLEO_L476RG-GCC_ARM | NUCLEO_L476RG | mbed-os-tests-netsocket-socket_sigio    | Socket Detach Test                     | 1      | 0      | OK     | 6.22               |
| NUCLEO_L476RG-GCC_ARM | NUCLEO_L476RG | mbed-os-tests-netsocket-socket_sigio    | Socket Reattach Test                   | 1      | 0      | OK     | 0.53               |
| NUCLEO_L476RG-GCC_ARM | NUCLEO_L476RG | mbed-os-tests-netsocket-tcp_echo        | TCP echo                               | 1      | 0      | OK     | 26.16              |
| NUCLEO_L476RG-GCC_ARM | NUCLEO_L476RG | mbed-os-tests-netsocket-tcp_hello_world | TCP hello world                        | 1      | 0      | OK     | 16.66              |
| NUCLEO_L476RG-GCC_ARM | NUCLEO_L476RG | mbed-os-tests-netsocket-udp_echo        | UDP echo                               | 1      | 0      | OK     | 19.2               |
+-----------------------+---------------+-----------------------------------------+----------------------------------------+--------+--------+--------+--------------------+
mbedgt: test case results: 21 OK
mbedgt: completed in 219.44 sec

</code>

NOTE: the "UDP DTLS handshake" test is a known failure and is expected.



