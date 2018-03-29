
#include "select-demo.h"

/* =====================================================================
   Copyright © 2016, Avnet (R)

   Contributors:
     * James M Flynn, www.em.avnet.com 
 
   Licensed under the Apache License, Version 2.0 (the "License"); 
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, 
   software distributed under the License is distributed on an 
   "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, 
   either express or implied. See the License for the specific 
   language governing permissions and limitations under the License.

    @file          main.cpp
    @version       1.0
    @date          Dec 2016

======================================================================== */

#if DEMO == DEMO_HTTPx

#include "mbed.h"
#include "easy-connect.h"
#include "http_request.h"
#include "https_request.h"
#include "BG96Interface.h"

#define STREAM_CNT  10          //when we test streaming, this is how many times to stream the string
#define STR_SIZE    150*(STREAM_CNT+1) //use a fixed size string buffer based on the streaming data count

#define TOSTR(x) #x
#define INTSTR(x) TOSTR(x)

//
// We do the same thing for both http and https, so create a macro to eaze the typing...
//


/* List of trusted root CA certificates
 * currently one: Let's Encrypt, the CA for httpbin.org
 *
 * To add more root certificates, just concatenate them.
 */
const char SSL_CA_PEM[] = "-----BEGIN CERTIFICATE-----\n"
    "MIIEkjCCA3qgAwIBAgIQCgFBQgAAAVOFc2oLheynCDANBgkqhkiG9w0BAQsFADA/\n"
    "MSQwIgYDVQQKExtEaWdpdGFsIFNpZ25hdHVyZSBUcnVzdCBDby4xFzAVBgNVBAMT\n"
    "DkRTVCBSb290IENBIFgzMB4XDTE2MDMxNzE2NDA0NloXDTIxMDMxNzE2NDA0Nlow\n"
    "SjELMAkGA1UEBhMCVVMxFjAUBgNVBAoTDUxldCdzIEVuY3J5cHQxIzAhBgNVBAMT\n"
    "GkxldCdzIEVuY3J5cHQgQXV0aG9yaXR5IFgzMIIBIjANBgkqhkiG9w0BAQEFAAOC\n"
    "AQ8AMIIBCgKCAQEAnNMM8FrlLke3cl03g7NoYzDq1zUmGSXhvb418XCSL7e4S0EF\n"
    "q6meNQhY7LEqxGiHC6PjdeTm86dicbp5gWAf15Gan/PQeGdxyGkOlZHP/uaZ6WA8\n"
    "SMx+yk13EiSdRxta67nsHjcAHJyse6cF6s5K671B5TaYucv9bTyWaN8jKkKQDIZ0\n"
    "Z8h/pZq4UmEUEz9l6YKHy9v6Dlb2honzhT+Xhq+w3Brvaw2VFn3EK6BlspkENnWA\n"
    "a6xK8xuQSXgvopZPKiAlKQTGdMDQMc2PMTiVFrqoM7hD8bEfwzB/onkxEz0tNvjj\n"
    "/PIzark5McWvxI0NHWQWM6r6hCm21AvA2H3DkwIDAQABo4IBfTCCAXkwEgYDVR0T\n"
    "AQH/BAgwBgEB/wIBADAOBgNVHQ8BAf8EBAMCAYYwfwYIKwYBBQUHAQEEczBxMDIG\n"
    "CCsGAQUFBzABhiZodHRwOi8vaXNyZy50cnVzdGlkLm9jc3AuaWRlbnRydXN0LmNv\n"
    "bTA7BggrBgEFBQcwAoYvaHR0cDovL2FwcHMuaWRlbnRydXN0LmNvbS9yb290cy9k\n"
    "c3Ryb290Y2F4My5wN2MwHwYDVR0jBBgwFoAUxKexpHsscfrb4UuQdf/EFWCFiRAw\n"
    "VAYDVR0gBE0wSzAIBgZngQwBAgEwPwYLKwYBBAGC3xMBAQEwMDAuBggrBgEFBQcC\n"
    "ARYiaHR0cDovL2Nwcy5yb290LXgxLmxldHNlbmNyeXB0Lm9yZzA8BgNVHR8ENTAz\n"
    "MDGgL6AthitodHRwOi8vY3JsLmlkZW50cnVzdC5jb20vRFNUUk9PVENBWDNDUkwu\n"
    "Y3JsMB0GA1UdDgQWBBSoSmpjBH3duubRObemRWXv86jsoTANBgkqhkiG9w0BAQsF\n"
    "AAOCAQEA3TPXEfNjWDjdGBX7CVW+dla5cEilaUcne8IkCJLxWh9KEik3JHRRHGJo\n"
    "uM2VcGfl96S8TihRzZvoroed6ti6WqEBmtzw3Wodatg+VyOeph4EYpr/1wXKtx8/\n"
    "wApIvJSwtmVi4MFU5aMqrSDE6ea73Mj2tcMyo5jMd6jmeWUHK8so/joWUoHOUgwu\n"
    "X4Po1QYz+3dszkDqMp4fklxBwXRsW10KXzPMTZ+sOPAveyxindmjkW8lGy+QsRlG\n"
    "PfZ+G6Z6h7mjem0Y+iWlkYcV4PIWL1iwBi8saCbGS5jN2p8M+X+Q7UNKEkROb3N6\n"
    "KOqkqm57TH2H3eDJAkSnh6/DNFu0Qg==\n"
    "-----END CERTIFICATE-----\n";

//
// This example is setup to use MBED OS (5.2).  It sets up a thread to call the different tests
// so the default stack size can be varied.  TLS is stack intensive and needs additional stack
// to work effeciently. 
//

Serial pc(USBTX, USBRX);

//
// The two test functions do the same set of tests, the first one uses standard HTTP methods while
// the second test uses HTTPS.
//

void https_test_thread(void);             //Thread that runs the two tests
void test_http(NetworkInterface *net);    //function makes standard HTTP calls
void test_https(NetworkInterface *net);   //function makes standard HTTPS calls

int main() {
    Thread http_test(osPriorityNormal, OS_STACK_SIZE*4, NULL);
    pc.baud(115200);

    printf("Test HTTP and HTTPS interface\n");
    http_test.start(https_test_thread);
    while (true) {
        osDelay(500);
    }
}

//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
// this is the Thread that calls each of the two tests.
//
void https_test_thread(void) {

    NetworkInterface *network = easy_connect(true);

    if (!network) {
        printf("Unable to connect to network!\n");
        return;
        }

    printf("\nModem SW Revision: %s\n\n", FIRMWARE_REV(network));

    test_http(network);
    test_https(network);
    
    printf(" - - - - - - - ALL DONE - - - - - - - \n");

    network->disconnect();
    delete network;
    Thread::wait(osWaitForever);
}


//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
// Utility function to print out responses 
//
void dump_response(HttpResponse* res) 
{
    printf("Status: %d - %s\n", res->get_status_code(), res->get_status_message().c_str());

    printf("Headers:\n");
    for (size_t ix = 0; ix < res->get_headers_length(); ix++) {
        printf("\t%s: %s\n", res->get_headers_fields()[ix]->c_str(), res->get_headers_values()[ix]->c_str());
    }
    printf("\nBody (%d bytes):\n\n%s\n", res->get_body_length(), res->get_body_as_string().c_str());
}

void stream_callback(const char *data, size_t len)
{
    if( data[0] == '{' )
        printf("Chunk Received: ");
    for( size_t x=0; x<len; x++ )
        printf("%c",data[x]);
}

//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
// test the HTTP client class
//
void test_http(NetworkInterface *net) 
{
    TCPSocket *socket = new TCPSocket();

    printf(">>>>>>>>>>>><<<<<<<<<<<<\n");
    printf(">>>  TEST HTTPClient <<<\n");
    printf(">>>>>>>>>>>><<<<<<<<<<<<\n\n");

    nsapi_error_t open_result = socket->open(net);
    if (open_result != 0) {
        printf("Opening TCPSocket failed... %d\n", open_result);
        return;
        }

    nsapi_error_t connect_result = socket->connect("developer.mbed.org", 80);
    if (connect_result != 0) {
        printf("Connecting over TCPSocket failed... %d\n", connect_result);
        return;
        }
    else
        printf("Connected over TCP to developer.mbed.org\n\n");

    printf(" >>>First, lets get a page from http://developer.mbed.org\n");
    {
        HttpRequest* get_req = new HttpRequest(socket,HTTP_GET,"https://os.mbed.com/media/uploads/mbed_official/hello.txt");
        HttpResponse* get_res = get_req->send();
        if (!get_res) {
            printf("HttpRequest failed (error code %d)\n", get_req->get_error());
            return;
            }

        printf("\n----- RESPONSE: -----\n");
        dump_response(get_res);
        delete get_req;
    }
    socket->close();
    delete socket;
 
    socket = new TCPSocket();

    open_result = socket->open(net);
    if (open_result != 0) {
        printf("Opening TCPSocket failed... %d\n", open_result);
        return;
        }

    connect_result = socket->connect("httpbin.org", 80);
    if (connect_result != 0) {
        printf("Connecting over TCPSocket http://httpbin.org... %d\n", connect_result);
        return;
        }
    else
        printf("Connected over TCP to httpbin.org\n\n");

    printf("\n\n >>>Post data... **\n");
    {
        HttpRequest* post_req = new HttpRequest(socket, HTTP_POST, "http://httpbin.org/post");
        post_req->set_header("Content-Type", "application/json");
        const char body[] = "{\"hello\":\"world\"},"
                            "{\"test\":\"1234\"}";

        HttpResponse* post_res = post_req->send(body, strlen(body));
        if (!post_res) {
            printf("HttpRequest failed (error code %d)\n", post_req->get_error());
            return;
        }

        printf("\n----- RESPONSE: -----\n");
        dump_response(post_res);
        delete post_req;
    }

    printf("\n\n >>>Put data... \n");
    {
        HttpRequest* put_req = new HttpRequest(socket, HTTP_PUT, "http://httpbin.org/put");
        put_req->set_header("Content-Type", "application/json");

        const char body[] = "This is a PUT test!";

        HttpResponse* put_res = put_req->send(body, strlen(body));
        if (!put_res) {
            printf("HttpRequest failed (error code %d)\n", put_req->get_error());
            return;
        }

        printf("\n----- RESPONSE: -----\n");
        dump_response(put_res);
        delete put_req;
    }

    printf("\n\n >>>Delete data... \n");
    {
        HttpRequest* del_req = new HttpRequest(socket, HTTP_DELETE, "http://httpbin.org/delete");
        del_req->set_header("Content-Type", "application/json");

        HttpResponse* del_res = del_req->send();
        if (!del_res) {
            printf("HttpRequest failed (error code %d)\n", del_req->get_error());
            return;
        }

        printf("\n----- RESPONSE: -----\n");
        dump_response(del_res);
        delete del_req;
    }

    printf("\n\n >>>HTTP:stream, send http://httpbin.org/stream/" INTSTR(STREAM_CNT) "... \n");
    {
        HttpRequest* stream_req = new HttpRequest(socket, HTTP_GET, "http://httpbin.org/stream/" INTSTR(STREAM_CNT),
                                                  stream_callback );
        stream_req->send();
        delete stream_req;
    }

    printf("\n\n >>>HTTP:Status...\n");
    {
        HttpRequest* get_req = new HttpRequest(socket,HTTP_GET,"http://httpbin.org/get?show_env=1");
        HttpResponse* get_res = get_req->send();
        if (!get_res) {
            printf("HttpRequest failed (error code %d)\n", get_req->get_error());
            return;
            }

        printf("\n----- RESPONSE: -----\n");
        dump_response(get_res);
        delete get_req;
    }
    socket->close();
    delete socket;
}


void dump_httpsresponse(HttpResponse* res) 
{
    mbedtls_printf("Status: %d - %s\n", res->get_status_code(), res->get_status_message().c_str());

    mbedtls_printf("Headers:\n");
    for (size_t ix = 0; ix < res->get_headers_length(); ix++) {
        mbedtls_printf("\t%s: %s\n", res->get_headers_fields()[ix]->c_str(), res->get_headers_values()[ix]->c_str());
    }
    mbedtls_printf("\nBody (%d bytes):\n\n%s\n", res->get_body_length(), res->get_body_as_string().c_str());
}

void stream_httpscallback(const char *data, size_t len)
{
    if( data[0] == '{' )
        printf("Chunk Received: ");
    for( size_t x=0; x<len; x++ )
        printf("%c",data[x]);
}

//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
// test the HTTPS client class
//
void test_https(NetworkInterface *net) 
{

    printf(">>>>>>>>>>>>>>>>>>>>>><<<<<<<<<<<<<<<<<<<<<<\n");
    printf(">>>  TEST HTTPS - set up TLS connection  <<<\n");
    printf(">>>>>>>>>>>>>>>>>>>>>><<<<<<<<<<<<<<<<<<<<<<\n\n");

    TLSSocket* socket = new TLSSocket(net, "httpbin.org", 443, SSL_CA_PEM);
    socket->set_debug(true);
    if (socket->connect() != 0) {
        printf("TLS Connect failed %d\n", socket->error());
        return;
    }

    printf("\n\n >>>Post data... **\n");
    {
        HttpsRequest* post_req = new HttpsRequest(socket, HTTP_POST, "http://httpbin.org/post");
        post_req->set_header("Content-Type", "application/json");
        const char body[] = "{\"hello\":\"world\"},"
                            "{\"test\":\"1234\"}";

        HttpResponse* post_res = post_req->send(body, strlen(body));
        if (!post_res) {
            printf("HttpsRequest failed (error code %d)\n", post_req->get_error());
            return;
        }

        printf("\n----- RESPONSE: -----\n");
        dump_httpsresponse(post_res);
        delete post_req;
    }

    printf("\n\n >>>Put data... \n");
    {
        HttpsRequest* put_req = new HttpsRequest(socket, HTTP_PUT, "http://httpbin.org/put");
        put_req->set_header("Content-Type", "application/json");

        const char body[] = "This is a PUT test!";

        HttpResponse* put_res = put_req->send(body, strlen(body));
        if (!put_res) {
            printf("HttpsRequest failed (error code %d)\n", put_req->get_error());
            return;
        }

        printf("\n----- RESPONSE: -----\n");
        dump_httpsresponse(put_res);
        delete put_req;
    }

    printf("\n\n >>>Delete data... \n");
    {
        HttpsRequest* del_req = new HttpsRequest(socket, HTTP_DELETE, "http://httpbin.org/delete");
        del_req->set_header("Content-Type", "application/json");

        HttpResponse* del_res = del_req->send();
        if (!del_res) {
            printf("HttpsRequest failed (error code %d)\n", del_req->get_error());
            return;
        }

        printf("\n----- RESPONSE: -----\n");
        dump_httpsresponse(del_res);
        delete del_req;
    }

    printf("\n\n >>>HTTP:stream, send http://httpbin.org/stream/" INTSTR(STREAM_CNT)"... \n");
    {
        HttpsRequest* stream_req = new HttpsRequest(socket, HTTP_GET, "http://httpbin.org/stream/" INTSTR(STREAM_CNT), 
                                                  stream_httpscallback );
        stream_req->send();
        delete stream_req;
    }

    printf("\n\n >>>HTTP:Status...\n");
    {
        HttpsRequest* get_req = new HttpsRequest(socket,HTTP_GET,"http://httpbin.org/get?show_env=1");
        HttpResponse* get_res = get_req->send();
        if (!get_res) {
            printf("HttpsRequest failed (error code %d)\n", get_req->get_error());
            return;
            }

        printf("\n----- RESPONSE: -----\n");
        dump_httpsresponse(get_res);
        delete get_req;
    }
    delete socket;
}

#endif // DEMO

